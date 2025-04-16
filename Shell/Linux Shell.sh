# 计算运行时间 
mount -t vfat /dev/mmcblk0p1 /mnt; sync
time sh -c "cp /mnt/upgrade/usr.tar.gz /tmp; sync"

#获取当前目录
DIR="$( cd "$( dirname "$0"  )" && pwd  )"
DIR=$(cd `dirname $0`;pwd)

#重启网络
ifdown eth0
ifconfig eth0 up
ifup eth0

#create a 100M file
dd if=/dev/zero of=100M.img bs=1M count=100
dd if=/dev/zero of=/dev/fb0

#search the AAAAA function
#查找包含 "AAAAA" 但排除文件名含 "AAAAAA" 的结果（ -v 表示反向匹配）
find . -name "*.XXX" |grep -v AAAAAA | xargs grep AAAAA
#find and copy
find -name play.h | xargs -I {} cp ../play.h {}
#快速定位定义"AAAAA"类的头文件
#查找包含 "AAAA" 且包含 "class" 的行（通常用于查找类定义）
find . -name "*.h*" | xargs grep AAAA | grep class

#bc配合反正切函数计算pi
echo "scale=1000; a(1)*4" | bc -l

#tar
tar zcvf img.tar.gz img/
tar xzvf img.tar.gz
tar xvf libpano13-2.9.19.tar.gz
tar xf linux-3.4.111.tar.xz

#echo 倒计时
for i in `seq -w 10 -1 1`; do
    echo -ne "\rWill reboot system.... q(/Q) to CANCEL!  $i \a"
    read -t 1 key
    if [[ "$key" == "q" ]] || [[ "$key" == "Q" ]]; then
        echo "reboot canceled"
        return 0
    fi
    #echo -ne "\b\b$i" #每次删除两个字符
done
echo "do it now!!!"

#查找git生成Log
DIR=/home/conan/work/
FN=`date +%Y-%m-%d`.log
echo $FN

cd $DIR
touch $DIR/$FN
for i in $(find -name .git)
do
        PRO=$DIR/${i%.*}
        echo $PRO
        cd $PRO
        echo "\n\n\n==========$PRO===========\n" >> $DIR/$FN
        git log -5 >> $DIR/$FN
done

#串口通信工具
screen /dev/tty.usbserial 115200

#扫描局域网主机
brew install nmap
sudo nmap -sP 192.168.0.0/24  | grep  -v 'Host is up' | awk 'BEGIN{RS=")";FS="scan report for "}NF>1{print $5 $NF}' | sed 'N;s/\n.*(/: /'

#生成目录树
find . -print | sed -e 's;[^/]*/;|____;g;s;____|; |;g'
alias tree="find . -print | sed -e 's;[^/]*/;|____;g;s;____|; |;g'"

#kill包含指定名字的进程
kill -9 `ps -ef | grep AAAA | grep -v "grep" | awk '{print $2}’`
