import serial

comport = serial.Serial('/dev/ttyACM0',115200)

while True:

   print comport.readline()
