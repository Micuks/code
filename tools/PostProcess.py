# 后处理:
# 删除重复图片,缺乏标签图片
# 按给定比例划分train集和val集

import os, shutil

ParentPath = "/home/micuks/ml/"
ImagePath = "images/"
JsonPath = "jsons/"
TxtPath = "labels/"
DestinationPath = "Dataset_RubbishSorting/"

ClassName = "SpiceBottle/"

MaxNum = 500
rate = 0.8

def f_MakeClassDir(DirName):
    if not os.path.exists(ParentPath+DestinationPath+DirName):
        os.mkdir(ParentPath+DestinationPath+DirName)
        os.mkdir(ParentPath+DestinationPath+DirName+ImagePath)
        os.mkdir(ParentPath+DestinationPath+DirName+TxtPath)
        print("Created folder", ParentPath+DestinationPath+DirName)
    else:
        print("Folder {} already exists.".format(ParentPath+DestinationPath+DirName))

def f_RemoveDuplicateItems():
    NameSet = set()
    FileCount = 0
    DirCount = 0
    DirName = ClassName.rsplit('/', 1)[0]+'_'+str(DirCount)+'/'

    SourceImageDir = os.listdir(ParentPath+ClassName+ImagePath)
    f_MakeClassDir(DirName)

    for file in SourceImageDir:
        if not os.path.isdir(os.path.isfile(os.path.join(ParentPath, ClassName, ImagePath, file))):
            FileName = file.rsplit('.', 1)[0]
            #print("file name is", FileName)
            if FileName in NameSet:
                print("Removed", file, "in destination folder: A file with the same name already exists.")
            elif not os.path.exists(ParentPath+ClassName+TxtPath+FileName+'.txt'):
                    print("Removed", file, "in destination folder. No corresponding label.")
            else:
                NameSet.add(FileName)
                FileCount += 1
                shutil.copy(ParentPath+ClassName+ImagePath+file, ParentPath+DestinationPath+DirName+ImagePath+ClassName.rsplit('/', 1)[0]+'_'+file)
                shutil.copy(ParentPath+ClassName+TxtPath+FileName+'.txt', ParentPath+DestinationPath+DirName+TxtPath+ClassName.rsplit('/', 1)[0]+'_'+FileName+'.txt')
                if FileCount >= 500:
                    f_DelineateDataset(DirName, FileCount)
                    FileCount = 0
                    DirCount += 1
                    DirName = ClassName.rsplit('/', 1)[0]+'_'+str(DirCount)+'/'
                    f_MakeClassDir(DirName)
                    print("Switched to new folder:", DirName)
        else:
            print(os.path.isdir(os.path.isfile(os.path.join(ParentPath, ClassName, ImagePath, file))))
            print(file, "is a dir")

    f_DelineateDataset(DirName, FileCount)
    print("Moved {} images.".format(NameSet.__len__()))

def f_DelineateDataset(DirName, ImageNumber):
    if not os.path.exists(ParentPath+DestinationPath+DirName+ImagePath+'train/'):
        os.mkdir(ParentPath+DestinationPath+DirName+ImagePath+'train/')
        os.mkdir(ParentPath+DestinationPath+DirName+TxtPath+'train/')
    if not os.path.exists(ParentPath+DestinationPath+DirName+ImagePath+'val/'):
        os.mkdir(ParentPath+DestinationPath+DirName+ImagePath+'val/')
        os.mkdir(ParentPath+DestinationPath+DirName+TxtPath+'val/')

    TrainNumber = int(ImageNumber * rate)
    ImageDir = os.listdir(ParentPath+DestinationPath+DirName+ImagePath)
    ImageCnt = 0
    for file in ImageDir:
        if not os.path.isdir(os.path.join(ParentPath, DestinationPath, DirName, ImagePath, file)):
            FileName = file.rsplit('.', 1)[0]
            if ImageCnt <= TrainNumber:
                shutil.move(ParentPath+DestinationPath+DirName+ImagePath+file, ParentPath+DestinationPath+DirName+ImagePath+'train/')
                shutil.move(ParentPath+DestinationPath+DirName+TxtPath+FileName+'.txt', ParentPath+DestinationPath+DirName+TxtPath+'train/')
                ImageCnt += 1
            else:
                shutil.move(ParentPath+DestinationPath+DirName+ImagePath+file, ParentPath+DestinationPath+DirName+ImagePath+'val/')
                shutil.move(ParentPath+DestinationPath+DirName+TxtPath+FileName+'.txt', ParentPath+DestinationPath+DirName+TxtPath+'val/')


if __name__ == "__main__":
    print("Class name is", ClassName)
    f_RemoveDuplicateItems()
    print("Done")

