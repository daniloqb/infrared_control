from Devices import *

__author__ = 'tic'

print 'Connecting to {} with baudrate {}'.format('/dev/ttyACM0',9600)
comport = serial.Serial('/dev/ttyACM0', 9600, timeout=5)
time.sleep(1.8)

york = AirConditioner(mode='normal', temp='24', fan='auto', sweep='off')

nec = DatashowNEC();
nec.powerOn()

d = dict()
d = york.getJsonCode()

code = json.dumps(d)

print('Sending code to device\n {}'.format(code))
comport.write(code)

time.sleep(0.5)
VALUE_SERIAL = comport.readline()
print '\nRetorno da serial: %s' % (VALUE_SERIAL)

d = dict()
d = nec.getJsonCode()

code = json.dumps(d)

time.sleep(1.8)


print('Sending code to device\n {}'.format(code))
comport.write(code)

time.sleep(0.5)
VALUE_SERIAL = comport.readline()
print '\nRetorno da serial: %s' % (VALUE_SERIAL)

comport.close()