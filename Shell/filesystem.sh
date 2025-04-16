# NFTL
mount -t ntfs -rw -o umask=0,nls=utf8 /dev/mmcblk0 /media/sd/
mount -t ntfs-3g -rw -o umask=0,nls=utf8 /dev/mmcblk0 /media/sd/
ntfs-3g /dev/mmcblk0 /media/sd/


#check mount
if [ -z `grep usrdata /etc/mtab`]; then
echo fail
fi 
is_mounted=$(grep ${destination}p /proc/mounts | awk '{print $2}')
	if grep -q ${destination}p /proc/mounts; then
			echo "Found mounted partition(s) on " ${destination}": " $is_mounted
	else
			echo "No eMMC partition found. exit."
			exit
	fi

#get read-only state
cat /proc/mounts | awk '/\/media\/usrdata/{print $4 }' | cut -c2-1


#get disk UUID
blkid -o value -s UUID /dev/sdb1

#usbfs state
mount -t usbfs none /proc/bus/usb
