from PyCRC.CRC16 import CRC16
import binascii


code_bin ='0001000000001000111000000100000000000010000100001000000010000000010000000011011000000000000000000000000000000000001101110011011100011011'

list_bin = list()
list_bin_r = list()
list_hex_r = list()


list_bin = [code_bin[i:i+8] for i in range(0,len(code_bin),8)]



for value in list_bin:
    l_aux = list(reversed(list(value)))
    s_aux = ''
    for bit in l_aux:
        s_aux += bit
    list_bin_r.append(s_aux)

list_hex = map(lambda b: hex(int(b,2)),list_bin)
list_hex_r = map(lambda b: hex(int(b,2)),list_bin_r)

for index in range(len(list_hex)):
    if len(list_hex[index]) < 4:
        list_hex[index] = '0x0'+list_hex[index][2:]

for index in range(len(list_hex_r)):
    if len(list_hex_r[index]) < 4:
        list_hex_r[index] = '0x0'+list_hex_r[index][2:]

code = ''

for h in range(0,len(list_hex_r)-3):
    code += list_hex_r[h][2::]


target = binascii.unhexlify(code)
crc = hex((CRC16().calculate(target)))
crc_t = 0


print crc

print code
print list_bin
print list_bin_r
print list_hex
print list_hex_r
