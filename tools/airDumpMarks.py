#!/usr/bin/python

import time
import serial
import sys


dict_args = {
'filename':'dumpMarks.cvs' ,
'port':'/dev/ttyACM0',
'baudrate':'115200',

}

args = sys.argv[1::]

if (args):
    if args[0] == '-h' or args[0] == '--help':
        print 'help'
        exit()

for arg in  args:
   l = arg.split('=')
   if len(l) > 1:
      if dict_args.has_key(l[0]):
          dict_args[l[0]] = l[1]




f = open(dict_args['filename'], 'w')
line = ''
comport = serial.Serial(dict_args['port'], int(dict_args['baudrate']))
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
