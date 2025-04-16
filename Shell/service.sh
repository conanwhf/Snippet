#! /bin/sh
### BEGIN INIT INFO
# Provides:          iNovaBearService
# Required-Start:    networking $network $remote_fs $syslog hostname    
# Required-Stop:     $remote_fs
# Default-Start:     S
# Default-Stop:      
# Short-Description: Start or stop the iNova Proxy.
### END INIT INFO



case $1 in
	start)
        /home/pi/iNova/iNovaServer_Modbus &
		/home/pi/iNova/iNovaServer_wifi.py &
		echo "Starting iNovaBear service"
        	;;
     	stop)
		sudo kill -9 `ps -ef | grep iNovaServer | grep -v "grep" | awk '{print $2}'`
		echo "iNovaBear service stopped"
        	;;
	*)
		echo "iNovaBear service Usage: $0 (start|stop)"
		exit 1
		;;
esac
exit 0



2. 将服务加入/移除启动选项：
sudo update-rc.d XXXX defaults
sudo update-rc.d -f XXXX remove
会在/etc/rc.(x)/下面生成/删除KxxXXX和SxxXXX的软链接

3. 手动启动/停止脚本
sudo service XXXX start
sudo service XXXX stop
