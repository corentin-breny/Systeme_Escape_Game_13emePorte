#!usr/bin/python2.7

import smbus
import time
from threading import Thread, RLock

bus=smbus.SMBus(1)

arduinos = [
        # {'id': 1, 'address': 0x12, 'mechanism_status': "NOT_OK", 'ms_timer': 0, 'actuator_status' : {'S_Echiquier':"NOT_OK"}, 'as_timer' : 0},
        # {'id': 2, 'address': 0x13, 'mechanism_status': "NOT_OK", 'ms_timer': 0, 'actuator_status' : {'S_Lion':"NOT_OK"}, 'as_timer' : 0},
        # {'id': 3, 'address': 0x14, 'mechanism_status': "NOT_OK", 'ms_timer': 0, 'actuator_status' : {'S_Meuble':"NOT_OK",'S_Terre':"NOT_OK"}, 'as_timer' : 0},
        {'id': 4, 'address': 0x15, 'mechanism_status': "NOT_OK", 'ms_timer': 0, 'actuator_status' : {'S_Dragon':"NOT_OK",'S_Fumee':"NOT_OK",'S_Led':"NOT_OK",'S_Feu':"NOT_OK"}, 'as_timer' : 0},
        # {'id': 5, 'address': 0x16, 'mechanism_status': "NOT_OK", 'ms_timer': 0, 'actuator_status' : {'S_Frigo':"NOT_OK",'S_Fontaine':"NOT_OK", 'S_Eau':"NOT_OK"}, 'as_timer' : 0},
        # {'id': 6, 'address': 0x17, 'mechanism_status': "NOT_OK", 'ms_timer': 0, 'actuator_status' : {'S_Vanne':"NOT_OK",'S_Chien':"NOT_OK",'S_Led':"NOT_OK",'S_Air':"NOT_OK"}, 'as_timer' : 0},
        # {'id': 7, 'address': 0x18, 'mechanism_status': "NOT_OK", 'ms_timer': 0, 'actuator_status' : {'S_Katana':"NOT_OK"}, 'as_timer' : 0},
        {'id': 8, 'address': 0x19, 'mechanism_status': "NOT_OK", 'ms_timer': 0, 'actuator_status' : {'S_Tableau':"NOT_OK",'S_Led':"NOT_OK"}, 'as_timer' : 0}#,
        # {'id': 9, 'address': 0x20, 'mechanism_status': "NOT_OK", 'ms_timer': 0, 'actuator_status' : {'S_PorteFinal':"NOT_OK"}, 'as_timer' : 0}
     ]

verrou = RLock()

def send_AStoDataBase(id_arduino, actuator_name, actuator_status):
    """
    send actuator status to DataBase
    """
    #Corentin : Ecrire code

def send_MStoDataBase(id_arduino, mechanism_status):
    """
    send mechanism status to DataBase
    """
    #Corentin : Ecrire code

class ASTimer(Thread):

    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino

    def run(self):
        while self.arduino['as_timer'] < 5 :
            time.sleep(1)
            self.arduino['as_timer'] += 1

class MSTimer(Thread):

    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino

    def run(self):
        while self.arduino['ms_timer'] < 60 :
            time.sleep(1)
            self.arduino['ms_timer'] += 1

def get_actuator_status(message, arduino):
    """
    manages actuator status reception of a Mechanism
    """
    as_timer_reset = 0

    cpt = 5
    for actuator_name in arduino['actuator_status'] :

        if arduino['as_timer'] >= 5 :
            message_console = "actuator status : 5s elapsed since last send"
            as_timer_reset = 1
            send_AStoDataBase(arduino['id'], actuator_name, arduino['actuator_status'][actuator_name])#Fonction Corentin

        if message[cpt] == "T" and arduino['actuator_status'][actuator_name] != "OK":
            arduino['actuator_status'][actuator_name] = "OK"
            message_console = "ACTUATOR STATUS HAS CHANGED"
            as_timer_reset = 1
            send_AStoDataBase(arduino['id'], actuator_name, arduino['actuator_status'][actuator_name])#Fonction Corentin

        cpt+=1

    if as_timer_reset == 1 :
        print("Mechanism %s : %s --- Envoie au serveur ---"  %(arduino['id'], message_console))
        arduino['as_timer'] = 0
        as_timer_thread = ASTimer(arduino)
        as_timer_thread.start()


def get_mechanism_status(message, arduino):
    """
    manages mechanism status reception of a Mechanism
    """
    ms_timer_reset = 0

    if arduino['ms_timer'] >= 60 :
        message_console = "mechanism status : 60s elapsed since last send"
        ms_timer_reset = 1

    if message[2] == "T" and arduino['mechanism_status'] != "OK" :
        arduino['mechanism_status'] = "OK"
        message_console = "MECHANISM STATUS HAS CHANGED"
        ms_timer_reset = 1

    if ms_timer_reset == 1 :
        print("Mechanism %s : %s --- Envoie au serveur ---"  %(arduino['id'], message_console))
        arduino['ms_timer'] = 0
        ms_timer_thread = MSTimer(arduino)
        ms_timer_thread.start()
        send_MStoDataBase(arduino['id'], arduino['mechanism_status'])#Fonction Corentin


def read_message(answer) :
    """
    convert an answer's Arduino to String
    """
    l = []
    for letter in answer:
        if letter==255:
            break
        l.append(chr(letter))

    message="".join(l)

    return message


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
                bus.write_byte(self.arduino['address'],1)
                time.sleep(1)

                answer=bus.read_i2c_block_data(self.arduino['address'],0x32)

                message = read_message(answer)

                get_mechanism_status(message, self.arduino)

                get_actuator_status(message, self.arduino)

            i += 1 #A supprimer


def get_status():
    """
    get mechanism and actuator status of the Mechanism
    """
    for arduino in arduinos :

        as_timer_thread = ASTimer(arduino)
        as_timer_thread.start()

        ms_timer_thread = MSTimer(arduino)
        ms_timer_thread.start()

        thread = ArduinoCom(arduino)
        thread.start()


def main():

    get_status()

main()
