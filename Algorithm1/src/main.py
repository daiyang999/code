import argparse
import numpy as np
from data_loader import load_data
from train import train

np.random.seed(555)

# 创建一个解析器
parser = argparse.ArgumentParser()
'''
# movie
parser.add_argument('--dataset', type=str, default='movie', help='which dataset to use')
parser.add_argument('--n_epochs', type=int, default=10, help='the number of epochs')
parser.add_argument('--dim', type=int, default=16, help='dimension of user and entity embeddings')
parser.add_argument('--L', type=int, default=1, help='number of low layers')
parser.add_argument('--H', type=int, default=1, help='number of high layers')
parser.add_argument('--batch_size', type=int, default=4096, help='batch size')
parser.add_argument('--l2_weight', type=float, default=1e-6, help='weight of l2 regularization')
parser.add_argument('--lr_rs', type=float, default=0.02, help='learning rate of RS task')
parser.add_argument('--lr_kge', type=float, default=0.01, help='learning rate of KGE task')
parser.add_argument('--kge_interval', type=int, default=2, help='training interval of KGE task')


'''

# book
parser.add_argument('--dataset', type=str, default='book', help='which dataset to use')
parser.add_argument('--n_epochs', type=int, default=10, help='the number of epochs')
parser.add_argument('--dim', type=int, default=128, help='dimension of user and entity embeddings')
parser.add_argument('--L', type=int, default=1, help='number of low layers')
parser.add_argument('--H', type=int, default=1, help='number of high layers')
parser.add_argument('--batch_size', type=int, default=16, help='batch size')
parser.add_argument('--l2_weight', type=float, default=1e-6, help='weight of l2 regularization')
parser.add_argument('--lr_rs', type=float, default=2e-4, help='learning rate of RS task')
parser.add_argument('--lr_kge', type=float, default=2e-5, help='learning rate of KGE task')
parser.add_argument('--kge_interval', type=int, default=2, help='training interval of KGE task')

'''
# music
parser.add_argument('--dataset', type=str, default='music', help='which dataset to use')
parser.add_argument('--n_epochs', type=int, default=10, help='the number of epochs')
parser.add_argument('--dim', type=int, default=256, help='dimension of user and entity embeddings')
parser.add_argument('--L', type=int, default=2, help='number of low layers')
parser.add_argument('--H', type=int, default=1, help='number of high layers')
parser.add_argument('--batch_size', type=int, default=128, help='批量大小')
parser.add_argument('--l2_weight', type=float, default=1e-6, help='l2正则化的权重')
parser.add_argument('--lr_rs', type=float, default=1e-3, help='learning rate of RS task')
parser.add_argument('--lr_kge', type=float, default=2e-4, help='learning rate of KGE task')
parser.add_argument('--kge_interval', type=int, default=2, help='KGE任务的训练间隔')
'''

show_loss = False
show_topk = True

# 解析参数，检查命令行，把每个参数转换为适当的类型然后调用相应的操作
args = parser.parse_args()
data = load_data(args)
train(args, data, show_loss, show_topk)
