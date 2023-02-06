import logging

import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F

import torchvision.datasets as dsets
import torchvision.transforms as transforms

import matplotlib.pyplot as plt
import numpy as np

# Logger settings
logger = logging.getLogger("MNISTCNN")
logger.setLevel(logging.DEBUG)

formatter = logging.Formatter(
        "%(asctime)s [%(levelname)s] %(name)s %(lineno)s: %(message)s")
con_handler = logging.StreamHandler()
con_handler.setLevel(logging.DEBUG)
con_handler.setFormatter(formatter)

logger.addHandler(con_handler)

# Pyplot configuration
plt.rcParams['font.sans-serif']=['Songti SC']
plt.rcParams['axes.unicode_minus']=False

device = ("mps" if torch.backends.mps.is_available() else "cuda" if
    torch.cuda.is_available() else "cpu")

# Hyperparameters
image_size=28
num_classes=10
num_epochs=20
batch_size = 64

# Load MNIST data
data_path = "./data"
train_dataset = dsets.MNIST(root=data_path, train=True, # Extract training set
                            transform=transforms.ToTensor(), # Transform images
                            # to vectors, preprocess images
                            download=True # Auto download if dataset not found.
                            )
test_dataset = dsets.MNIST(root=data_path,
                           train=False,
                           transform=transforms.ToTensor()
                           )
# Training set data loader, auto split data into batches and shuffle data.
train_loader = torch.utils.data.DataLoader(dataset=train_dataset,
                                           batch_size=batch_size,
                                           shuffle=True)

# Split testing data into two parts, one as validating data, the other as testing
# data. validating data is used to check whether model is over-fitting, and
# update hyperparameters. Testing data is used to check the whole model's
# function.
indices = range(len(test_dataset))
indices_val = indices[:5000]
indices_test = indices[5000:]
# Construct SubsetRandomSampler for two datasets according indices.
# This will sample indices.
sampler_val = torch.utils.data.sampler.SubsetRandomSampler(indices_val)
sampler_test = torch.utils.data.sampler.SubsetRandomSampler(indices_test)
# Define loader according sampler
val_loader = torch.utils.data.DataLoader(dataset=test_dataset,
                                         batch_size=batch_size,
                                         shuffle=False,
                                         sampler=sampler_val)
test_loader=torch.utils.data.DataLoader(dataset=test_dataset,
                                        batch_size=batch_size,
                                        shuffle=False,
                                        sampler=sampler_test)

# Index data and plot diagrams.
# Select random image from dataset and plot.
idx = 576
muteimg = train_dataset[idx][0].numpy()
# Default images have RGB three channels, but MNIST dataset only have greyscale
# images, so ignore channels.
plt.imshow(muteimg[0,...])
plt.show()
logger.info("Label: {}".format(train_dataset[idx][1]))

# Define CNN
depth = [4, 8] # depth of convolutional cores
class ConvNet(nn.Module):
    def __init__(self):
        super(ConvNet, self).__init__()
        # Convolutional layer1, 
        # input_channels=1, output_channels=4, window_size=5, padding=2
        # padding of 2 remains width and height of image with window_size=5
        self.conv1 = nn.Conv2d(1,4,5,padding=2)
        self.pool = nn.MaxPool2d(2,2)
        # input_channels=4, output_channels=8
        self.conv2 = nn.Conv2d(depth[0],depth[1],5,padding=2)
        # Full connected layer, flatten output of last convolutional layer.
        self.fc1 = nn.Linear(image_size//4*image_size//4*depth[1],512)
        self.fc2=nn.Linear(512, num_classes)

    def forward(self,x):
        x=self.conv1(x)
        x=F.relu(x)
        x=self.pool(x)
        x=self.conv2(x)
        x=F.relu(x)
        x=self.pool(x)
        # Two 2x2 pooling layers make the image 1/4 as before by height and width.
        x=x.view(-1, image_size//4*image_size//4*depth[1])
        x=self.fc1(x)
        x.F.relu(x)
        # Dropout at 0.5 possibility.
        x=F.dropout(x,training=self.training)
        x=self.fc2(x)
        # Accelerate CrossEntropyLoss calculation with log_softmax
        x=F.log_softmax(x,dim=1)
        return x

    def retrieve_features(self, x):
        """
        Extract Convolutional Neuron Network's feature map.
        """
        feature_map1=F.relu(self.conv1(x))
        x=self.pool(feature_map1)
        feature_map2=F.relu(self.conv2(x))
        return (feature_map1, feature_map2)

def check(predictions, labels):
    pred=torch.max(predictions.data,1)[1]
    rights=pred.eq(labels.data.view_as(pred)).sum()
    return rights, len(labels)

net=ConvNet()
criterion=nn.CrossEntropyLoss()
optimizer=optim.SGD(net.parameters(), lr=0.001, momentum=0.9)

record=[]
weights=[]

# training
for epoch in range(num_epochs):
    train_rights=[]
    for batch_idx,(data, target) in enumerate(train_loader):
        data,target=data.clone().requires_grad_(True), target.clone().detach()
        # Tag net model that it's on training.
        net.train()
        # To decide open dropout or not

        net = net.to(device)
        data = data.to(device)
        target = target.to(device)

        output = net(data)
        loss = criterion(output, target)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step() # One stop of SGD
        right = check(output, target)
        train_rights.append(right)

        if batch_idx%100==0:
            net.eval() # Tag net model that it's on validating
            val_rights = []

            for (data, target) in val_loader:
                data, target = (data.clone().requires_grad_(True),
                                target.clone().detach())

                data=data.to(device)
                target=target.to(device)
                output=net(data)
                right=check(output,target)
                val_rights.append(right)

            train_r=(sum(tup[0] for tup in train_rights), sum([tup[1] for tup in
                                                               train_rights]))
            val_r = (sum([tup[0] for tup in val_rights]), sum([tup[1] for tup in
                                                               val_rights]))
            logger.info(val_r)
            logger.info("Training epoch: {} [{}/{} ({:.0f}%)]    loss: {:.6f}    Accuracy: {:.2f}"
                        .format(epoch,
                                batch_idx*batch_size,
                                len(train_loader.dataset),
                               100.*batch_idx/len(train_loader),
                                loss.data,
                                100.*train_r[0].numpy()/train_r[1],
                               100.*val_r[0].numpy()/val_r[1]))

            record.append((100-100.*train_r[0]/train_r[1],100-100.*val_r[0]/val_r[1]))
            weights.append([net.conv1.weight.data.clone(),
                            net.conv1.bias.data.clone(),
                            net.conv2.weight.data.clone(),
                            net.conv2.bias.data.clone()])

# Test on testing set
net.eval() 
vals = []

for data, target in test_loader:
    data, target = data.clone().detach().requires_grad_(True),
    target.clone().detach()
    data = data.to(device)
    target=target.to(device)
    output=net(data)
    val=check(output,target)
    vals.append(val)

# Calculate accuracy
rights=(sum([tup[0] for tup in vals]), sum([tup[1] for tup in vals]))
accuracy = 100.*rights[0].numpy()/rights[1]
logger.info("Accuracy: {}".format(accuracy))

# Plot loss diagram, error rate on validating and testing set.
plt.figure(figsize=(10,7))
plt.plot(record)
plt.xlabel("Steps", fontsize=16)
plt.ylabel("Error rate", fontsize=16)
plt.show()

# Random image test
idx = 4576
muteimg=test_dataset[idx][0].numpy()
plt.imshow(muteimg[0,...])
logger.info(f"Label: {test_dataset[idx][1]}")
plt.show()

