def _file_output(arg, line=0):
    f = open(arg)
    res = f.readlines()
    f.close()
    if line == -1:  # 需要全部数据
        return res
    else:
        return res[line]
    # return res


def _cmd_output(args, line=0):
    f = os.popen(args)
    res = f.readlines()
    f.close()
    if line == -1:  # 需要全部数据
        return res
    else:
        return res[line]
