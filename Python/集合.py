a = [1, 2, 3]
b = [2, 4, 5]
# 并集
print(list(set(a+b)))
list(set(a).union(set(b)))
# 差集
print(list(set(a).difference(set(b))))
# 交集
list(set(a).intersection(set(b)))


t = set([1, 2, 3])
t = set([1, 3, 5])
a = t | s          # t 和 s的并集
b = t & s          # t 和 s的交集
c = t - s;          # 求差集（项在t中，但不在s中）
d = t ^ s          # 对称差集（项在t或s中，但不会同时出现在二者中）
