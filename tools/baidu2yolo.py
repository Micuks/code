import os
import json

ParentPath = './SpiceBottle/'
JsonPath = 'jsons/'
LabelPath = 'labels/'

names = ['传单', '充电宝', '包', '塑料玩具', '塑料碗盆', '塑料衣架', '快递纸袋', '报纸', '插头电线', '旧书', '旧衣服', '易拉罐', '杂志', '枕头', '毛绒玩具', '泡沫塑料', '洗发水瓶', '牛奶盒等利乐包装', '玻璃', '玻璃瓶罐', '皮鞋', '砧板', '纸板箱', '调料瓶', '酒瓶', '金属食品罐', '锅', '食用油桶', '饮料瓶', '干电池', '废弃水银温度计', '废旧灯管灯泡', '杀虫剂容器', '电池', '软膏', '过期药物', '除草剂容器', '剩饭剩菜', '大骨头', '果壳瓜皮', '残枝落叶', '水果果皮', '水果果肉', '茶叶渣', '菜梗菜叶', '落叶', '蛋壳', '西餐糕点', '鱼骨', '一次性餐具', '化妆品瓶', '卫生纸', '尿片', '污损塑料', '烟蒂', '牙签', '破碎花盆及碟碗', '竹筷', '纸杯', '贝壳']

def calculate(x1, x2, y1, y2, h, w):
    CenX = 1.0 * (x1 + x2) / (2 * w)
    CenY = 1.0 * (y1 + y2) / (2 * h)
    Width = 1.0 * (y2 - y1) / h
    Height = 1.0 * (x2 - x1) / w
    return CenX, CenY, Width, Height

def main():


    JsonFiles = os.listdir(ParentPath+JsonPath)

    for JsonFile in JsonFiles:
        TxtFileName = JsonFile.split('.')[0]+'.txt'
        try:
            data = json.load(open(ParentPath+JsonPath+JsonFile, 'r', encoding='utf-8'))
        except:
            print(JsonFile)
            continue

        if not os.path.exists(ParentPath+LabelPath):
            os.mkdir(ParentPath+LabelPath)
        TxtFile = open(ParentPath+LabelPath+TxtFileName, 'w', encoding='utf-8')

        for i in data['labels']:
            if(i['name'] == '烟蒂群'):
                i['name'] = '烟蒂'
            if(i['name'] == '化妆品'):
                i['name'] = '化妆品瓶'
            if(i['name']) == '果皮':
                i['name'] = '果壳瓜皮'
            if(i['name']) in ['西餐', '糕点', '厨具', '纸盒']:
                i['name'] = '西餐糕点'
            if(i['name']) == '水管':
                i['name'] = '锅'
            if(i['name']) == '酒杯':
                i['name'] = '酒瓶'
            if(i['name']) == '石臼':
                i['name'] = '破碎花盆及碟碗'
            if(i['name']) in ['塑料袋', '塑料盒']:
                i['name'] = '污损塑料'
            if(i['name']) == '金属罐':
                i['name'] = '金属食品罐'
            if(i['name']) == '塑料瓶':
                i['name'] = '调料瓶'
            if(i['name']) == '玻璃瓶':
                i['name'] = '酒瓶'
            ClassId = names.index(i['name'])
            x1 = i['x1']
            x2 = i['x2']
            y1 = i['y1']
            y2 = i['y2']
            w = i['size']['width']
            h = i['size']['height']
            ConvertedLabel = calculate(x1, x2, y1, y2, h, w)
            TxtFile.write("%s %s %s %s %s\n" % (ClassId, ConvertedLabel[0],
                                                ConvertedLabel[1],
                                                ConvertedLabel[2],
                                                ConvertedLabel[3]))
    print('Done')

if __name__ == "__main__":
    print('The number of classes is:{}'.format(names.__len__()))
    #input("Press enter to begin")
    main()
