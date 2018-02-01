import os
import shutil
# combine text in subfolders in one doc
PATH = r'''D:\download\02.托马斯和他的朋友们中文版'''
OUTPUT = r'''D:\download\动画MP3\托马斯中文mp3'''

# ffmpeg -i input.mp4 -vn -y -acodec copy output.aac
# ffmpeg -i 01.m4a -f mp3 -acodec libmp3lame -y o.mp3
# ffmpeg -i input.mp4 -vn -y -acodec libmp3lame -f mp3 output.aac

def ExtractAudio(dirname):
    if dirname[0] == '.':
        return
    os.chdir(dirname)

    ffmpeg = PATH + '\\ffmpeg.exe'
    if not os.path.isfile(ffmpeg):
        raise Exception("ffmpeg not found")
    dstpath = OUTPUT + '\\' + dirname
    os.mkdir(dstpath)

    for fn in os.listdir():
        if not os.path.isfile(fn):
            continue
        paths = os.path.splitext(fn)
        if paths[1] == '.mp4':
            print('proc file %s' % fn)
            dst = dstpath + '\\' + paths[0] + '.mp3'
            cmd = ('%s -i "%s" -vn -y -acodec libmp3lame -f mp3 "%s"'%(ffmpeg, fn, dst))
#            dst = dstpath + '\\' + paths[0] + '.m4a'
#            cmd = ('%s -i "%s" -vn -y -acodec copy "%s"'%(ffmpeg, fn, dst))
            print(cmd)
            os.system(cmd)

    
    os.chdir('..')

if __name__ == '__main__':
    os.mkdir(OUTPUT)
    shutil.copy('ffmpeg.exe', PATH + '\\.')
    os.chdir(PATH)
    files = os.listdir()

    for fn in files:
        if os.path.isdir(fn):
            print('****proc dir %s' % fn)
            ExtractAudio(fn)