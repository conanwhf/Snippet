#批量文件重命名
import os
import io
import sys
import shutil

# 将"*第*.mp3"重命名为"第*.mp3"
for i in os.listdir("./"):
    # print(i)
    j = i.split('.')
    if i.endswith(".mp3"):
        temp = i.find('第')
        print(i[temp:])
        os.rename(i, i[temp:])

# 文件路径
os.path.join(ImageSaveDir, fn)
# 添加删除文件夹
os.mkdir(ImageSaveDir)
shutil.rmtree(ImageSaveDir)
# 遍历文件夹
for i in os.listdir(dir):
    # print(i)
    temp = i.split('.')
    if len(temp) == 2 and temp[1] == 'csv':
        print(temp[0])

# 读写
with open(StockResultOutputInfo, 'w', encoding="utf8") as f:
	f.write(resText)
