#!/usr/bin/python

import csv
f_bin = open('dumpBin.csv','w')
f = open('dumpMarks.csv', 'r');

try:
    reader = csv.reader(f, delimiter=',')
    for row in reader:
        bin_dump = ''
        if len(row):
           print( row.pop(0))
        for marks in row:
            try:
                v_marks = int(marks)
                if v_marks < 0:
                    if -600+(-600*0.2) < v_marks < -600-(-600*0.2):
                        bin_dump += '0'
                    elif -1800+(-1800*0.2) < v_marks < -1800-(-1800*0.2):
                        bin_dump +='1'

            except ValueError:
                continue
        print ''
        for i in range(0,len(bin_dump),8):
            print '%2s' % hex(int(bin_dump[i:i+8],2))
        f_bin.write(bin_dump+'\n')


finally:
    f.close()
    f_bin.close()
