from Devices import *

__author__ = 'tic'


york = AirConditioner(mode='normal', temp='24', fan='auto', sweep='off')

#york.setStatus('off')
print york.getCode()

print
print york.getCode('bin')
print york.getCode('hex')


led = LED(1);

crtlLed = ControllerDeviceEthernet(led,'143.106.230.104',80);

#controller = ControllerDeviceCOM(york,'/dev/ttyACM0',9600)
#controller = ControllerDeviceEthernet(york,'143.106.230.104',80)
crtlLed.execute()
time.sleep(1)
#controller.execute()




time.sleep(3)

led.status = 0

crtlLed.execute()
york.status = 'off'
#controller.execute()