#交叉编译内核
make ARCH=arm CROSS_COMPILE=arm-linux- menuconfig
make ARCH=arm CROSS_COMPILE=arm-linux- uImage
make -C src ARCH=arm CROSS_COMPILE=arm-linux- O=../out modules

# 设置内核的打印级别(全部显示)
echo 7 > /proc/sys/kernel/printk

#get read-only state
cat /proc/mounts | awk '/\/media\/usrdata/{print $4 }' | cut -c2-1

#power mode switch
echo standby > /sys/power/state
echo mem > /sys/power/state
echo on > /sys/power/state

#backlight
echo wf_mode=1 > /sys/devices/platform/lcdc.0/mode
cat /sys/devices/platform/lcdc.0/mode

#for touch calibrate
cat /etc/pointercal >> /sys/devices/platform/ssltsc/calibrate
echo show > /sys/devices/platform/ssltsc/calibrate
echo reset > /sys/devices/platform/ssltsc/calibrate

#bus-max
echo 480000 > /sys/devices/system/cpu/cpu0/cpufreq/optimus_set_armfreq
echo 132000 > /sys/devices/system/cpu/cpu0/cpufreq/optimus_set_hclk
#normal-clk
echo 396000 > /sys/devices/system/cpu/cpu0/cpufreq/optimus_set_armfreq
echo 132000 > /sys/devices/system/cpu/cpu0/cpufreq/optimus_set_hclk
#core-max
echo 99000 > /sys/devices/system/cpu/cpu0/cpufreq/optimus_set_hclk
echo 528000 > /sys/devices/system/cpu/cpu0/cpufreq/optimus_set_armfreq

# 手动创建设备节点
major=`cat /proc/devices | grep SSL_VPPHD| cut -c1-3`
mknod /dev/vpphd c $major 0

#mount USB
mount -t vfat /dev/sda /mnt

#check mount
if [ -z `grep usrdata /etc/mtab`]; then
echo fail
fi 

# clean memory to free from cache, 
echo 3 > /proc/sys/vm/drop_caches
echo 0 > /proc/sys/vm/drop_caches 
cat /proc/sys/vm/drop_caches

# 检查节点是否生成
while [ ! -e /dev/binder ]; do sleep 1; done

#enable the SWAP in PP1938
swapoff /dev/mtdblock7
umount /media/cdrom
rmmod nftl_swp
flash_eraseall /dev/mtd7
insmod /tmp/nftl_swp.ko partition=7
sleep 1
mke2fs -b 4096 /dev/nftl_swp0
mount -t  ext2  /dev/nftl_swp0 /media/cdrom
dd if=/dev/zero of=/media/cdrom/swapfile bs=1024 count=32768
mkswap /media/cdrom/swapfile
swapon /media/cdrom/swapfile

# 启用内存压缩
insmod ramzswap.ko num_devices=1 disksize_kb=16384
sleep 1
swapon /dev/ramzswap0
cat /proc/meminfo; free; rzscontrol /dev/ramzswap0 --stats

#get disk UUID
blkid -o value -s UUID /dev/sdb1

#usbfs state
mount -t usbfs none /proc/bus/usb

#get the kernel dump file
arm-linux-objdump -d out/vmlinux > log
