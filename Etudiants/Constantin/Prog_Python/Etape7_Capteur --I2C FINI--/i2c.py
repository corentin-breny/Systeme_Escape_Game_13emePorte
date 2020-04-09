#!usr/bin/python2.7

import smbus
import time
from threading import Thread, RLock

bus=smbus.SMBus(1)

arduinos = [
        # {'id': 1, 'address': 0x12, 'mechanism_status': False, 'actuator_status' : {'S_Echiquier': False}, 'as_timer' : 0, 'sensor_data' : {'C_EffetHall1': 0, 'C_EffetHall2': 0}, 'sd_timer': 0, 'ordre' : False},
        # {'id': 2, 'address': 0x13, 'mechanism_status': False, 'actuator_status' : {'S_Lion': False}, 'as_timer' : 0, 'sensor_data' : {'C_EffetHall': 0}, 'sd_timer': 0, 'ordre' : False},
        # {'id': 3, 'address': 0x14, 'mechanism_status': False, 'actuator_status' : {'S_Meuble': False, 'S_Terre': False}, 'as_timer' : 0, 'sensor_data' : {'C_EffetHall': 0}, 'sd_timer': 0, 'ordre' : False},
        {'id': 4, 'address': 0x15, 'mechanism_status': False, 'actuator_status' : {'S_Dragon': False, 'S_Fumee': False, 'S_Led': False, 'S_Feu': False}, 'as_timer' : 0, 'sensor_data' : {'C_Interupteur': False}, 'sd_timer': 0, 'ordre' : True},
        # {'id': 5, 'address': 0x16, 'mechanism_status': False, 'actuator_status' : {'S_Frigo': False, 'S_Fontaine': False, 'S_Led': False, 'S_Eau': False}, 'as_timer' : 0, 'sensor_data' : {'C_Humidite': 0}, 'sd_timer': 0, 'ordre' : False},
        # {'id': 6, 'address': 0x17, 'mechanism_status': False, 'actuator_status' : {'S_Vanne': False, 'S_Chien': False, 'S_Led': False, 'S_Air': False}, 'as_timer' : 0, 'sensor_data' : {'C_Vanne1': False, 'C_Vanne2': False, , 'C_Vanne3': False, 'C_Vanne4': False, 'C_Vanne5': False, 'C_Vanne6': False, 'C_Vanne7': False, 'C_Bouton': False}, 'sd_timer': 0, 'ordre' : False},
        # {'id': 7, 'address': 0x18, 'mechanism_status': False, 'actuator_status' : {'S_Katana': False}, 'as_timer' : 0, 'sensor_data' : {'C_Interupteur': False}, 'sd_timer': 0, 'ordre' : False},
        {'id': 8, 'address': 0x19, 'mechanism_status': False, 'actuator_status' : {'S_Tableau': False, 'S_LedV': False, 'S_LedR': True}, 'as_timer' : 0, 'sensor_data' : {'C_Poids': 0}, 'sd_timer': 0, 'ordre' : False}#,
        # {'id': 9, 'address': 0x20, 'mechanism_status': False, 'actuator_status' : {'S_Terre': False, 'S_Feu': False, 'S_Eau': False, 'S_Air': False,'S_Led': False, 'S_PorteFinal': False}, 'as_timer' : 0, 'sensor_data' : {'C_Bouton': False}, 'sd_timer': 0, 'ordre' : False}
     ]

verrou = RLock()

#Thomas :
        #Structure du msgSocket : [noMecanisme][T ou F ou X][T ou F ou X][T ou F ou X] (Si il y a 3 actionneurs) ex : 8TXX

def get_socketMessage():
    """
    get socket message
    """
    #Thomas : Ecrire code

    # NE PAS OUBLIER CETTE PARTIE :
    # if socket_message != ""
        # for arduino in arduinos :
            # if socket_message[0] == arduino['id']:
                # arduino['ordre'] = True

    socket_message = "4TXXX"

    return socket_message

def send_SDtoDataBase(arduino_id, sensor_name, sensor_data):
    """
    send sensor data to DataBase
    """
    #Corentin : Ecrire code


def send_AStoDataBase(arduino_id, actuator_name, actuator_status):
    """
    send actuator status to DataBase
    """
    #Corentin : Ecrire code


def send_MStoDataBase(arduino_id, mechanism_status):
    """
    send mechanism status to DataBase
    """
    #Corentin : Ecrire code


class ASTimer(Thread):

    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino

    def run(self):
        while self.arduino['as_timer'] < 60 :
            time.sleep(1)
            self.arduino['as_timer'] += 1


class SDTimer(Thread):

    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino

    def run(self):
        while self.arduino['sd_timer'] < 3 :
            time.sleep(1)
            self.arduino['sd_timer'] += 1


def get_sensor_data(message, arduino):
    """
    manages data sensor reception of a Mechanism
    """
    sd_timer_reset = 0
    console_message =""
    
    cpt = 8
    integer = 0
    for sensor_name in arduino['sensor_data'] :
            
        if message[cpt] == "T" and arduino['sensor_data'][sensor_name] != True :
            arduino['sensor_data'][sensor_name] = True
            console_message = "CHANGE"
            sd_timer_reset = 1
            send_SDtoDataBase(arduino['id'], sensor_name, arduino['sensor_data'][sensor_name])#Fonction Corentin
            
        if message[-1] == "X":
            l = []
            for (key,character) in enumerate(message) :
                if key > cpt-1 :
                    if character == "X" :
                        break
                    else :
                        l.append(character)
                        cpt += 1

            data_sensor="".join(l)
            if data_sensor != arduino['sensor_data'][sensor_name] :
                arduino['sensor_data'][sensor_name] = data_sensor
                sd_timer_reset = 1
                send_SDtoDataBase(arduino['id'], sensor_name, arduino['sensor_data'][sensor_name])#Fonction Corentin
        
        if arduino['sd_timer'] >= 3 :
            console_message = "5s elapsed since last send"
            sd_timer_reset = 1
            send_SDtoDataBase(arduino['id'], sensor_name, arduino['sensor_data'][sensor_name])#Fonction Corentin

        cpt += 1
        
    if sd_timer_reset == 1 :
        print("Mechanism %s : sensor data : %s --- database update ---" %(arduino['id'], console_message))
        arduino['sd_timer'] = 0
        sd_timer_thread = SDTimer(arduino)
        sd_timer_thread.start()


def get_actuator_status(message, arduino):
    """
    manages actuator status reception of a Mechanism
    """
    as_timer_reset = 0
    actuator_ok = 0
    console_message = ""
    
    cpt = 3
    for actuator_name in arduino['actuator_status'] :
        
        if actuator_name == True : 
            actuator_ok += 1
        
        if message[cpt] == "T" and arduino['actuator_status'][actuator_name] != True :
            arduino['actuator_status'][actuator_name] = True
            console_message = "CHANGE"
            as_timer_reset = 1
            send_AStoDataBase(arduino['id'], actuator_name, arduino['actuator_status'][actuator_name])#Fonction Corentin
        
        elif arduino['as_timer'] >= 60 :
            console_message = "60s elapsed since last send"
            as_timer_reset = 1
            send_AStoDataBase(arduino['id'], actuator_name, arduino['actuator_status'][actuator_name])#Fonction Corentin

        cpt+=1
    
    if actuator_ok == len(arduino['actuator_status']) :
        arduino['mechanism_status'] = True
    
    elif actuator_ok != len(arduino['actuator_status']) :
        arduino['mechanism_status'] = False
    
    if as_timer_reset == 1 :
        send_MStoDataBase(arduino['id'], arduino['mechanism_status'])#Fonction Corentin
        print("Mechanism %s : actuator status : %s --- database update ---" %(arduino['id'], console_message))
        arduino['as_timer'] = 0
        as_timer_thread = ASTimer(arduino)
        as_timer_thread.start()


def read_message(answer) :
    """
    convert an answer's Arduino to String
    """
    l = []
    for letter in answer:
        if letter == 255:
            break
        l.append(chr(letter))

    message="".join(l)

    return message


def convertStrToListHex(strCharacter):
   lstHex = []
   for c in strCharacter:
      lstHex.append(ord(c))
   return lstHex


def send_order(arduino):
    if arduino['ordre'] == True :
        socket_message = get_socketMessage()#"4TXXX" Fonction Thomas
        order = convertStrToListHex(socket_message)
        bus.write_i2c_block_data(arduino['address'], 0, order)
        arduino['ordre'] = False
        print("Mechanism %s : ORDER SENT" %arduino['id'])


class ArduinoCom(Thread):

    def __init__(self, arduino) :
        Thread.__init__(self)
        self.arduino = arduino

    def run(self):
        #while True: #A decommenter
        i = 0 #A supprimer
        while i < 10 : #A supprimer
            with verrou :

                print("Arduino communication")

                send_order(self.arduino)

                answer=bus.read_i2c_block_data(self.arduino['address'],0x32)#asFFFTsdF Mecanism4 asFFXXsd0X Mecanism8

                message = read_message(answer)

                get_actuator_status(message, self.arduino)
                
                get_sensor_data(message, self.arduino)

                time.sleep(1)

            i += 1 #A supprimer


def execute():
    """
    get mechanism and actuator status and gives orders if necessary
    """
    for arduino in arduinos :

        as_timer_thread = ASTimer(arduino)
        as_timer_thread.start()

        sd_timer_thread = SDTimer(arduino)
        sd_timer_thread.start()

        thread = ArduinoCom(arduino)
        thread.start()


def main():

    execute()

main()
