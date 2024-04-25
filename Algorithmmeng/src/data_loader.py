import numpy as np
import os


def load_data(args):
    n_user, n_item, train_data, eval_data, test_data  = load_rating(args)
    n_entity, n_relation, kg = load_kg(args)
    #print('data loaded.')
    # print('n_user:',n_user)
    # print('n_item:',n_item)
    # print('n_entity:',n_entity)
    # print('n_relation:',n_relation)

    return n_user, n_item, n_entity, n_relation, train_data, eval_data, test_data, kg


def load_rating(args):

    # reading rating file
    rating_file = '../data/' + args.dataset + '/ratings_final'
    #print('读取评分文件 ...'+rating_file)
    if os.path.exists(rating_file + '.npy'):
        rating_np = np.load(rating_file + '.npy')
    else:
        rating_np = np.loadtxt(rating_file + '.txt', dtype=np.int32)
        np.save(rating_file + '.npy', rating_np)

    # set函数统计不重复的个数
    n_user = len(set(rating_np[:, 0]))
    n_item = len(set(rating_np[:, 1]))

    train_data, eval_data, test_data = dataset_split(rating_np)

    return n_user, n_item, train_data, eval_data, test_data


def dataset_split(rating_np):
    # 分割数据集
    #print('分割数据集 ...')

    # 训练、评估、测试
    # train:eval:test = 6:2:2
    eval_ratio = 0.2
    test_ratio = 0.2
    n_ratings = rating_np.shape[0] # 读取矩阵第一维的长度

    # 选定评估集
    eval_indices = np.random.choice(list(range(n_ratings)), size=int(n_ratings * eval_ratio), replace=False)
    left = set(range(n_ratings)) - set(eval_indices)
    # 选定测试集
    test_indices = np.random.choice(list(left), size=int(n_ratings * test_ratio), replace=False)
    # 剩下的为训练集
    # train_indices = list(left - set(test_indices))
    train_indices = np.random.choice(list(left - set(test_indices)), size=int(len(list(left - set(test_indices)))*1.0), replace=False)

    train_data = rating_np[train_indices]
    eval_data = rating_np[eval_indices]
    test_data = rating_np[test_indices]

    return train_data, eval_data, test_data


def load_kg(args):

    # reading kg file
    kg_file = '../data/' + args.dataset + '/kg_final'
    #print('读取kg文件 ...'+kg_file)
    if os.path.exists(kg_file + '.npy'):
        kg1 = np.load(kg_file + '.npy')
    else:
        kg1 = np.loadtxt(kg_file + '.txt', dtype=np.int32)
        np.save(kg_file + '.npy', kg1)

    n_entity = len(set(kg1[:, 0]) | set(kg1[:, 2]))
    n_relation = len(set(kg1[:, 1]))

    # kg, enti, rela = construct_kg(args,kg1)

    # adj_entity, adj_relation = construct_adj(args, kg, n_entity)

    return n_entity, n_relation, kg1

# def construct_kg(args,kg_np):
#     print('constructing knowledge graph ...')
#     kg = dict()
#     enti = 0
#     rela = 0
#     for triple in kg_np:
#         head = triple[0]
#         relation = triple[1]
#         tail = triple[2]
#         # treat the KG as an undirected graph
#         if head not in kg:
#             kg[head] = []
#         kg[head].append((tail, relation))
#         if tail not in kg:
#             kg[tail] = []
#         kg[tail].append((head, relation))

#         enti = max(enti, head, tail)
#         rela = max(rela, relation)
#     return kg, enti, rela


# def construct_adj(args, kg, entity_num, random_seed = 1):
#     adj_entity, adj_relation = contruct_random_adj(args,kg,entity_num)
#     return adj_entity, adj_relation

# def contruct_random_adj(args,kg,entity_num):

#     adj_entity = np.zeros([entity_num, args.neighbor_sample_size], dtype=np.int64)
#     adj_relation = np.zeros([entity_num, args.neighbor_sample_size], dtype=np.int64)
#     for entity in range(entity_num):
#         if entity in kg:
#             neighbors = kg[entity]
#             n_neighbors = len(neighbors)
#             if n_neighbors >= args.neighbor_sample_size: sampled_indices = np.random.choice(list(range(n_neighbors)), size=args.neighbor_sample_size, replace=False)
#             else: sampled_indices = np.random.choice(list(range(n_neighbors)), size=args.neighbor_sample_size, replace=True)
#             adj_entity[entity] = np.array([neighbors[i][0] for i in sampled_indices])
#             adj_relation[entity] = np.array([neighbors[i][1] for i in sampled_indices])

#     return adj_entity, adj_relation