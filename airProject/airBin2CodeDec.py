#!/usr/bin/python


f = open('dumpBin.csv','r')
f_codes = open('dumpCodesDec.csv','w')

for line in f:
    v = []
    for i in range(0, len(line)-1,8):
        v.append(line[i:i+8])
    str_line = ''
    for code in range(len(v)):
        if code % 4 == 0:
            str_line += ' 0x'
        h =  hex(int(v[code],2))[2::]
        if len(h) < 2:
            h = '0'+h
        str_line +=h
    dec =  str_line.split()
    l = []

    for values in dec:
        l.append(int(values,16))

    str_l = ''
    for values in l:
        str_l += str(values) + ' '
    f_codes.write(str_l + '\n')

f.close()
f_codes.close()
