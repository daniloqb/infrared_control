from Devices import *

__author__ = 'tic'


york = AirConditioner(mode='cool', temp='24', fan='auto', sweep='off')

york.info()
print york.getIRCode()


york.setSweep('on')
print york.getIRCode()
york.setStatus('off')
print york.getIRCode()