import tensorflow as tf
import scipy.sparse as sp
import numpy as np
from time import time
import os
import collections
from abc import abstractmethod
os.environ['TF_CPP_MIN_LOG_LEVEL']='2'

import argparse
from data_loader import load_data

LAYER_IDS = {}
parser = argparse.ArgumentParser()

parser.add_argument('--dataset', type=str, default='book', help='which dataset to use')

args = parser.parse_args()
data = load_data(args)
n_user, n_item, n_entity, n_relation = data[0], data[1], data[2], data[3]
train_data, eval_data, test_data = data[4], data[5], data[6]
kg = data[7]

file_name = '../data/' + args.dataset + '/kg_final.txt'
kg_np = np.loadtxt(file_name, dtype=np.int32)
kg_np = np.unique(kg_np, axis=0)
print('kg_np文件读取成功')
n_relations = max(kg_np[:, 1]) + 1

kg_dict = collections.defaultdict(list)
relation_dict = collections.defaultdict(list)

for head, relation, tail in kg_np:
    kg_dict[head].append((tail, relation))
    relation_dict[relation].append((head, tail))


def get_layer_id(layer_name=''):
    print('开始get_layer_id')
    if layer_name not in LAYER_IDS:
        LAYER_IDS[layer_name] = 0
        return 0
    else:
        LAYER_IDS[layer_name] += 1
        return LAYER_IDS[layer_name]


class Layer(object):
    def __init__(self, name):
        print('开始Layer的__init__')
        if not name:
            layer = self.__class__.__name__.lower()
            name = layer + '_' + str(get_layer_id(layer))
        self.name = name
        print(self.name)
        self.vars = []

    def __call__(self, inputs):
        print('开始Layer的__call__')
        outputs = self._call(inputs)
        return outputs

    @abstractmethod
    def _call(self, inputs):
        print('开始Layer的__call')
        pass


# 使用tf.layers.Dense方法定义了不带偏置的全连接层，将该全连接层作用于交叉后的特征向量，实现压缩的过程
class Dense(Layer):
    def __init__(self, input_dim, output_dim, dropout=0.0, act=tf.nn.relu, name=None):
        print('定义不带偏置的全连接层，将该全连接层作用于交叉后的特征向量，实现压缩的过程')
        super(Dense, self).__init__(name)
        self.n_fold=100
        self.input_dim = input_dim
        self.output_dim = output_dim
        self.dropout = dropout
        self.act = act
        self.all_weights = dict()
        initializer = tf.contrib.layers.xavier_initializer()
        if args.dataset=='movie':
            emb_dim,kge_dim=4,4
            self.weight_size = eval('[6,4,2]')
        elif args.dataset=='book':
            emb_dim,kge_dim=64,64
            self.weight_size = eval('[32,16,16]')   
        else:
            emb_dim,kge_dim=128,128
            self.weight_size = eval('[64,32,32]') 
        self.n_layers = len(self.weight_size)
        self.all_weights['user_embed'] = tf.Variable(initializer([n_user, emb_dim]), name='user_embed')# shape=(6036,8)
        self.all_weights['entity_embed'] = tf.Variable(initializer([n_entity, emb_dim]), name='entity_embed')# shape=(6729,8)

        self.all_weights['relation_embed'] = tf.Variable(initializer([n_relations, kge_dim]),
                                                    name='relation_embed')# shape=(7,8)
        self.all_weights['trans_W'] = tf.Variable(initializer([n_relations, emb_dim, kge_dim]))# shape=(7,8,8)

        self.weight_size_list = [emb_dim] + self.weight_size
        for k in range(self.n_layers):
            self.all_weights['W_gc_%d' %k] = tf.Variable(
                initializer([self.weight_size_list[k], self.weight_size_list[k+1]]), name='W_gc_%d' % k)
            self.all_weights['b_gc_%d' %k] = tf.Variable(
                initializer([1, self.weight_size_list[k+1]]), name='b_gc_%d' % k)

            self.all_weights['W_bi_%d' % k] = tf.Variable(
                initializer([self.weight_size_list[k], self.weight_size_list[k + 1]]), name='W_bi_%d' % k)
            self.all_weights['b_bi_%d' % k] = tf.Variable(
                initializer([1, self.weight_size_list[k + 1]]), name='b_bi_%d' % k)

        with tf.variable_scope(self.name):
            self.weight = tf.get_variable(name='weight', shape=(input_dim, output_dim), dtype=tf.float32)
            self.bias = tf.get_variable(name='bias', shape=output_dim, initializer=tf.zeros_initializer())
        self.vars = [self.weight]
        # self.vars = [self.all_weights['W_gc_0'],self.all_weights['b_gc_0'],self.all_weights['W_bi_0'],self.all_weights['b_bi_0'],
        # self.all_weights['W_gc_1'],self.all_weights['b_gc_1'],self.all_weights['W_bi_1'],self.all_weights['b_bi_1'],
        # self.all_weights['W_gc_2'],self.all_weights['b_gc_2'],self.all_weights['W_bi_2'],self.all_weights['b_bi_2']]


    
    def _split_A_hat(self, X):
        print('开始KGAT中的_split_A_hat')
        A_fold_hat = []

        fold_len = (n_user + n_entity) // self.n_fold

        for i_fold in range(self.n_fold):
            start = i_fold * fold_len
            if i_fold == self.n_fold - 1:
                end = n_user + n_entity
            else:
                end = (i_fold + 1) * fold_len

            A_fold_hat.append(self._convert_sp_mat_to_sp_tensor(X[start:end]))
        return A_fold_hat

    def _convert_sp_mat_to_sp_tensor(self, X):
        # print('开始KGAT中的_convert_sp_mat_to_sp_tensor')
        coo = X.tocoo().astype(np.float32)
        # mat创建数组
        indices = np.mat([coo.row, coo.col]).transpose()
        # tf.SparseTensor生成稀疏矩阵
        return tf.SparseTensor(indices, coo.data, coo.shape)


    def _si_norm_lap(self,adj):
            # print('开始loader_kgat中的_si_norm_lap')
        
            rowsum = np.array(adj.sum(1))

            d_inv = np.power(rowsum, -1).flatten()
            #将所有inf转为0
            d_inv[np.isinf(d_inv)] = 0.
            d_mat_inv = sp.diags(d_inv)

            norm_adj = d_mat_inv.dot(adj)
            return norm_adj.tocoo()

    def _get_relational_adj_list(self):
        print('为用户项目交互和关系KG数据生成稀疏邻接矩阵')
        t1 = time()
        adj_mat_list = []
        adj_r_list = []

        def _np_mat2sp_adj(np_mat, row_pre, col_pre):
            # print('生成矩阵，然后返回的矩阵互为转置矩阵')
            # 6036+6729
            n_all = n_user + n_entity
        
            a_rows = np_mat[:, 0] + row_pre
            a_cols = np_mat[:, 1] + col_pre

            a_vals = [1.] * len(a_rows)

            b_rows = a_cols
            b_cols = a_rows
            b_vals = [1.] * len(b_rows)

            a_adj = sp.coo_matrix((a_vals, (a_rows, a_cols)), shape=(n_all, n_all))
            b_adj = sp.coo_matrix((b_vals, (b_rows, b_cols)), shape=(n_all, n_all))

            return a_adj, b_adj

        print('生成CF的稀疏矩阵：R,R_inv')
        # user-item的邻接矩阵 R和R_inv互逆
        train_data1 = list()
        for interaction in train_data:
            user = interaction[0]
            item = interaction[1]
            label = interaction[2]
            if label == 1:
                train_data1.append([user,item])
        R, R_inv = _np_mat2sp_adj(np.array(train_data1), row_pre=0, col_pre=n_user)

        adj_mat_list.append(R)

        adj_r_list.append(0)

        adj_mat_list.append(R_inv)

        n_relations = max(kg_np[:, 1]) + 1
        adj_r_list.append(n_relations - 1)
        print('\tconvert ratings into adj mat done.')

        print('生成KG的稀疏矩阵：K,K_inv')
        for r_id in relation_dict.keys():
            #np.array(self.relation_dict[r_id])==>[（head,tail）,(head,tail),...]
            #K:[[129955*129955矩阵(但是rows∈[23566,129954] cols∈[23566,129953]才有值）]]
            #item-item邻接矩阵
            K, K_inv = _np_mat2sp_adj(np.array(relation_dict[r_id]), row_pre=n_user, col_pre=n_user)
            #adj_mat_list[??]=[129955*129955矩阵]
            adj_mat_list.append(K)
            #adj_r_list[??] = [1,2,3,4,5,6,7,8,9]
            adj_r_list.append(r_id)

            # adj_mat_list[??]=[129955*129955矩阵]
            adj_mat_list.append(K_inv)
            # adj_r_list[??] = [11,12,13,14,15,16,17,18,19]
            adj_r_list.append(r_id)
        #20 有向图，所以关系也加了一倍
        print('\tconvert %d relational triples into adj mat done. @%.4fs' %(len(adj_mat_list), time()-t1))

        n_relations = len(adj_r_list)
        # print('\tadj relation list is', adj_r_list)

        return adj_mat_list, adj_r_list

    def _call(self, inputs):
        # dropout的作用是丢弃一部分数据，防止模型过拟合
        print('进行GAT')
        # dropout中第二个参数设置神经元被选中的概率,参数 keep_prob: 表示的是保留的比例，
        # 假设为0.8 则 20% 的数据变为0，然后其他的数据乘以 1/keep_prob；keep_prob 越大，保留的越多；
        # relu用于用0替换负数

        self.dim=8
        
        self.adj_list, self.adj_r_list = self._get_relational_adj_list()
        lap_list = [self._si_norm_lap(adj) for adj in self.adj_list]
        self.A = sum(lap_list)
        self.A_fold_hat = self._split_A_hat(self.A)# 列表，存储了分割之后的稀疏矩阵


        ego_embeddings = tf.concat([self.all_weights['user_embed'], self.all_weights['entity_embed']], axis=0)# shape=(12765,8)
        all_embeddings = [ego_embeddings]# shape=(12765,16)加括号是为了后面的matmul运算

        for k in range(0, self.n_layers):
            # A_hat_drop = tf.nn.dropout(A_hat, 1 - self.node_dropout[k], [self.n_users + self.n_items, 1])
            temp_embed = []
            for f in range(self.n_fold):# 100
                # 稀疏tensor和稠密矩阵相乘的方法，完成聚合过程
                temp_embed.append(tf.sparse_tensor_dense_matmul(self.A_fold_hat[f], ego_embeddings))

            # sum messages of neighbors.
            side_embeddings = tf.concat(temp_embed, 0)# shape=(12765,8)

            add_embeddings = ego_embeddings + side_embeddings# shape=(12765,8)

            # transformed sum messages of neighbors.
            sum_embeddings = tf.nn.leaky_relu(
                tf.matmul(add_embeddings, self.all_weights['W_gc_%d' % k]) + self.all_weights['b_gc_%d' % k])# shape=(12765,8)


            # bi messages of neighbors.
            bi_embeddings = tf.multiply(ego_embeddings, side_embeddings)# shape=(12765,8)
            # transformed bi messages of neighbors.
            bi_embeddings = tf.nn.leaky_relu(
                tf.matmul(bi_embeddings, self.all_weights['W_bi_%d' % k]) + self.all_weights['b_bi_%d' % k])# shape=(12765,8)

            ego_embeddings = bi_embeddings + sum_embeddings# shape=(12765,8)
            # message dropout.
            ego_embeddings = tf.nn.dropout(ego_embeddings, 0.9)# shape=(12765,8)

            # normalize the distribution of embeddings.
            norm_embeddings = tf.math.l2_normalize(ego_embeddings, axis=1)# shape=(12765,8)

            all_embeddings += [norm_embeddings]# shape=(12765,16)
        all_embeddings = tf.concat(all_embeddings, 1)# shape=(12765,16)
        ua_embeddings, ea_embeddings = tf.split(all_embeddings, [n_user, n_entity], 0)

        return ua_embeddings, ea_embeddings,lap_list,self.adj_r_list,self.A


class CrossCompressUnit(Layer):
    # 定义交叉压缩单元模型类
    def __init__(self, dim, name=None):
        print('定义交叉压缩单元模型类')
        super(CrossCompressUnit, self).__init__(name)
        self.dim = dim
        with tf.variable_scope(self.name):
            # 在模型中开辟各自的空间，其中的变量均在这个空间内进行管理
            # get_variable创建新的tensorflow变量
            self.weight_vv = tf.get_variable(name='weight_vv', shape=(dim, 1), dtype=tf.float32)
            self.weight_ev = tf.get_variable(name='weight_ev', shape=(dim, 1), dtype=tf.float32)
            self.weight_ve = tf.get_variable(name='weight_ve', shape=(dim, 1), dtype=tf.float32)
            self.weight_ee = tf.get_variable(name='weight_ee', shape=(dim, 1), dtype=tf.float32)
            self.bias_v = tf.get_variable(name='bias_v', shape=dim, initializer=tf.zeros_initializer())
            self.bias_e = tf.get_variable(name='bias_e', shape=dim, initializer=tf.zeros_initializer())
        self.vars = [self.weight_vv, self.weight_ev, self.weight_ve, self.weight_ee]


    def _call(self, inputs):
        print('进行交叉单元运算')
        # [batch_size, dim]
        v, e = inputs# shape=(b,16)

        # v = tf.expand_dims(v, dim=2)# shape=(b,16,1)
        # e = tf.expand_dims(e, dim=1)

        # ve_out=tf.matmul(v,e)# 矩阵外积

        # v1=tf.concat([v,ve_out],axis=0)
        # e1=tf.concat([e,ve_out],axis=0)

        # v1=tf.reshape(v1, [-1, self.dim])
        # e1=tf.reshape(e1, [-1, self.dim])

        # v_output = tf.reshape(tf.matmul(v1, self.weight_vv),
        #                       [-1, self.dim]) + self.bias_v
        # e_output = tf.reshape(tf.matmul(e1, self.weight_ee),
        #                       [-1, self.dim]) + self.bias_e        


        # [batch_size, dim, 1], [batch_size, 1, dim]增加维度
        v = tf.expand_dims(v, dim=2)# shape=(b,16,1)
        e = tf.expand_dims(e, dim=1)# shape=(b,1,16)

        # [batch_size, dim, dim]矩阵v*e
        c_matrix = tf.matmul(v, e)# shape=(b,16,16)

        # perm对矩阵进行转置，2*3*4变成2*4*3
        c_matrix_transpose = tf.transpose(c_matrix, perm=[0, 2, 1])# shape=(b,16,16)

        # [batch_size * dim, dim]
        c_matrix = tf.reshape(c_matrix, [-1, self.dim])# shape=(b*16,16)
        c_matrix_transpose = tf.reshape(c_matrix_transpose, [-1, self.dim])# shape=(b*16,16)

        # [batch_size, dim]  shape=(b,16)
        v_output = tf.reshape(tf.matmul(c_matrix, self.weight_vv) + tf.matmul(c_matrix_transpose, self.weight_ev),
                              [-1, self.dim]) + self.bias_v
        e_output = tf.reshape(tf.matmul(c_matrix, self.weight_ve) + tf.matmul(c_matrix_transpose, self.weight_ee),
                              [-1, self.dim]) + self.bias_e



        return v_output, e_output


class Dense1(Layer):
    #                  8          8
    def __init__(self, input_dim, output_dim, dropout=0.0, act=tf.nn.relu, name=None):
        print('定义不带偏置的全连接层，将该全连接层作用于交叉后的特征向量，实现压缩的过程')
        super(Dense1, self).__init__(name)
        self.input_dim = input_dim
        self.output_dim = output_dim
        self.dropout = dropout
        self.act = act
        with tf.variable_scope(self.name):
            #                                            shape=(8,8)
            self.weight = tf.get_variable(name='weight', shape=(input_dim, output_dim), dtype=tf.float32)
            self.bias = tf.get_variable(name='bias', shape=output_dim, initializer=tf.zeros_initializer())
        self.vars = [self.weight]

    def _call(self, inputs):
        # dropout的作用是丢弃一部分数据，防止模型过拟合
        print('丢弃一部分数据，防止模型过拟合')
        # dropout中第二个参数设置神经元被选中的概率,参数 keep_prob: 表示的是保留的比例，
        # 假设为0.8 则 20% 的数据变为0，然后其他的数据乘以 1/keep_prob；keep_prob 越大，保留的越多；
        #                           self.dropout=0
        x = tf.nn.dropout(inputs, 1-self.dropout)
        output = tf.matmul(x, self.weight) + self.bias
        # tf.nn.relu用于用0替换负数
        return self.act(output)
