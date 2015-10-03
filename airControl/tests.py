from Devices import *

__author__ = 'tic'


york = AirConditioner(mode='cool', temp='24', fan='auto', sweep='off')

york.info()
print york.getIRCode()

controller = ControllerDeviceCOM(york,'/dev/ttyUSB0',9600)

controller.execute()


#time.sleep(5)

#york.setStatus('off')

#controller.execute()