import numpy as np
import tensorflow as tf
import scipy.sparse as sp
from sklearn.metrics import roc_auc_score
from layers import Dense, CrossCompressUnit,Dense1
import collections
import argparse


class MKR(object):
    def __init__(self, args, n_users, n_items, n_entities, n_relations):
        self._parse_args(n_users, n_items, n_entities, n_relations)
        self._build_inputs()
        self._build_model(args)
        self._build_loss(args)
        self._build_train(args)

    def _parse_args(self, n_users, n_items, n_entities, n_relations):
        print('收集数据')
        self.n_user = n_users
        self.n_item = n_items
        self.n_entity = n_entities
        self.n_relation = n_relations

        # 收集训练数据，用于计算l2损失
        self.vars_rs = []
        self.vars_kge = []

    def _build_inputs(self):
        # indice：目录
        print('使用placeholder定义输入的数据，不必指定初始值，可在运行时，通过 Session.run 的函数的 feed_dict 参数指定')
        self.user_indices = tf.placeholder(tf.int32, [None], 'user_indices')
        self.item_indices = tf.placeholder(tf.int32, [None], 'item_indices')
        self.labels = tf.placeholder(tf.float32, [None], 'labels')
        self.head_indices = tf.placeholder(tf.int32, [None], 'head_indices')
        self.tail_indices = tf.placeholder(tf.int32, [None], 'tail_indices')
        self.relation_indices = tf.placeholder(tf.int32, [None], 'relation_indices')


    def _build_model(self, args):
        # 构建低层模型
        self._build_low_layers(args)
        # 构建高层模型
        self._build_high_layers(args)

    def _build_low_layers(self, args):
        print('构建低层模型')
        # 生成词嵌入向量
        # 如果你定义的变量名称在之前已被定义过，则TensorFlow会引发异常。可使用tf.get_variable() 函数代替tf.Variable( )。
        # 如果变量存在，函数tf.get_variable() 会返回现有的变量。如果变量不存在，会根据给定形状和初始值创建变量
        # 默认initializer为tf.glorot_uniform_initializer：使得每一层的方差都尽可能相等,
        print('首先生成词嵌入向量')
        self.user_emb_matrix = tf.get_variable('user_emb_matrix', [self.n_user, args.dim])
        self.item_emb_matrix = tf.get_variable('item_emb_matrix', [self.n_item, args.dim])
        self.entity_emb_matrix = tf.get_variable('entity_emb_matrix', [self.n_entity, args.dim])
        self.relation_emb_matrix = tf.get_variable('relation_emb_matrix', [self.n_relation, args.dim])

        # 获取指定输入对应的词嵌入向量，形状为[batch_size, dim]
        # 根据indices寻找对应的matrix中的第indices行
        print('然后获取指定输入对应的词嵌入向量')
        self.user_embeddings = tf.nn.embedding_lookup(self.user_emb_matrix, self.user_indices)
        self.item_embeddings = tf.nn.embedding_lookup(self.item_emb_matrix, self.item_indices)
        self.head_embeddings = tf.nn.embedding_lookup(self.entity_emb_matrix, self.head_indices)
        self.relation_embeddings = tf.nn.embedding_lookup(self.relation_emb_matrix, self.relation_indices)
        self.tail_embeddings = tf.nn.embedding_lookup(self.entity_emb_matrix, self.tail_indices)


        # 按指定参数构建多层MKR结构
        for i in range(args.L):
            print('构建的多层MKR结构：当前：',i+1)
            # 定义全连接层
            user_tail = Dense(input_dim=args.dim, output_dim=args.dim)
            cc_unit = CrossCompressUnit(args.dim)
            # 实现MKR结构的正向处理
            self.user_e,self.tail_e,self.lap_list,self.adj_r_list,self.A = user_tail([self.user_embeddings,self.tail_embeddings])
            self.item_embeddings, self.head_embeddings = cc_unit([self.item_embeddings, self.head_embeddings])
            

            self.user_embeddings=tf.nn.embedding_lookup(self.user_e, self.user_indices)
            self.tail_embeddings=tf.nn.embedding_lookup(self.tail_e, self.tail_indices)

            # 收集训练数据
            self.vars_rs.extend(user_tail.vars)
            self.vars_rs.extend(cc_unit.vars)
            self.vars_kge.extend(user_tail.vars)
            self.vars_kge.extend(cc_unit.vars)

    def _build_high_layers(self, args):
        print('定义高层模型')
        # 推荐算法模型
        # 指定相似度分数计算的方式
        use_inner_product = True
        if use_inner_product:
            print('采用内积方式，self.scores的形状为[batch_size]，每一行求和')
            # 内积方式
            # self.scores的形状为[batch_size]，每一行求和
            self.scores = tf.reduce_sum(self.user_embeddings * self.item_embeddings, axis=1)
        else:
            # [batch_size, dim * 2]
            self.user_item_concat = tf.concat([self.user_embeddings, self.item_embeddings], axis=1)
            for _ in range(args.H - 1):
                rs_mlp = Dense1(input_dim=args.dim * 2, output_dim=args.dim * 2)
                # [batch_size, dim * 2]
                self.user_item_concat = rs_mlp(self.user_item_concat)
                self.vars_rs.extend(rs_mlp.vars)

            rs_pred_mlp = Dense1(input_dim=args.dim * 2, output_dim=1)
            # [batch_size]
            self.scores = tf.squeeze(rs_pred_mlp(self.user_item_concat))
            self.vars_rs.extend(rs_pred_mlp.vars)# 收集参数

            
        # normalized：标准化
        self.scores_normalized = tf.nn.sigmoid(self.scores)

        # 知识图谱词嵌入模型
        # [batch_size, dim * 2]
        self.head_relation_concat = tf.concat([self.head_embeddings, self.relation_embeddings], axis=1)
        for _ in range(args.H - 1):
            kge_mlp = Dense1(input_dim=args.dim * 2, output_dim=args.dim * 2)
            # [batch_size, dim]
            self.head_relation_concat = kge_mlp(self.head_relation_concat)
            self.vars_kge.extend(kge_mlp.vars)

        print('知识图谱词嵌入模型定义全连接层，进行softmax归一化')
        # 定义全连接层
        kge_pred_mlp = Dense1(input_dim=args.dim * 2, output_dim=args.dim)
        # [batch_size, 1]
        self.tail_pred = kge_pred_mlp(self.head_relation_concat)
        self.vars_kge.extend(kge_pred_mlp.vars)
        # 进行softmax归一化
        self.tail_pred = tf.nn.sigmoid(self.tail_pred)

        self.scores_kge = tf.nn.sigmoid(tf.reduce_sum(self.tail_embeddings * self.tail_pred, axis=1))
        self.rmse = tf.reduce_mean(
            tf.sqrt(tf.reduce_sum(tf.square(self.tail_embeddings - self.tail_pred), axis=1) / args.dim))

    def _build_loss(self, args):
        # 计算推荐算法模型的loss
        # 对logits通过sigmoid计算，再计算交叉熵
        print('计算推荐算法模型的损失')
        self.base_loss_rs = tf.reduce_mean(
            tf.nn.sigmoid_cross_entropy_with_logits(labels=self.labels, logits=self.scores))
        # l2_loss用于优化目标函数中的正则项，防止参数太多复杂容易过拟合
        # output = sum(t**2)/2
        print('使用l2_loss优化目标函数中的正则项，防止参数太多复杂容易过拟合')
        self.l2_loss_rs = tf.nn.l2_loss(self.user_embeddings) + tf.nn.l2_loss(self.item_embeddings)
        for var in self.vars_rs:
            self.l2_loss_rs += tf.nn.l2_loss(var)
        self.loss_rs = self.base_loss_rs + self.l2_loss_rs * args.l2_weight

        # 计算知识图谱词嵌入模型的loss
        print('计算知识图谱词嵌入模型的损失')
        self.base_loss_kge = -self.scores_kge
        self.l2_loss_kge = tf.nn.l2_loss(self.head_embeddings) + tf.nn.l2_loss(self.tail_embeddings)
        for var in self.vars_kge:
            # 计算L2正则
            self.l2_loss_kge += tf.nn.l2_loss(var)
        self.loss_kge = self.base_loss_kge + self.l2_loss_kge * args.l2_weight

    def _build_train(self, args):
        # 定义优化器
        print('定义优化器，寻找全局最优点的优化算法，引入了二次方梯度校正')
        # tf.train.AdamOptimizer函数是Adam优化算法，是一个寻找全局最优点的优化算法，引入了二次方梯度校正
        self.optimizer_rs = tf.train.AdamOptimizer(args.lr_rs).minimize(self.loss_rs)
        self.optimizer_kge = tf.train.AdamOptimizer(args.lr_kge).minimize(self.loss_kge)

    def train_rs(self, sess, feed_dict):
        # 训练推荐算法模型
        return sess.run([self.optimizer_rs, self.loss_rs], feed_dict)

    def train_kge(self, sess, feed_dict):
        # 训练知识图谱词嵌入模型
        return sess.run([self.optimizer_kge, self.rmse], feed_dict)

    def eval(self, sess, feed_dict):

        # 评估模型
        labels, scores = sess.run([self.labels, self.scores_normalized], feed_dict)
        # auc为曲线下面积，数值越高，模型越优秀
        auc = roc_auc_score(y_true=labels, y_score=scores)
        predictions = [1 if i >= 0.5 else 0 for i in scores]
        # mean求均值，equal输出相等为True，不相等为False
        acc = np.mean(np.equal(predictions, labels))
        return auc, acc

    def get_scores(self, sess, feed_dict):
        return sess.run([self.item_indices, self.scores_normalized], feed_dict)



    """
    Update the attentive laplacian matrix.
    """
    def update_attentive_A(self,sess,n_user,n_entity,step):
        dim=8
            # dropout中第二个参数设置神经元被选中的概率,参数 keep_prob: 表示的是保留的比例，
            # 假设为0.8 则 20% 的数据变为0，然后其他的数据乘以 1/keep_prob；keep_prob 越大，保留的越多；
            # relu用于用0替换负数
            # tf.SparseTensor的作用是构造一个稀疏矩阵类，便于为其他的API提供输入(稀疏矩阵的输入)。
        def _create_attentive_A_out(self):
            # print('开始KGAT中的_create_attentive_A_out')
            indices = np.mat([self.new_h_list, self.new_t_list]).transpose()
            A1 = tf.sparse.softmax(tf.SparseTensor(indices, self.A_values, self.A.shape))
            return A1
        def _generate_transE_score(h, t, r):
            # print('开始KGAT中的_generate_transE_score')
            parser = argparse.ArgumentParser()

            parser.add_argument('--dataset', type=str, default='book', help='which dataset to use')

            args = parser.parse_args()
            file_name = '../data/' + args.dataset + '/kg_final.txt'
            kg_np = np.loadtxt(file_name, dtype=np.int32)
            kg_np = np.unique(kg_np, axis=0)
            # print('kg_np文件读取成功')
            n_relations = max(kg_np[:, 1]) + 1
            all_weights = dict()
            emb_dim,kge_dim=8,8
            initializer = tf.contrib.layers.xavier_initializer()
            all_weights['user_embed'] = tf.Variable(initializer([n_user, emb_dim]), name='user_embed')# shape=(6036,8)
            all_weights['entity_embed'] = tf.Variable(initializer([n_entity, emb_dim]), name='entity_embed')# shape=(6729,8)

            all_weights['relation_embed'] = tf.Variable(initializer([n_relations, kge_dim]),
                                                        name='relation_embed')# shape=(7,8)
            all_weights['trans_W'] = tf.Variable(initializer([n_relations, emb_dim, kge_dim]))# shape=(7,8,8)

            embeddings = tf.concat([all_weights['user_embed'], all_weights['entity_embed']], axis=0)
            embeddings = tf.expand_dims(embeddings, 1)# shape=(12765,1,8)

            h_e = tf.nn.embedding_lookup(embeddings, h)
            t_e = tf.nn.embedding_lookup(embeddings, t)

                # relation embeddings: batch_size * kge_dim

            r_e = tf.nn.embedding_lookup(all_weights['relation_embed'], r)

                # relation transform weights: batch_size * kge_dim * emb_dim
            trans_M = tf.nn.embedding_lookup(all_weights['trans_W'], r)

                # batch_size * 1 * kge_dim -> batch_size * kge_dim
            h_e = tf.reshape(tf.matmul(h_e, trans_M), [-1, dim])
            t_e = tf.reshape(tf.matmul(t_e, trans_M), [-1, dim])

                # l2-normalize
                # h_e = tf.math.l2_normalize(h_e, axis=1)
                # r_e = tf.math.l2_normalize(r_e, axis=1)
                # t_e = tf.math.l2_normalize(t_e, axis=1)

            kg_score = tf.reduce_sum(tf.multiply(t_e, tf.tanh(h_e + r_e)), 1)

            return kg_score

        if step==0:
            self.h = tf.placeholder(tf.int32, shape=[None], name='h')
            self.r = tf.placeholder(tf.int32, shape=[None], name='r')
            self.pos_t = tf.placeholder(tf.int32, shape=[None], name='pos_t')


            self.A_kg_score = _generate_transE_score(h=self.h, t=self.pos_t, r=self.r)

            def _reorder_list(org_list, order):
                new_list = np.array(org_list)
                new_list = new_list[order]
                return new_list

            all_h_list, all_t_list, all_r_list = [], [], []
            all_v_list = []

            for l_id, lap in enumerate(self.lap_list):
                all_h_list += list(lap.row)
                all_t_list += list(lap.col)
                all_v_list += list(lap.data)
                all_r_list += [self.adj_r_list[l_id]] * len(lap.row)

            assert len(all_h_list) == sum([len(lap.data) for lap in self.lap_list])

                # resort the all_h/t/r/v_list,
                # ... since tensorflow.sparse.softmax requires indices sorted in the canonical lexicographic order
            # print('\t重新排序目录...')
            org_h_dict = dict()

            for idx, h in enumerate(all_h_list):
                if h not in org_h_dict.keys():
                    org_h_dict[h] = [[],[],[]]

                org_h_dict[h][0].append(all_t_list[idx])
                org_h_dict[h][1].append(all_r_list[idx])
                org_h_dict[h][2].append(all_v_list[idx])
            # print('\t重新组织所有KG数据完成.')

            sorted_h_dict = dict()
            for h in org_h_dict.keys():
                org_t_list, org_r_list, org_v_list = org_h_dict[h]
                sort_t_list = np.array(org_t_list)
                sort_order = np.argsort(sort_t_list)

                sort_t_list = _reorder_list(org_t_list, sort_order)
                sort_r_list = _reorder_list(org_r_list, sort_order)
                sort_v_list = _reorder_list(org_v_list, sort_order)

                sorted_h_dict[h] = [sort_t_list, sort_r_list, sort_v_list]
            # print('\t完成元数据排序.')

            od = collections.OrderedDict(sorted(sorted_h_dict.items()))
            self.new_h_list, self.new_t_list, self.new_r_list, self.new_v_list = [], [], [], []

            for h, vals in od.items():
                self.new_h_list += [h] * len(vals[0])
                self.new_t_list += list(vals[0])
                self.new_r_list += list(vals[1])
                self.new_v_list += list(vals[2])


            assert sum(self.new_h_list) == sum(all_h_list)
            assert sum(self.new_t_list) == sum(all_t_list)
            assert sum(self.new_r_list) == sum(all_r_list)
                # try:
                #     assert sum(new_v_list) == sum(all_v_list)
                # except Exception:
                #     print(sum(new_v_list), '\n')
                #     print(sum(all_v_list), '\n')
            # print('\t完成所有数据排序.')
            self.A_values = tf.placeholder(tf.float32, shape=[len(self.new_v_list)], name='A_values')
        #print('开始KGAT中的update_attentive_A')
        fold_len = len(self.new_h_list) // 100
        kg_score = []
        with tf.Session() as sess:
            sess.run(tf.global_variables_initializer())

            for i_fold in range(100):
                start = i_fold * fold_len
                if i_fold == 99:
                    end = len(self.new_h_list)
                else:
                    end = (i_fold + 1) * fold_len

                feed_dict = {
                    self.h: self.new_h_list[start:end],
                    self.r: self.new_r_list[start:end],
                    self.pos_t: self.new_t_list[start:end]
                }
                A_kg_score = sess.run(self.A_kg_score, feed_dict=feed_dict)
                kg_score += list(A_kg_score)

            kg_score = np.array(kg_score)

            A_out= _create_attentive_A_out(self)

            new_A = sess.run(A_out, feed_dict={self.A_values: kg_score})
            new_A_values = new_A.values
            new_A_indices = new_A.indices

            rows = new_A_indices[:, 0]
            cols = new_A_indices[:, 1]
            self.A = sp.coo_matrix((new_A_values, (rows, cols)), shape=(n_user + n_entity,n_user + n_entity))