import warnings
 
warnings.filterwarnings('ignore')
import os
os.environ['TF_CPP_MIN_LOG_LEVEL']='2'
import tensorflow._api.v2.compat.v1 as tf

tf.disable_v2_behavior()
import numpy as np
from tqdm import tqdm
from model import MKR


def train(args, data, show_loss, show_topk):
    tf.reset_default_graph()
    n_user, n_item, n_entity, n_relation, = data[0], data[1], data[2], data[3]
    train_data, eval_data, test_data= data[4], data[5], data[6]
    kg, adj_entity, adj_relation, kg1= data[7], data[8], data[9], data[10]

    file1 = '../txt/' + args.dataset + '+'+str(args.dim)+ '+' +str(args.L) + '+'+str(args.H)+ '+' +str(args.batch_size)+ '+' +str(args.kge_interval) + '.txt'
    f=open(file1,'w')

    #print('构建MKR模型')
    model = MKR(args, n_user, n_item, n_entity, n_relation, adj_entity, adj_relation)

    # 设置top-K 评估
    user_num = 100
    k_list = [2, 5, 10, 20, 50]
    train_record = get_user_record(train_data, True)
    test_record = get_user_record(test_data, False)
    user_list = list(set(train_record.keys()) & set(test_record.keys()))
    #print('随机选择user_num个数据进入user_list中')
    if len(user_list) > user_num:
        user_list = np.random.choice(user_list, size=user_num, replace=False)
    item_set = set(list(range(n_item)))

    with tf.Session() as sess:
        # 训练自己的神经网络时初始化模型的参数
        sess.run(tf.global_variables_initializer())
        for step in range(args.n_epochs):
            # RS training
            # shuffle函数将序列的所有元素随机排序
            np.random.shuffle(train_data)
            start = 0
            while start < train_data.shape[0]:# <452264
                # 452264/4096=110.416次循环
                #          MKR(args, n_user, n_item, n_entity, n_relation),train_data,start,start+4096
                _, loss = model.train_rs(sess, get_feed_dict_for_rs(model, train_data, start, start + args.batch_size))
                start += args.batch_size
                # if show_loss:
                #     print('loss:',loss)

            # KGE training
            if step % args.kge_interval == 0:
                np.random.shuffle(kg1)
                start = 0
                while start < kg1.shape[0]:
                    _, rmse = model.train_kge(sess, get_feed_dict_for_kge(model, kg1, start, start + args.batch_size))
                    start += args.batch_size
                    if show_loss:
                        print('均方根误差rmse:',rmse)

            model.update_attentive_A(sess,args,n_user,n_entity,step)

            # CTR evaluation
            train_auc, train_acc = model.eval(sess, get_feed_dict_for_rs(model, train_data, 0, train_data.shape[0]))
            eval_auc, eval_acc = model.eval(sess, get_feed_dict_for_rs(model, eval_data, 0, eval_data.shape[0]))
            test_auc, test_acc = model.eval(sess, get_feed_dict_for_rs(model, test_data, 0, test_data.shape[0]))

            print('epoch %d    train auc: %.4f  acc: %.4f    eval auc: %.4f  acc: %.4f    test auc: %.4f  acc: %.4f'
                  % (step, train_auc, train_acc, eval_auc, eval_acc, test_auc, test_acc))

            print('epoch %d    train auc: %.4f  acc: %.4f    eval auc: %.4f  acc: %.4f    test auc: %.4f  acc: %.4f'
                  % (step, train_auc, train_acc, eval_auc, eval_acc, test_auc, test_acc),file=f)

            # top-K evaluation
            if show_topk:
                # topk_eval(model,100个重复用户，dict{},dict{},2347个item，[1, 2, 5, 10, 20, 50, 100])
                precision, recall, f1 = topk_eval(
                    sess, model, user_list, train_record, test_record, item_set, k_list)
                print('precision: ', end='')
                print('precision: ', end='',file=f)
                for i in precision:
                    print('%.4f\t' % i, end='',file=f)
                    print('%.4f\t' % i, end='')
                print()
                print('recall: ', end='',file=f)
                print('recall: ', end='')
                for i in recall:
                    print('%.4f\t' % i, end='',file=f)
                    print('%.4f\t' % i, end='')
                print()
                print('f1: ', end='',file=f)
                print('f1: ', end='')
                for i in f1:
                    print('%.4f\t' % i, end='',file=f)
                    print('%.4f\t' % i, end='')
                print('\n',file=f)
                print('\n')
    f.close()

#MKR(args, n_user, n_item, n_entity, n_relation),   train_data,   start,   start+4096  
def get_feed_dict_for_rs(model, data, start, end):
    feed_dict = {model.user_indices: data[start:end, 0],# （4096*1）
                 model.item_indices: data[start:end, 1],
                 model.labels: data[start:end, 2],
                 model.head_indices: data[start:end, 1]}
    return feed_dict


def get_feed_dict_for_kge(model, kg, start, end):
    feed_dict = {model.item_indices: kg[start:end, 0],
                 model.head_indices: kg[start:end, 0],
                 model.relation_indices: kg[start:end, 1],
                 model.tail_indices: kg[start:end, 2]}
    return feed_dict

# topk_eval(model,         100个重复用户，dict{},    dict{},      2347个item，[1, 2, 5, 10, 20, 50, 100])
def topk_eval(sess, model, user_list, train_record, test_record, item_set, k_list):
    precision_list = {k: [] for k in k_list}
    recall_list = {k: [] for k in k_list}

    for user in user_list:
        test_item_list = list(item_set - train_record[user])
        item_score_map = dict()
        items, scores = model.get_scores(sess, {model.user_indices: [user] * len(test_item_list),
                                                model.item_indices: test_item_list,
                                                model.head_indices: test_item_list})
        for item, score in zip(items, scores):
            item_score_map[item] = score
        item_score_pair_sorted = sorted(item_score_map.items(), key=lambda x: x[1], reverse=True)
        item_sorted = [i[0] for i in item_score_pair_sorted]

        for k in k_list:
            hit_num = len(set(item_sorted[:k]) & test_record[user])
            precision_list[k].append(hit_num / k)
            recall_list[k].append(hit_num / len(test_record[user]))

    # 准确率、召回率、F1值
    precision = [np.mean(precision_list[k]) for k in k_list]
    recall = [np.mean(recall_list[k]) for k in k_list]
    f1 = [2 / (1 / precision[i] + 1 / recall[i]) for i in range(len(k_list))]

    return precision, recall, f1


def get_user_record(data, is_train):
    #print('得到用户记录：是否训练过：',is_train)
    user_history_dict = dict()
    for interaction in data:
        user = interaction[0]
        item = interaction[1]
        label = interaction[2]
        if is_train or label == 1:
            if user not in user_history_dict:
                user_history_dict[user] = set()
            user_history_dict[user].add(item)
    return user_history_dict

