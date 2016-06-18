from Devices import *

__author__ = 'tic'


york = AirConditioner(mode='normal', temp='24', fan='auto', sweep='off')


print york.getCode()
print york.getJsonCode()
print
print york.getCode('bin')
print york.getCode('hex')
print york.info()

#controller = ControllerDeviceEthernet(york,'143.106.230.104',80)
#controller.execute()


controller = ControllerDeviceCOM(york,'/dev/ttyUSB0',9600)


time.sleep(3)


#crtlLed.execute()
york.status = 'off'
controller.execute()