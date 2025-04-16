# 判断文件,变量是否存在 
myFile="/var/log/httpd/access.log" 
if [ ! -f "$myFile”]; then 
    echo “No file”
fi 

# 其他参数还有-n,-n是判断一个变量是否是否有值 
if [ ! -n "$myVar" ]; then 
	echo "$myVar is empty" 
fi 

# 两个变量判断是否相等 
if [ "$var1" == "$var2" ]; then 
	echo '$var1 eq $var2' 
fi 

# $key==y/Y
if [ "$key" = "y" -o "$key" = "Y" ]; then 
	echo "yes"
fi

-a file exists. 
-b file exists and is a block special file. 
-c file exists and is a character special file. 
-d file exists and is a directory. 
-e file exists (just the same as -a). 
-f file exists and is a regular file. 
-g file exists and has its setgid(2) bit set. 
-G file exists and has the same group ID as this process. 
-k file exists and has its sticky bit set. 
-L file exists and is a symbolic link. 
-n string length is not zero. 
-o Named option is set on. 
-O file exists and is owned by the user ID of this process. 
-p file exists and is a first in, first out (FIFO) special file or 
named pipe. 
-r file exists and is readable by the current process. 
-s file exists and has a size greater than zero. 
-S file exists and is a socket. 
-t file descriptor number fildes is open and associated with a 
terminal device. 
-u file exists and has its setuid(2) bit set. 
-w file exists and is writable by the current process. 
-x file exists and is executable by the current process. 
-z string length is zero. 