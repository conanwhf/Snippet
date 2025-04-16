import matplotlib.pyplot as plt

'''绘制散点图'''


def draw(x, y, color='b'):
	fig = plt.figure()
	ax = fig.add_subplot(111)
	# 设置标题
    ax.set_title('Scatter Plot')  
    #设置轴标签  
    plt.xlabel('X')  
    plt.ylabel('Y') 
    #设置图标  
    plt.legend('x1')  
    #画散点图 
	ax.scatter(x, y, c=color)
	plt.show()
	return


#产生测试数据  
x = np.arange(1,10)  
y = np.arange(11,20)
z = np.arange(21,30)

draw(x, y, color=30*z)