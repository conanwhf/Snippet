import datetime
# 时区转换


def hy_get_China_time():
	t = datetime.datetime.utcnow()
	t = t.replace(tzinfo=datetime.timezone.utc)
	# print(t)
	temp = datetime.timezone(datetime.timedelta(hours=8))
	t = t.astimezone(temp)
	# print(t)
	return t


# 当前时间
now = datetime.datetime.now()
# 格式化
now.strftime('%Y-%m-%d %H:%M:%S')
%y 两位数的年份表示（00-99）
%Y 四位数的年份表示（000-9999）
%m 月份（01-12）
%d 月内中的一天（0-31）
%H 24小时制小时数（0-23）
%I 12小时制小时数（01-12）
%M 分钟数（00 = 59）
%S 秒（00-59）

%a 本地简化星期名称
%A 本地完整星期名称
%b 本地简化的月份名称
%B 本地完整的月份名称
%c 本地相应的日期表示和时间表示
%j 年内的一天（001-366）
%p 本地A.M.或P.M.的等价符
%U 一年中的星期数（00-53）星期天为星期的开始
%w 星期（0-6），星期天为星期的开始
%W 一年中的星期数（00-53）星期一为星期的开始
%x 本地相应的日期表示
%X 本地相应的时间表示
%Z 当前时区的名称
% % %号本身


# 日期计算
yesterday = now - datetime.timedelta(days=1)
