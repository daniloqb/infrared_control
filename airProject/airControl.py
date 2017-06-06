import binascii
import time
import serial
from PyCRC.CRC16 import CRC16

d_config = {
    'b0': '00001000',
    'b1': '00010000',
    'b2': '00000111',
    'b3': '00000010',
    'b4': '01000000',
    'b5': '00001000',
    'b12': '00000000',
    'b14': '11101100',
    'crc_lsb': '',
    'crc_msb': ''
}

d_act = {
    'normal': '00000001',
    'clear': '00000111',
    'filter': '00001111',
    'sleep': '00001000',
    'offtimer': '00100110',
    'ontimer': '00110110'
}

d_status = {
    'on': '0001',
    'off': '0000'
}

d_mode = {
    'cool': '00000010',
    'dry': '00000011',
    'fan': '00000100'
}

d_fan = {
    '01': '0001',
    '02': '0010',
    '03': '0011',
    'auto': '1000'
}

d_sweep = {
    'on': '00000001',
    'off': '00000000'
}

d_temp = {
    '16': '01000000',
    '17': '01000100',
    '18': '01001000',
    '19': '01001100',
    '20': '01010000',
    '21': '01010100',
    '22': '01011000',
    '23': '01011100',
    '24': '01100000',
    '25': '01100100',
    '26': '01101000',
    '27': '01101100',
    '28': '01110000',
    '29': '01110100',
    '30': '01111000',
    '31': '01111100',
    '32': '10000000'
}

d_offtimer = {
    '0': '00000000'
}

d_ontimer = {
    '0': '00000000'
}

d_airState = {
    'status': 'on',
    'mode': 'cool',
    'fan': 'auto',
    'temp': '26',
    'act': 'normal',
    'sweep': 'on',
    'offtimer': '0',
    'ontimer': '0'
}

code = d_config['b0'] + d_config['b1'] + d_config['b2'] + d_config['b3'] + d_config['b4'] + d_config['b5']
code += d_act[d_airState['act']] + d_status[d_airState['status']] + d_fan[d_airState['fan']] + d_mode[
    d_airState['mode']]
code += d_temp[d_airState['temp']] + d_offtimer[d_airState['offtimer']] + d_ontimer[d_airState['ontimer']]
code += d_config['b12'] + d_sweep[d_airState['sweep']]

code_hex = ''
for index in range(0, len(code), 8):
    v_hex = hex(int(code[index:index + 8], 2), )[2::]
    if len(v_hex) < 2:
        v_hex = '0' + v_hex
    code_hex += v_hex

target = binascii.unhexlify(code_hex)
crc = hex((CRC16().calculate(target)))

d_config['crc_lsb' ]= bin(int(crc[4:6],16))[2::].zfill(8)
d_config['crc_msb' ]= bin(int(crc[2:4],16))[2::].zfill(8)

code += d_config['b14'] + d_config['crc_lsb'] + d_config['crc_msb']

list_bin = [code[i:i+8] for i in range(0,len(code),8)]
list_bin_r = list()
list_hex_r = list()
list_code_int = list()
code_hex_r = ''

for value in list_bin:
    l_aux = list(reversed(list(value)))
    s_aux = ''
    for bit in l_aux:
        s_aux += bit
    list_bin_r.append(s_aux)


list_hex_r = map(lambda b: hex(int(b,2)),list_bin_r)

for index in range(len(list_hex_r)):
    if len(list_hex_r[index]) < 4:
        list_hex_r[index] = '0x0'+list_hex_r[index][2:]


for h in range(0,len(list_hex_r)):
    code_hex_r +=  list_hex_r[h][2::]


for index in range(0,len(code_hex_r),8):
    list_code_int.append(str(int(code_hex_r[index:index+8],16)))


data =  ' '.join((list_code_int))
data = '3 ' + data
print data
'''
print code_int
print code_hex
print code, len(code)
print crc

print list_bin
print list_bin_r
print list_hex_r
print code_hex_r

print list_code_int
'''

comport = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(1.8)

print 'Escrevendo na serial'
comport.write(data)
print 'Lendo dados da serial'
VALUE_SERIAL=comport.readline()
print '\nRetorno da serial: %s' % (VALUE_SERIAL)
# Fechando conexao serial
comport.close()