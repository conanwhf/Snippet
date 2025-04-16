## 截取指定字符串
- $\{parameter%word} 最小限度从后面截取word
- $\{parameter%%word} 最大限度从后面截取word
- $\{parameter#word} 最小限度从前面截取word
- $\{parameter##word} 最大限度从前面截取word

str=usr/local/bin/test123
${str%/*}=usr/local/bin
${str%%/*}=usr
${str#*/}=local/bin/test123
${str##*/}=test123
  
## 截取固定长度字符串
`$str|cut -c1-8`=“sr/local”
`${str:0:4}`=“usr/”

## 字符串长度
`${#str}`

#shell to get the string
var=a.b.c.d
echo ${var%.*}	a.b.c
echo ${var%%.*}	a
echo ${var#*.}	b.c.d
echo ${var##*.}	d

#删除文件重复行
awk '!seen[$0]++' <filename>

#替换文本中的字符串
vi urls.txt <<-!
:g/$str1/s//$str2/g
:wq
-!
