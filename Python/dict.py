#字典
# 作为json文件存取
import json
# 读取
f = open(HistoryDataFile, 'r', encoding="utf8")
res = json.loads(f.read())
f.close()
# 保存
f = open(HistoryDataFile, 'w', encoding="utf8")
f.write(json.dumps(res, ensure_ascii=False))
f.close()


# 生成统一初始值的数据
test = dict.fromkeys(allcode.keys(), 0.0)
# 数组是传指针，所以只能手动初始化：
for i in keys:
    test[i] = []

# 从数组生成字典
keys = [1, 2, 3, 4]
values = [55, 56, 57, 58]
new_dict = dict(zip(keys, values))
