import serial
import time


def showdata(arg):
    # print('data length=', len(arg))
    result = ''
    for i in arg:
        st = '%02X' % ord(i)
        result += st+' '
    print(result)


def serial_test():
    print("start serial test")
    ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    loop = 5
    while loop > 0:
        # 获得接收缓冲区字符
        # count = ser.inWaiting()
        # 读取内容
        data = ser.read(5)
        showdata(data)
        # 清空接收缓冲区
        # ser.flushInput()
        loop = loop-1
    ser.close()
    print("serial test done!")
