# -*- coding: utf-8 -*-
import mimetypes
from email.mime.base import MIMEBase
from email.mime.audio import MIMEAudio
from email.mime.image import MIMEImage
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email import encoders
import smtplib
import os
import sys
import datetime

EmailTo = 'gfdsgfdsgd@gmail.com,fdafdas@yahoo.com'
EmailFrom = 'fdasfdasfsd@126.com'
SMTPsever = 'smtp.126.com'
LoginAccount = EmailFrom
LoginPassword = 'fdasfdafds'
EmailResultFile = '等待添加的附件'

'''添加附件
'''


def getAttachment(fn, fn_shown):
	att = MIMEText(open(fn, 'rb').read(), 'base64', 'utf-8')
	att["Content-Type"] = 'application/octet-stream'
	att.add_header('Content-Disposition', 'attachment',
	               filename=('gbk', '', fn_shown))
	encoders.encode_base64(att)
	return att


'''
发送邮件
'''


def hy_send_email(resText):
	# 创建一个带附件的实例
	msg = MIMEMultipart()
	# 添加正文
	text = "测试\n\n"
	text = text + resText
	msg.attach(MIMEText(text, 'plain', 'utf-8'))

	# 添加附件
	fn_shown = '我想显示在邮件中的附件名'  # 这里的filename可以任意写，写什么名字，邮件中显示什么名字
	msg.attach(getAttachment(EmailResultFile, fn_shown))

	# 邮件头
	msg['to'] = EmailTo
	msg['from'] = EmailFrom
	msg['subject'] = '测试' + timestr
	# 发送邮件
	try:
		server = smtplib.SMTP(SMTPsever)
		server.ehlo()
		server.starttls()
		server.login(LoginAccount, LoginPassword)
		server.sendmail(msg['from'], msg['to'], msg.as_string())
		server.quit()
		print('发送成功')
		return True
	except:
		info = sys.exc_info()
		print(info[0], ":", info[1])
		return False
