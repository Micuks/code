import torch
import logging

# logger settings
logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)

con_handler = logging.StreamHandler()
con_handler.setLevel(logging.DEBUG)

formatter = logging.Formatter(
        "%(asctime)s [%(levelname)s] %(name)s L%(lineno)d: %(message)s",
        datefmt="%Y-%m-%DT%H:%M:%S",
        style="%"
        )

con_handler.setFormatter(formatter)
logger.addHandler(con_handler)

x = torch.linspace(0, 100, 100).type(torch.FloatTensor)
rand = torch.randn(100) * 10
y = x + rand
x_train = x[:-10]  # 取出倒数第10个元素之前的所有元素，从0到89号
x_test = x[-10:]  # 取出倒数10个数，从90到99
y_train = y[:-10]
y_test = y[-10:]
a = torch.rand(1, requires_grad=True)
b = torch.rand(1, requires_grad=True)
logger.info(f"a={a}, b={b}")
logger.info(f"a.expand_as(x_train)={a.expand_as(x_train)}, \
            b.expand_as(x_train)={b.expand_as(y_train)}")
learning_rate = 0.0001

for i in range(1000):
    # 计算在当前a、b条件下的模型预测值
    predictions = a.expand_as(x_train) * x_train + b.expand_as(x_train)
    # 将所有训练数据带入模型ax+b,计算每个预测值。这里x_train和predictions都是(90,1)的张量
    # expand_as的作用是扩展a、b维度与x_train一致
    loss = torch.mean((predictions - y_train) ** 2)  # 通过与标签数据y比较计算误差，loss是一个标量
    logger.debug("loss:{}".format(loss))
    loss.backward()  # 对损失函数求导进行梯度反传
    # 利用上一步计算得到的a的梯度更新a的data数值
    a.data.add_(-learning_rate * a.grad.data)
    # 利用上一步计算得到的b的梯度更新b的data数值
    b.data.add_(-learning_rate * b.grad.data)
    # 增加这部分代码，清空存储在变量a、b中的梯度信息，以免在backward的过程中反复不停地累加
    a.grad.data.zero_()  # 清空a的梯度数值
    b.grad.data.zero_()  # 清空b的梯度数值

import matplotlib.pyplot as plt
import numpy as np

plt.rcParams["font.sans-serif"] = ["Songti SC"]
plt.rcParams["axes.unicode_minus"] = False
x_data = x_train.data.numpy()  # 将x中的数据转换为Numpy数组
fig, (ax1, ax2) = plt.subplots(1,2, figsize=(15,6))
# #绘制xh和y的散点图
xplot, = ax1.plot(x_data, y_train.data.numpy(), "o")
# 绘制出拟合直线
yplot, = ax1.plot(x_data, a.data.numpy() * x_data + b.data.numpy())
predictions = a.expand_as(x_test) * x_test + b.expand_as(x_test)  # 计算模型预测结果
plt.xlabel("月份")
ax1.set_xlabel("月份")
ax1.set_ylabel("房价")
ax1.set_title("训练集数据")
ax1.legend([xplot, yplot], ["Data", "Y_train" ])  # 绘制图例
# 获得包裹的测试数据的自变量
x_pred = x_test.data.numpy()
ax2.plot(x_data, y_train.data.numpy(), "o")  # 绘制训练数据
ytest_plot, = ax2.plot(x_pred, y_test.data.numpy(), "s")  # 绘制测试数据
x_data = np.r_[x_data, x_test.data.numpy()]
# 绘制拟合数据
ax2.plot(x_data, a.data.numpy() * x_data + b.data.numpy())
# 绘制预测数据
yhat_plot, = ax2.plot(x_pred, a.data.numpy() * x_pred + b.data.numpy(), "o")
ax2.set_title("训练集和测试集数据")
ax2.set_xlabel("月份")
ax2.set_ylabel("房价")
str1 = str(a.data.numpy()[0]) + "x+" + str(b.data.numpy()[0])
ax2.legend([xplot, yplot, ytest_plot, yhat_plot], ["Data", str1, "Y_test",
                                                   "Y_test_hat"])  # 绘制图例
plt.show()  # 绘制图形
