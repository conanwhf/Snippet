import time
import smbus


i2c_addr = 0x48
i2c_cmd = 0xAB


def i2c_test(addr):
    print("start i2c test for addr=%x" % addr)
    data = 0x0f
    cmd = 0xAB
    loop = 5
    # 打开 /dviev/i2c-1
    bus = smbus.SMBus(1)
    while loop > 0:
        bus.write_byte(addr, data)
        data = bus.read_byte(addr)
    	# @bus.write_byte_data(addr, cmd, data)
    	# data = bus.read_byte_data(addr, cmd)
    	print(data)
        loop = loop-1
    print("i2c test done!")
