import pandas as pd
import numpy as np

filename = "./hour.csv"
rides = pd.read_csv(filename)
# 所有类型编码变量的名称
dummy_fields = ["season", "weathersit", "mnth", "hr", "weekday"]
for each in dummy_fields:
    # 取出所有类型变量，并将它们转变为独热编码
    dummies = pd.get_dummies(rides[each], prefix=each, drop_first=False)
    # 将新的独热编码变量与原有的所有变量合并在一起
    rides = pd.concat([rides, dummies], axis=1)

# 将原来的类型变量从数据表中删除
fields_to_drop = [
    "instant",
    "dteday",
    "season",
    "weathersit",
    "weekday",
    "atemp",
    "mnth",
    "workingday",
    "hr",
]
data = rides.drop(fields_to_drop, axis=1)
# 数值类型变量名称
quant_features = ["cnt", "temp", "hum", "windspeed"]
scaled_features = {}  # 将每个变量的均值和方差都存到scaled_features变量中
for each in quant_features:
    # 计算这些变量的均值和方差
    mean, std = data[each].mean(), data[each].std()
    scaled_features[each] = [mean, std]
    # 对每个变量进行标准化
    data.loc[:, each] = (data[each] - mean) / std
# print(data[quant_features].head())

############################数据集划分###############################
test_data = data[-21 * 24 :]  # 选出训练集,21天24小时的数据
train_data = data[: -21 * 24]  # 剩下的数据
# 目标列包含的字段
target_fields = ["cnt", "casual", "registered"]
# 将训练集划分为特征变量列和目标特征列
features, targets = train_data.drop(target_fields, axis=1), train_data[target_fields]
# 将测试集划分成特征变量列和目标特征列
test_features, test_targets = (
    test_data.drop(target_fields, axis=1),
    test_data[target_fields],
)
# 将数据类型转换为Numpy数组
X = features.values  # 将数据从pandas dataframe转换为Numpy数组
Y = targets["cnt"].values
Y = Y.astype(float)
Y = np.reshape(Y, [len(Y), 1])
losses = []

##################构建神经网络######################
import torch

# 定义神经网络架构，features.shape[1]个输入单元，10个隐含单元，1个输出单元
input_size = features.shape[1]
hidden_size = 10
output_size = 1
batch_size = 128
neu = torch.nn.Sequential(
    torch.nn.Linear(input_size, hidden_size),
    torch.nn.Sigmoid(),
    torch.nn.Linear(hidden_size, output_size),
)  ##这是一个函数闭包
cost = torch.nn.MSELoss()
optimizer = torch.optim.SGD(neu.parameters(), lr=0.01)

####################采用批处理后的循环代码##################
# 神经网络训练循环
losses = []
for i in range(1000):
    # 每128个样本点划分为一批，在循环时一批一批读取
    batch_loss = []
    # start和end分别是提取一批数据的起始下标和终止下标
    for start in range(0, len(X), batch_size):
        end = start + batch_size if start + batch_size < len(X) else len(X)
        xx = torch.FloatTensor(X[start:end])
        yy = torch.FloatTensor(Y[start:end])
        predict = neu(xx)
        loss = cost(predict, yy)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        batch_loss.append(loss.data.numpy())

    if i % 100 == 0:
        losses.append(np.mean(batch_loss))
        print(i, np.mean(batch_loss))

# ############画出单车预测器的训练曲线###############
import matplotlib.pyplot as plt

plt.rcParams["font.sans-serif"] = "Songti SC"
plt.rcParams["axes.unicode_minus"] = False
# #打印输出损失值
# plt.plot(np.arange(len(losses))*100, losses, "o-")
# plt.xlabel("epoch")
# plt.ylabel("MSE")
# plt.show()
############################测试神经网络###########################
# 读取测试集的cnt数据
targets = test_targets["cnt"]
# 将数据转换成合适的张量形式
targets = targets.values.reshape([len(targets), 1])
# 保证数据为实数
targets = targets.astype(float)
x = torch.FloatTensor(test_features.values)
y = torch.FloatTensor(targets)
# 用神经网络进行预测
predict = neu(x)
predict = predict.data.numpy()
fig, ax = plt.subplots(figsize=(10, 7))
mean, std = scaled_features["cnt"]
ax.plot(predict * std + mean, "--", label="预测值")
ax.plot(targets * std + mean, label="数据")
ax.legend()
ax.set_xlabel("日期——时间", fontsize=16)
ax.set_ylabel("单车使用量", fontsize=16)
dates = pd.to_datetime(rides.loc[test_data.index]["dteday"])
dates = dates.apply(lambda d: d.strftime("%b %d"))
ax.set_xticks(np.arange(len(dates))[12::24])
_ = ax.set_xticklabels(dates[12::24], rotation=45)
plt.show()
