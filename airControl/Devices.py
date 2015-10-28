import socket
import binascii
import time
import serial
from PyCRC.CRC16 import CRC16

__author__ = 'tic'
__version__ = '20151001'

class Device(object):
    pass


class LED(Device):

    def __init__(self,status=0):
        self.__status = status

    def setStatus(self,status):
        self.__status = status

    def getStatus(self):
        return self.__status

    def getCode(self):
        return '5 ' + str(self.__status)


    status = property(getStatus,setStatus)


class AirConditioner(Device):

    '''
    #Classe para gerenciamento do ar condicionado
    '''

    # ____d_config e um dicionario com as configuracoes padroes do dispositivo
    # b0, b1, b2, b3, b4, b5 -- sao os cabecalhos do codigo infravermelho
    # b12 -- ainda nao foi decodificado, contudo sempre apresenta o valor 0
    # b14 -- possui um valor constante em todos os comandos e nao entra no calculo do CRC16
    # crc_lsb e crc_msb -- sao os campos calculados pelo CRC16.


    __d_infraredCodes = {'code_bin':'',
                         'code_hex': '',
                         'code_int':''}

    __d_config = {
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


    # __d_act esta relacionado com o tipo de operacao do ar condicionado

    __d_act = {
        'normal': '00000001',
        'clear': '00000111',
        'filter': '00001111',
        'sleep': '00001000',
        'offtimer': '00100110',
        'ontimer': '00110110'
    }

    # __d_status possui os valores de ligado e desligado do dispositivo

    __d_status = {
        'on': '0001',
        'off': '0000'
    }

    # __d_mode descreve os modos de operacao possiveis do dispositivo

    __d_mode = {
        'cool': '00000010',
        'dry': '00000011',
        'fan': '00000100'
    }


    # __d_fan controla as velocidades de operacao da ventoinha

    __d_fan = {
        '01': '0001',
        '02': '0010',
        '03': '0011',
        'auto': '1000'
    }

    # __d_sweep possui os modos de operacao da paleta de ar
    __d_sweep = {
        'on': '00000001',
        'off': '00000000'
    }


    # __d_temp possui os valores de temperatura possiveis do aparelho

    __d_temp = {
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

    # __d_offtimer esta relacionado ao tempo de desligamento do dispositivo

    __d_offtimer = {
        '0': '00000000'
    }

    # __d_ontimer  esta relacionado ao tempo de acionamento do dispositivo
    __d_ontimer = {
        '0': '00000000'
    }


    #__d_airState -- o status inicial e atual do dispositivo e controlado por estes valores

    __d_airState = {
        'status': 'on',
        'mode': 'cool',
        'fan': 'auto',
        'temp': '24',
        'act': 'normal',
        'sweep': 'on',
        'offtimer': '0',
        'ontimer': '0'
    }

    # inicializa o dispositivo com todos os dados possiveis de configuracao.
    # caso os valores nao forem passados os valores padrao serao atribuidos
    def __init__(self,
                 status=__d_airState['status'],
                 mode=__d_airState['mode'],
                 fan=__d_airState['fan'],
                 temp=__d_airState['temp'],
                 act=__d_airState['act'],
                 sweep=__d_airState['sweep'],
                 offtimer=__d_airState['offtimer'],
                 ontimer=__d_airState['ontimer']):

        self.setStatus(status)
        self.setMode(mode)
        self.setFan(fan)
        self.setTemp(temp)
        self.setAct(act)
        self.setSweep(sweep)
        self.setOfftimer(offtimer)
        self.setOntimer(ontimer)

        self.__generateIRCode()


    # Sera utilizado sets para atribuir valores pois so serao aceitos os valores que tiverem referencia nos seus respe
    #ctivos dicionarios
    def setStatus(self, status):
        if self.__d_status.has_key(status):
            self.__d_airState['status'] = status

            self.__generateIRCode()

    def setMode(self, mode):
        if self.__d_mode.has_key(mode):
            self.__d_airState['mode'] = mode
            self.__generateIRCode()

    def setFan(self, fan):
        if self.__d_fan.has_key(fan):
            self.__d_airState['fan'] = fan
            self.__generateIRCode()

    def setTemp(self, temp):
        if self.__d_temp.has_key(temp):
            self.__d_airState['temp'] = temp
            self.__generateIRCode()

    def setFan(self, fan):
        if self.__d_fan.has_key(fan):
            self.__d_airState['fan'] = fan
            self.__generateIRCode()

    def setAct(self, act):
        if self.__d_act.has_key(act):
            self.__d_airState['act'] = act
            self.__generateIRCode()

    def setSweep(self, sweep):
        if self.__d_sweep.has_key(sweep):
            self.__d_airState['sweep'] = sweep
            self.__generateIRCode()

    def setOfftimer(self, offtimer):
        if self.__d_offtimer.has_key(offtimer):
            self.__d_airState['offtimer'] = offtimer
            self.__generateIRCode()

    def setOntimer(self, ontimer):
        if self.__d_ontimer.has_key(ontimer):
            self.__d_airState['ontimer'] = ontimer
            self.__generateIRCode()

    def info(self):
        for k, v in self.__d_airState.iteritems():
            print '%-10s:  %-10s' % (k.upper(), v)


    def getStatus(self):
        return self.__d_airState['status']

    def getMode(self):
        return self.__d_airState['mode']

    def getFan(self):
        return self.__d_airState['fan']

    def getTemp(self):
        return self.__d_airState['temp']

    def getAct(self):
        return self.__d_airState['act']


    def getSweep(self):
        return self.__d_airState['sweep']

    def getOfftimer(self):
        return self.__d_airState['offtimer']

    def getOntimer(self):
        return self.__d_airState['ontimer']

    def getCode(self, type='int'):
        if type == 'int':
            return '2 ' + self.__d_infraredCodes['code_int']
        elif type == 'hex':
            return self.__d_infraredCodes['code_hex']
        elif type == 'bin':
            return  self.__d_infraredCodes['code_bin']
        else:
            return None



    def __generateIRCode(self):

        # Primeira etapa sera gerar um codigo binario de 136 bits com as informacoes do modo de operacao
        # nesta primeira etapa nao inclui os 03 ultimos bytes. Estao somente os bytes necessarios para o calculo
        # do CRC16
        #
        # As strings serao concatenadas
        # Configuracoes de cabecalho

        code = self.__d_config['b0'] + self.__d_config['b1'] + self.__d_config['b2'] + self.__d_config['b3'] + \
               self.__d_config['b4'] + self.__d_config['b5']

        # Configuracoes dos modos de operacao
        code += self.__d_act[self.__d_airState['act']] + self.__d_status[self.__d_airState['status']] + \
                self.__d_fan[self.__d_airState['fan']] + self.__d_mode[self.__d_airState['mode']]+\
                self.__d_temp[self.__d_airState['temp']] + self.__d_offtimer[self.__d_airState['offtimer']] + \
                self.__d_ontimer[self.__d_airState['ontimer']]

        # Configuracao do byte 12 ainda nao descoberto e o final dos modos de operacao
        code += self.__d_config['b12'] + self.__d_sweep[self.__d_airState['sweep']]


        # Nesta etapa o codigo binario sera transformado em hexadecimal que sera utilizado na conversao para caracteres
        # Sera recuperado blocos de 8 bits do codigo em binario, transformado em inteiro e depois em uma string hexadecimal
        # Da string hexadecimal sera retirado os dois primeiros caracteres 0x e concatenado em uma unica string code_hex
        code_hex = ''
        for index in range(0, len(code), 8):
            v_hex = hex(int(code[index:index + 8], 2), )[2::]
            if len(v_hex) < 2:
                v_hex = '0' + v_hex
            code_hex += v_hex

        # Nesta etapa o codigo hexadecimal sera transformado em uma cadeia de caracteres
        target = binascii.unhexlify(code_hex)

        # E essa cadeia de caracteres sera utilizada para calcular o CRC do codigo
        crc = hex((CRC16().calculate(target)))

        # O valor de CRC sera dividido em duas partes de 8 bits cada e sera guardada no dicionario de configuracoes
        self.__d_config['crc_lsb' ]= bin(int(crc[4:6],16))[2::].zfill(8)
        self.__d_config['crc_msb' ]= bin(int(crc[2:4],16))[2::].zfill(8)

        # Nesta etapa os valores da constante do byte 14 e dos bits de CRC serao acrescentados ao codigo binario.
        code += self.__d_config['b14'] + self.__d_config['crc_lsb'] + self.__d_config['crc_msb']


        # Nesta etapa serao gerados os codigos definitivos que poderao ser enviados para o dispositivo

        # Primeiro serao inicializadas as listas e as variaveis de controle
        list_bin = [code[i:i+8] for i in range(0,len(code),8)]  # separa a string binaria em blocos de 8 bits
        list_bin_r = list()
        list_hex_r = list()
        list_code_int = list()
        code_hex_r = ''

        # Para cada byte na lista de bytes, transforma o byte em uma lista e coloca em ordem reversa
        # Depois junta todos os bits da lista novamente e adiciona na lista de bytes reversos
        for value in list_bin:
            l_aux = list(reversed(list(value)))
            list_bin_r.append(''.join(l_aux))

        # Sera gerada uma lista reversa em hexadecimal
        list_hex_r = map(lambda b: hex(int(b,2)),list_bin_r)
        # Nesta parte sera ajustado o numero hexadecimal que possuir somente uma casa. Duas casas sao o ideal
        for index in range(len(list_hex_r)):
            if len(list_hex_r[index]) < 4:
                list_hex_r[index] = '0x0'+list_hex_r[index][2:]

        # Nesta Etapa sera gerado o codigo hexadecimal reverso que podera ser utilizado para enviar o sinal infravermelho
        for h in range(0,len(list_hex_r)):
            code_hex_r +=  list_hex_r[h][2::]

        # Agora sera gerado o codigo em inteiro que pode ser usado como uma string passado para o dispositivo
        for index in range(0,len(code_hex_r),8):
            list_code_int.append(str(int(code_hex_r[index:index+8],16)))


        # Estes codigos serao salvos no dicionario de codigos
        self.__d_infraredCodes['code_hex'] = code_hex_r
        self.__d_infraredCodes['code_int'] = ' '.join((list_code_int))
        self.__d_infraredCodes['code_bin'] = ''.join(list_bin_r)

    # Secao das propriedades
    status   = property(getStatus,setStatus)
    mode     = property(getMode,setMode)
    temp     = property(getTemp,setTemp)
    fan      = property(getFan,setFan)
    act      = property(getAct,setAct)
    sweep    = property(getSweep,setSweep)
    offtimer = property(getOfftimer,setOfftimer)
    ontimmer = property(getOntimer,setOntimer)
    # fim da classe


class ControllerDeviceCOM:

    def __init__(self, device, port, baudrate):
        #self.device = Device()
        self.device = device
        self.port = port
        self.baudrate = baudrate

    def execute(self):
        code = self.device.getCode()
        #code = '3 ' + code

        print 'Connecting to {} with baudrate {}'.format(self.port,self.baudrate)
        comport = serial.Serial(self.port,self.baudrate)
        time.sleep(1.8)

        print('Sending code to device\n {}'.format(code))
        comport.write(code)
        time.sleep(0.5)
        VALUE_SERIAL=comport.readline()
        print '\nRetorno da serial: %s' % (VALUE_SERIAL)

        comport.close()

class ControllerDeviceEthernet:
    def __init__(self,device,hostname,port):
        self.device = device
        self.hostname = hostname
        self.port = port

    def execute(self):
        code = self.device.getCode()
       # code = '3 ' + self.device.getCode()
        #code = self.device.getIRCode()
        code +='\n\n\n'


        print 'Connecting to {} on port {}'.format(self.hostname, self.port)
        tcp = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

        tcp.connect((self.hostname,self.port))

        tcp.send(code)

        st = tcp.recv(1024)
        while (st):
            print st
            st = tcp.recv(1024)
        tcp.close()