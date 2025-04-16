# -*- coding: utf-8 -*-
#打印调试信息（通过查看栈）
import sys


def get_cur_info():
	# 当前文件名，可以通过__file__获得
	print(sys._getframe().f_code.co_filename)
	# 当前函数名
	print(sys._getframe(0).f_code.co_name)
	# 调用该函数的函数的名字，如果没有被调用，则返回<module>，貌似call stack的栈低
	print(sys._getframe(1).f_code.co_name)
	# 当前行号
	print(sys._getframe().f_lineno)


def debug():
	print("\n=====function call debug info:")
	print(get_cur_info())


if __name__ == "__main__":
	print("=====main call debug info:")
	print(get_cur_info())
	debug()
