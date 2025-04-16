# 编码
StockResultOutputInfo = '结果.txt'.encode('UTF-8')
# 正则
all_codes = re.compile('~(\d+)`').findall(st)  # 寻找~和`之间的所有字符串
s = re.search('''(")(.+)(")''', st).group(2)  # ""之间的数据
# 替换
s.replace()
# 分组
stockInfo = st.split(",")
# 补全长度填0
str.zfill(6)
# 补全长度填空格
str.rjust(9)
str.ljust(9)

# string to hex
# way 1
def convert(arg):
    print('string length=', len(arg))
    result = ''
    data = []
    for i in arg:
        st = '%02X' % ord(i)
        result += st+' '
        data.append(ord(i))
    print(result)
    return data
# way 2
print("hello".encode("hex"))

# hex to string
print("\x49\x36\x5f")
print("49365f".decode("hex"))
