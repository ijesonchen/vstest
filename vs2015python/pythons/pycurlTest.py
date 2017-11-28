import pycurl
import time

URL = "http://sw.bos.baidu.com/sw-search-sp/software/2d8a07cb1d5d7/Thunder9.1.42.926baidu.exe"
URL = "http://speedtest-sfo2.digitalocean.com/10mb.test"
#URL = 'http://blog.csdn.net/ccpw_cn/article/details/51880860'

tm_init = time.time()
tm_start = time.time()
tm_last = time.time()
total_byte = 0
x = []
b = True

def progress(download_t, download_d, upload_t, upload_d):
    global tm_start
    global tm_last
    global b
    global total_byte
    global x
    if download_d == 0:
        tm_start = time.time()
        tm_last = tm_start
        return

    if b:
        total_byte = download_t
        print("Total size %d %.2f MB"%(download_t, download_t / 1024.0 / 1024))
        b = False
    tm_now = time.time()
    if tm_now - tm_last >= 1:
        tm_last = tm_now
        kbps = download_d / (tm_now - tm_start) / 1024
        x.append(kbps)
        print("Progress %.2f%%, %d kB/s"%(100 * download_d / download_t, kbps))

def body(buf):
    pass



def down(url):
    tm_init = time.time()
    c = pycurl.Curl()
    c.setopt(c.URL, url)
    c.setopt(c.NOPROGRESS, False)
    c.setopt(c.XFERINFOFUNCTION, progress)
    c.setopt(pycurl.WRITEFUNCTION, body)
    c.setopt(pycurl.VERBOSE,0)
    c.perform()
    tm_down = time.time()
    cost1 = tm_down - tm_init
    cost2 = tm_down - tm_start
    print("cost1 %.2f, cost2 %.2f, kbps %d %d"%(cost1, cost2, total_byte / 1024 / cost2, sum(x)/len(x)))

if __name__ == "__main__":
    print("test")
    down(URL)