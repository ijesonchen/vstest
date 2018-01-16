import os

TMPLNAME = 'PatTemplate.cpp'
SRC = 'A0000'
DSTDIR = r'z:\\0\\t\\'

def ReadTmpl(filename):
    with open(filename) as f:
        return f.read()

if __name__ == '__main__':
    
    s = ReadTmpl(TMPLNAME)
    for i in range(1001,1200):
        title = ("T%04d"%i)
        s2 = s.replace(SRC, title)
        fndst = DSTDIR+title+'.cpp'
        with open(fndst, 'w') as f:
            f.write(s2)
