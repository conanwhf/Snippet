#create root.img（ssl）
e2fsimage -d rootfs -f root.img -s 10240
gzip -9 root.img
mkimage -A arm -O linux -T kernel -C none -a 43000000 -e 43000000 -n linux-2.6.18.8 -d root.img.gz root.img


#制作uboot使用的文件系统img（beagleboard）
#!/bin/bash
dd if=/dev/zero of=temp bs=1M count=40
losetup /dev/loop0 temp
sudo mke2fs -m 0 /dev/loop0
mkdir -p loop 
sudo mount -t ext2 /dev/loop0 loop
sudo cp -raf initramfs/* loop
sudo umount loop; rm -rf loop
gzip -v9 temp
mkimage -n 'iNova ext2 uboot ramdisk' -A arm -O linux -T ramdisk -C gzip -d temp.gz ramdisk.img

# mount相关
umount /usr
rmmod nftl_usr
flash_eraseall /dev/mtd4
insmod /lib/modules/nftl_usr.ko partition=4
mke2fs -b 4096 /dev/nftl_usr0
mount -t  ext2 /dev/nftl_usr0 /usr

umount /media/localdata
rmmod nftl_dat
flash_eraseall /dev/mtd5
insmod /lib/modules/nftl_dat.ko partition=5
sleep 1
mke2fs -b 4096 /dev/nftl_dat0
mount -t  ext2  /dev/nftl_dat0 /media/localdata

umount /media/usrdata
rmmod nftl
flash_eraseall /dev/mtd6
insmod /lib/modules/nftl.ko partition=6
sleep 1 
mkdosfs_nftl -F 32 -s 8 -R 6 -n Android /dev/nftl0
mount -t vfat -rw -o umask=0,utf8,shortname=winnt /dev/nftl0 /media/usrdata

mount -t ntfs -rw -o umask=0,nls=utf8 /dev/mmcblk0 /media/sd/
mount -t ntfs-3g -rw -o umask=0,nls=utf8 /dev/mmcblk0 /media/sd/
ntfs-3g /dev/mmcblk0 /media/sd/


# 烧写Bootloader
arm-linux-objcopy --set-start=0xE0001000 -Osrec ipl.exe ipl.srec
../tool/s2brc <u-boot.srec >uboot.brc
arm-linux-objcopy -Obinary ipl.exe ipl.bin

#create root.img
e2fsimage -d rootfs -f root.img -s 10240
gzip -9 root.img
mkimage -A arm -O linux -T kernel -C none -a 43000000 -e 43000000 -n linux-2.6.18.8 -d root.img.gz root.img
