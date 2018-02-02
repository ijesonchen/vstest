import os

# create empty text file

DSTDIR = r'z:\\0\\t\\'

def ReadTmpl(filename):
    with open(filename) as f:
        return f.read()

if __name__ == '__main__':
    for i in range(1001,1200):
        title = ("A%04d"%i)
        fndst = DSTDIR+title+'-1.txt'
        with open(fndst, 'w') as f:
            pass
