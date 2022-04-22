import os
import shutil
ParentPath = './SpiceBottle/'
ImagePath = 'images/'
JsonPath = 'jsons/'
LabelPath = 'labels/'

def MakeDir():
    if not os.path.exists(ParentPath+ImagePath):
        os.mkdir(ParentPath+ImagePath)
    if not os.path.exists(ParentPath+JsonPath):
        os.mkdir(ParentPath+JsonPath)
    if not os.path.exists(ParentPath+LabelPath):
        os.mkdir(ParentPath+LabelPath)

def Classificate():
    Files = os.listdir(ParentPath)
    MakeDir()
    for eachfile in Files:
        # FileSpliltedList = eachfile.split('.')
        # print("FileSpliltedList.__len__ == {}".format(FileSpliltedList.__len__()))
        if eachfile.split('.').__len__() > 1:
            FileExpandName = eachfile.split('.')[1]
            # print('The expand name of {} is {}'.format(eachfile, FileExpandName))
            if FileExpandName == 'json':
                shutil.move(ParentPath+eachfile, ParentPath+JsonPath+eachfile)
                print("move {} to {}".format(eachfile, ParentPath+JsonPath))
            else:
                shutil.move(ParentPath+eachfile, ParentPath+ImagePath+eachfile)
                print("move {} tp {}".format(eachfile, ParentPath+ImagePath))

if __name__ == '__main__':
    print("Classification begins")
    Classificate()
    print("Classification ends")
