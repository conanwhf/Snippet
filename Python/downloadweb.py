# 方法一
import requests
import webbrowser
import urllib.request

dataUrl = "http://hq.sinajs.cn/list=sh600755"
stdout = urllib.request.urlopen(dataUrl)
stdoutInfo = stdout.read().decode('utf-8')

# 方法二
data = requests.get(dataUrl).text

# 获取图片

dataUrl = "http://test.com/test.jpg"
try:
    data = requests.get(dataUrl)
    return data.content
except:
    print("获取数据失败")

#下载网页
import urllib.request
import urllib.error
import ssl


def getHTML(url):
    context = ssl._create_unverified_context()
    request = urllib.request.Request(url, headers={'User-agent': 'panda'})
    try:
        html = urllib.request.urlopen(request, context=context).read()
    except urllib.error.HTTPError as e:
        print("URL download error:", e.reason)
        return None
    print(html)
    return html


getHTML("http://www.google.com")
getHTML("file:///Users/conan/archives.html")
