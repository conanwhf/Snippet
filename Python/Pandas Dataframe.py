import pandas as pd

pd.options.mode.chained_assignment = None

# 新建
data = pd.DataFrame(columns=['code', 'name'])
result = pd.DataFrame({'result': ['']}, index=[])

# 合并，添加
# 合并数据，取交集
data = pd.merge(data, new, how='outer', left_index=False,
                right_index=False, sort=True, copy=False)
# 添加一条数据新数据
appendData = pd.DataFrame({'date': [new[0]], 'open': [new[1]], 'close': [
                          new[2]], 'high': [new[3]], 'low': [new[4]], 'volume': [new[5]], 'code': [new[6]]})
data = pd.concat([data, appendData])
# 直接合并数据
result = pd.merge(stocks, result, how='inner', left_index=True,
                  right_index=True, sort=True, copy=True)
# 在默认情况下，axis=0为纵向拼接，此时有
concat([df1, df2]) #等价于 df1.append(df2)
# 在axis=1 时为横向拼接 ，此时有
concat([df1, df2], axis=1) #等价于 merge(df1, df2, left_index=True, right_index=True, how='outer')


# 排序
result.sort_values(by=['raise'], ascending=[0], inplace=True)

# 赋值
result.loc[i] = {'result': res}

# 属性
stocks.empty  # 判断为空
len(data)  # 长度

# 定位和切片
data = data[['col1', 'col2']]

''''
data={
index col1 col2
0       2   3
3       32  33
8       82  83
9       92  93
4       42  43
}
'''
data.close.ix[length-6:length-2]
data.close.iloc[length-1]
data.tail(1)

# 保存和读取
new = pd.read_csv('test.csv', sep=',')
data.to_csv(os.path.join(SearchDir, SaveFileName), sep=',',
            header=True, columns=['code', 'name'] + days + ['total'])
stocks = pd.read_csv(StockCodesFile, sep=',', dtype={'code': object})
data = pd.read_table('test2', sep='[|,\s,\t,\,]+', header=None)

# 数据修改
new.result = new.result.astype(str).str.replace('周期符合要求', '')
result.loc[i] = {'result': res}

# 重命名列名
new.columns = ['code', 'name', 'test']

# 部分计数，并保存在新列
days = ['c1', 'c2', 'c3']
temp = data[days].groupby(level=0).count()
data['total'] = temp.sum(axis=1)

# 设置index相关
stocks.set_index('code', inplace=True, drop=True)
need[need.index % period == 1]  # 提取单数行
need = need.reset_index(drop=True)

# 获取列或index数值
allcode = stocks.index.values

# 统计某一列x中各个值出现的次数：
a['x'].value_counts()

# 根据分类生成数字指代的分类表
data['Class'].replace({"largeDoses": 2, "smallDoses": 1, "didntLike": 0})

# 清空数据，保留列名
df.drop(df.index, inplace=True)
