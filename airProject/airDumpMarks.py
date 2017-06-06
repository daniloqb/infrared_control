#!/usr/bin/python

import time
import serial



filename = 'dumpMarks.csv'
f = open(filename, 'w')
line = ''
comport = serial.Serial('/dev/ttyACM0', 115200)
time.sleep(1.8)
try:
    while True:
        line = comport.readline()
        print line

        if line[0:4] == 'Raw:':
            print 'Command Accepted.'
            f.write(line)
except KeyboardInterrupt:
    print 'You canceled the operation.'
finally:
    comport.close()
    f.close()
