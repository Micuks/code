import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.sans-serif"] = "Songti SC"
plt.rcParams["axes.unicode_minus"] = False
fileName = "./hour.csv"
df = pd.read_csv(fileName, usecols=["cnt"])
df1 = df[:50]
import torch

# 输入变量：1,2,3,...这样的一维数组
x = torch.FloatTensor(np.arange(df1.shape[0], dtype=float) / df1.shape[0])
# 输出变量，是从单车使用量数据中得到的每一时刻的单车量，
# 共50个数据点的一维数组，作为标准答案
y = torch.FloatTensor(np.array(df1["cnt"], dtype=float))
sz = 10  # 设置隐含神经元数量
# 初始化输入层到隐含层的权重矩阵，尺寸是(1,10)
weights = torch.randn((1, sz), requires_grad=True)
# 初始化隐含层节点的偏置向量，是尺寸为10的一维向量
biases = torch.randn((sz), requires_grad=True)
# 初始化从隐含层到输出层的权重矩阵，尺寸为(10,1)
weights2 = torch.randn((sz, 1), requires_grad=True)

##迭代训练神经网络
learningRate = 0.001  # 设置学习率
losses = []  # 该数组记录每一次迭代的损失函数值，以方便后续绘图
x = x.view(50, -1)
y = y.view(50, -1)
for i in range(100000):  # 训练10万次
    # 从输入层到隐含层的计算
    hidden = x * weights + biases
    # 此时，hidden变量的尺寸是(50,10),即50个数据点，10个隐含神经元
    # 将sigmoid函数应用在隐含层每个神经元
    hidden = torch.sigmoid(hidden)
    # 隐含层输出到输出层，计算得到最终预测值
    predictions = hidden.mm(weights2)
    # 此时，predictions的尺寸为（50,1），即50个点的预测
    # 通过与数据中的标准答案y做对比，计算均方误差
    loss = torch.mean((predictions - y) ** 2)
    # 此时，loss为一个标量，即一个数
    losses.append(loss.data.numpy())
    if i % 10000 == 0:  # 每隔10000次打印一下损失函数
        print("loss:", loss)

    # ********************************
    # 接下来执行梯度下降算法，将误差反向传播
    loss.backward()  # 对损失函数进行梯度反传

    # 利用上一步计算得到的weights、biases等梯度信息更新weights和biases
    weights.data.add_(-learningRate * weights.grad.data)
    biases.data.add_(-learningRate * biases.grad.data)
    weights2.data.add_(-learningRate * weights2.grad.data)

    # 清空所有变量的梯度
    weights.grad.data.zero_()
    biases.grad.data.zero_()
    weights2.grad.data.zero_()

x_data = x.data.numpy()  # 获得x包裹的数据
plt.figure(figsize=(10, 7))
(xplot,) = plt.plot(x_data, y.data.numpy(), "o")  # 绘制原始数据
(yplot,) = plt.plot(x_data, predictions.data.numpy())  # 绘制拟合数据
plt.xlabel("X", fontsize=16)
plt.ylabel("Y", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend([xplot, yplot], ["原始数据", "100000此训练后得到的预测值"])  # 绘制图例
plt.show()
