import matplotlib.pyplot as plt
import random

'''
对几个数组绘制折线图
'''


def plot_data(x=[], data=[[]], labels=[], title="T=???", show=False):
	# 计算需要的中间变量
	count = len(data)
	if count == 0:
		print("待绘制数据为空！")
		return
	if labels == []:
		print("自动生成数据的labels")
		for i in range(count):
			labels += ["%04d" % i]
	if count != len(labels):
		print("数据名称和数据数组个数不符，无法绘制")
		return
	length = []
	alldata = []
	for i in range(count):
		length += [len(data[i])]
		alldata += data[i]
	dataMin = min(alldata)
	dataMax = max(alldata)
	lenMax = max(length)
	# 生成颜色数据
	if count <= 7:
		colors = "bgryckm"
	else:
		colors = []
		for i in range(count):
			random.seed()
			(r, g, b) = random.randint(0, 0x7f), random.randint(
				0x7f, 0xff), random.randint(0, 0xff)
			if i % 3 == 0:
				colors += ['#%02x%02x%02x' % (r, g, b)]
			if i % 3 == 1:
				colors += ['#%02x%02x%02x' % (b, r, g)]
			if i % 3 == 2:
				colors += ['#%02x%02x%02x' % (g, b, r)]
			# colors += [ '#%06x' %random.randint(0,0xf0f0f0)]
	# 折线图初始化配置
	# colors="bgryckm"
	plt.rcParams['font.sans-serif'] = ['SimHei']  # for Chinese characters
	plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号
	fig, ax = plt.subplots()
	plt.title(title)
	plt.grid(True)
	# 定义x, y的坐标轴
	ax.set_ylim([dataMin-(dataMax-dataMin)*0.1, dataMax+(dataMax-dataMin)*0.1])
	if x == [] or len(x) != lenMax:
		x = range(lenMax)
	# 绘制
	for i in range(count):
		plt.plot(x[0:length[i]], data[i], "o-", label=labels[i], color=colors[i])
	plt.legend(loc='best')
	plt.close(0)
	if show == True:
		plt.show()
	return


A = [1, 2, 3, 4, 5]
B = [5, 6, 3, 4, 8, 1, -2]
C = [0.1, 0.4, 10]
x = [4, 5, 6, 7, 8, 9, 10]
plot_data(x, data=[B, C, A], labels=["B", "C", "A"], title=u'测试', show=True)


''''
1、线形
 - | 实线
 --          虚线
 ：         点线
 -.         点横线
 
2、点形
标记符    点形
 +          加号
 o          圆圈
 *          星号
 .          实心点
 x         叉号
 s         正方形
 d         钻石形
 ^         上三角形
 v         下三角形
 >        右三角形
 <        左三角形
 p        五角星形
 h        六角星形
 
3、颜色
标记符    颜色
 r             红
 g            绿
 b            蓝
 c          蓝绿
 m         紫红
 y           黄
 k           黑
 w          白
 '''
