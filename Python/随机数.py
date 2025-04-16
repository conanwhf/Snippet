import random

# 给随机数对象一个种子值，用于产生随机序列
random.seed(int)

# 返回指定范围的一个随机整数，包含上下限
random.randint(a, b)

# 随机正态浮点数
random.uniform(u, sigma)

# 按步长随机在上下限范围内取一个随机数
random.randrange(start, stop, step)

# 随机的选取n个字符
random.sample('abcdefghijk', 3)
# 随机的选取一个字符
random.choice('abcde./;[fgja13ds2d')
#随机选取几个字符，再拼接成新的字符串
# 对list列表随机打乱顺序，也就是洗牌
item = [1, 2, 3, 4, 5, 6, 7]
random.shuffle(item)
