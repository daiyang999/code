import argparse
import warnings
 
warnings.filterwarnings('ignore')
import numpy as np
from data_loader import load_data
from train import train
import os

os.environ["CUDA_VISIBLE_DEVICES"] = "0" 


np.random.seed(555)

# 创建一个解析器dkn改
parser = argparse.ArgumentParser()


# movie
parser.add_argument('--dataset', type=str, default='movie', help='which dataset to use')
parser.add_argument('--n_epochs', type=int, default=20, help='the number of epochs')
parser.add_argument('--dim', type=int, default=512, help='dimension of user and entity embeddings')
parser.add_argument('--L', type=int, default=4, help='number of low layers')
parser.add_argument('--H', type=int, default=2, help='number of high layers')
parser.add_argument('--batch_size', type=int, default=1024, help='batch size')
parser.add_argument('--l2_weight', type=float, default=1e-6, help='weight of l2 regularization')
parser.add_argument('--lr_rs', type=float, default=0.001, help='learning rate of RS task')
parser.add_argument('--lr_kge', type=float, default=0.0002, help='learning rate of KGE task')
parser.add_argument('--kge_interval', type=int, default=3, help='training interval of KGE task')
parser.add_argument('--n_memory', type=int, default=16, help='size of ripple set for each hop')
parser.add_argument('--p_hop', type=int, default=1, help='mix hop')
parser.add_argument('--neighbor_sample_size', type=int, default=8, help='the number of neighbors to be sampled')
parser.add_argument('--h_hop', type=int, default=3, help='number of iterations when computing entity representation')
parser.add_argument('--n_mix_hop', type=int, default=2, help='mix hop')


'''
# book
parser.add_argument('--dataset', type=str, default='book', help='which dataset to use')
parser.add_argument('--n_epochs', type=int, default=20, help='the number of epochs')
parser.add_argument('--dim', type=int, default=256, help='dimension of user and entity embeddings')
parser.add_argument('--L', type=int, default=1, help='number of low layers')
parser.add_argument('--H', type=int, default=2, help='number of high layers')
parser.add_argument('--batch_size', type=int, default=64, help='batch size')
parser.add_argument('--l2_weight', type=float, default=1e-6, help='weight of l2 regularization')
parser.add_argument('--lr_rs', type=float, default=2e-4, help='learning rate of RS task')
parser.add_argument('--lr_kge', type=float, default=2e-5, help='learning rate of KGE task')
parser.add_argument('--kge_interval', type=int, default=2, help='training interval of KGE task')
parser.add_argument('--n_memory', type=int, default=16, help='size of ripple set for each hop')
parser.add_argument('--p_hop', type=int, default=1, help='mix hop')
parser.add_argument('--neighbor_sample_size', type=int, default=8, help='the number of neighbors to be sampled')
parser.add_argument('--h_hop', type=int, default=3, help='number of iterations when computing entity representation')
parser.add_argument('--n_mix_hop', type=int, default=2, help='mix hop')
'''

'''
# music
parser.add_argument('--dataset', type=str, default='music', help='which dataset to use')
parser.add_argument('--n_epochs', type=int, default=9, help='the number of epochs')
parser.add_argument('--dim', type=int, default=256, help='dimension of user and entity embeddings')
parser.add_argument('--L', type=int, default=2, help='number of low layers')
parser.add_argument('--H', type=int, default=1, help='number of high layers')
parser.add_argument('--batch_size', type=int, default=128, help='批量大小')
parser.add_argument('--l2_weight', type=float, default=1e-6, help='l2正则化的权重')
parser.add_argument('--lr_rs', type=float, default=1e-3, help='learning rate of RS task')
parser.add_argument('--lr_kge', type=float, default=2e-4, help='learning rate of KGE task')
parser.add_argument('--kge_interval', type=int, default=3, help='KGE任务的训练间隔')
parser.add_argument('--n_memory', type=int, default=16, help='size of ripple set for each hop')
parser.add_argument('--p_hop', type=int, default=1, help='mix hop')
parser.add_argument('--neighbor_sample_size', type=int, default=8, help='the number of neighbors to be sampled')
parser.add_argument('--h_hop', type=int, default=3, help='number of iterations when computing entity representation')
parser.add_argument('--n_mix_hop', type=int, default=2, help='mix hop')
'''

show_loss = False
show_topk = True

# args = parser.parse_args()
args = parser.parse_args(args=[])
data = load_data(args)
print('dataset: %s    dim: %.1f  L: %.1f    H: %.1f    batch_size: %.1f     kge_interval: %.1f'
                  % (args.dataset, args.dim, args.L, args.H, args.batch_size,args.kge_interval))
train(args, data, show_loss, show_topk)



# 解析参数，检查命令行，把每个参数转换为适当的类型然后调用相应的操作
# args = parser.parse_args()
# data = load_data(args)
# args.n_memory=16
# args.p_hop=1
# args.neighbor_sample_size=8
# args.h_hop=3
# args.n_mix_hop=2
# for args.dataset in ['movie','book','music']:
#     if args.dataset=='movie':
#         args.l2_weight=1e-6
#         args.lr_rs=0.001
#         args.lr_kge=0.0002
#         args.kge_interval=3
#         args.n_epochs=5
#     elif args.dataset=='book':
#         args.l2_weight=1e-6
#         args.lr_rs=2e-4
#         args.lr_kge=2e-5
#         args.kge_interval=2
#         args.n_epochs=5
#     else:
#         args.l2_weight=1e-6
#         args.lr_rs=1e-3
#         args.lr_kge=2e-4
#         args.kge_interval=3
#         args.n_epochs=6
#     for args.batch_size in [1024,512,256,128,64,32,16,8]:
#         for args.L in [1,2,3,4,5,6,7,8]:
#             for args.H in [1,2,3,4,5]:
#                 for args.dim in [16,32,64,128,256,512]:
#                     print('dataset: %s    dim: %.1f  L: %.1f    H: %.1f    batch_size: %.1f     kge_interval: %.1f'
#                   % (args.dataset, args.dim, args.L, args.H, args.batch_size,args.kge_interval))
#                     train(args, data, show_loss, show_topk)
