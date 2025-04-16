#将 /dev/disk2 全盘数据备份到指定路径的 image 文件
dd if=/dev/disk2 of=~/image

#将备份文件恢复到指定磁盘
dd if=~/image of=/dev/disk2

#备份 /dev/disk2 全盘数据，并利用 gzip 工具进行压缩，保存到指定路径
dd if=/dev/disk2 | gzip > ~/image.gz

#将压缩的备份文件恢复到指定盘
`gzip -dc ~/image.gz | dd of=/dev/disk2`

#备份磁盘开始的 512 个字节大小的 MBR 信息到指定文件
`dd if=/dev/disk2 of=~/image count=1 bs=512`
count=1 指仅拷贝一个块；bs=512 指块大小为 512 个字节。

#拷贝内存内容到硬盘（Linux）
`dd if=/dev/mem of=~/mem.bin bs=1024`（指定块大小为 1k）

#销毁磁盘数据（利用随机的数据填充硬盘）
`dd if=/dev/urandom of=/dev/disk2 bs=16M`

#通过两个命令输出的执行时间,测试硬盘读写速度
dd if=/dev/zero of=~/1Gb.file bs=1024 count=1000000
dd if=~/1Gb.file bs=64k | dd of=/dev/null`
