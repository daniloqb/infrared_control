#!/usr/bin/python


f = open('dumpBin.csv','r')
f_codes = open('dumpCodesHex.csv','w')

for line in f:
    v = []
    for i in range(0, len(line)-1,8):
        v.append(line[i:i+8])
    str = ''
    for code in range(len(v)):
        if code % 4 == 0:
            str += ' 0x'
        h =  hex(int(v[code],2))[2::]
        if len(h) < 2:
            h = '0'+h
        str +=h
    f_codes.write(str + '\n')
    print str

f.close()
f_codes.close()
