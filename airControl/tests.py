from Devices import *

__author__ = 'tic'


york = AirConditioner(mode='cool', temp='24', fan='auto', sweep='off')


print york.getIRCode()

print
print york.getIRCode('bin')
print york.getIRCode('hex')

#controller = ControllerDeviceCOM(york,'/dev/ttyUSB0',9600)
#controller = ControllerDeviceEthernet(york,'143.106.230.104',80)


#controller.execute()


#time.sleep(3)

#york.setStatus('off')

#controller.execute()