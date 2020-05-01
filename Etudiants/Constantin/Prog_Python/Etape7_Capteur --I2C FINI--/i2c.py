#!usr/bin/python2.7

import smbus
import time
from threading import Thread, RLock

bus=smbus.SMBus(1)

arduinos = [
        # {'id': 1, 'address': 0x12, 'mechanism_status': False, 
        # 'actuator_status' : {'S_Echiquier': False}, 'as_timer' : 0, 
        # 'sensor_data' : {'C_EffetHall1': 0, 'C_EffetHall2': 0}, 'sd_timer': 0, 
        # 'ordre' : False},
        
        # {'id': 2, 'address': 0x13, 'mechanism_status': False, 
        # 'actuator_status' : {'S_Lion': False}, 'as_timer' : 0, 
        # 'sensor_data' : {'C_EffetHall': 0}, 'sd_timer': 0, 
        # 'ordre' : False},
        
        # {'id': 3, 'address': 0x14, 'mechanism_status': False, 
        # 'actuator_status' : {'S_Meuble': False, 'S_Terre': False}, 'as_timer' : 0, 
        # 'sensor_data' : {'C_EffetHall': 0}, 'sd_timer': 0, 
        # 'ordre' : False},
        
        {'id': 4, 'address': 0x15, 'mechanism_status': False, 
        'actuator_status' : {'S_Dragon': False, 'S_Fumee': False, 'S_Led': False, 'S_Feu': False}, 
        'as_timer' : 0, 'sensor_data' : {'C_Interupteur': False}, 'sd_timer': 0, 
        'ordre' : False},
        
        # {'id': 5, 'address': 0x16, 'mechanism_status': False, 
        # 'actuator_status' : {'S_Frigo': False, 'S_Fontaine': False, 'S_Led': False, 'S_Eau': False}, 'as_timer' : 0, 
        # 'sensor_data' : {'C_Humidite': 0}, 'sd_timer': 0, 
        # 'ordre' : False},
        
        # {'id': 6, 'address': 0x17, 'mechanism_status': False, 
        # 'actuator_status' : {'S_Vanne': False, 'S_Chien': False, 'S_Led': False, 'S_Air': False}, 'as_timer' : 0, 
        # 'sensor_data' : {'C_Vanne1': False, 'C_Vanne2': False, 'C_Vanne3': False, 'C_Vanne4': False, 'C_Vanne5': False, 'C_Vanne6': False, 'C_Vanne7': False, 'C_Bouton': False}, 'sd_timer': 0, 
        # 'ordre' : False},
        
        # {'id': 7, 'address': 0x18, 'mechanism_status': False, 
        # 'actuator_status' : {'S_Katana': False}, 'as_timer' : 0, 
        # 'sensor_data' : {'C_Interupteur': False}, 'sd_timer': 0, 
        # 'ordre' : False},
        
        {'id': 8, 'address': 0x19, 'mechanism_status': False, 
        'actuator_status' : {'S_Tableau': False, 'S_Led': False}, 'as_timer' : 0, 
        'sensor_data' : {'C_Poids': 0}, 'sd_timer': 0, 
        'ordre' : False}#,
        
        # {'id': 9, 'address': 0x20, 'mechanism_status': False, 
        # 'actuator_status' : {'S_Led': False, 'S_PorteFinal': False}, 'as_timer' : 0, 
        # 'sensor_data' : {'C_Bouton': False}, 'sd_timer': 0, 
        # 'ordre' : False}
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

    socket_message = "4TXXX" #A Supprimer

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
    """
    timer thread about actuator status
    """
    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino

    def run(self):
        while self.arduino['as_timer'] <= 60 :              #Tant que le timer est inferieur ou egale à 60s
            time.sleep(1)                                   #Laisser 1s s'ecouler
            self.arduino['as_timer'] += 1                   #Incrementer la valeur du timer


class SDTimer(Thread):
    """
    timer thread about sensor data
    """
    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino

    def run(self):
        while self.arduino['sd_timer'] <= 3 :               #Tant que le timer est inferieur ou egale à 3s
            time.sleep(1)                                   #Laisser 1s s'ecouler
            self.arduino['sd_timer'] += 1                   #Incrementer la valeur du timer


def get_sensor_int_data(message, cpt):
    """
    get sensor with digital data
    """
    l = []
    for (key,character) in enumerate(message) :
        if key > cpt-1 :
            if character == "X" :
                break
            else :
                l.append(character)
                cpt += 1

    data_sensor="".join(l)
    
    return (data_sensor,cpt)


def get_sensor_data(message, arduino):
    """
    manages data sensor reception of a Mechanism
    """
    sd_timer_reset = False
    console_message =""
    
    cpt = 8
    integer = 0
    for sensor_name in arduino['sensor_data'] :                         #Pour chaque capteur du mecanisme
            
        if message[cpt] == "T"                                          #Si le capteur a une valeur boolean 
        and arduino['sensor_data'][sensor_name] != True :               #Et si le capteur selectionne vient d'etre valide
            arduino['sensor_data'][sensor_name] = True                  #On change la valeur du capteur dans le dictionnaire
            sd_timer_reset = True                                       #On reset le timer de 3s
            send_SDtoDataBase(arduino['id'], sensor_name, arduino['sensor_data'][sensor_name])#On envoie la valeur en BDD       #Fonction Corentin
            console_message = "CHANGE"
            
        if message[-1] == "X":                                          #Si le capteur possede une valeur numerique
            data_sensor,cpt = get_sensor_int_data(message, cpt)         #On recupere la valeur numerique
            if data_sensor != arduino['sensor_data'][sensor_name] :     #Si la valeur numerique vient de changer
                arduino['sensor_data'][sensor_name] = data_sensor       #On change la valeur du capteur dans le dictionnaire
                sd_timer_reset = True                                   #On reset le timer de 3s
                send_SDtoDataBase(arduino['id'], sensor_name, arduino['sensor_data'][sensor_name])#On envoie la valeur en BDD   #Fonction Corentin
                console_message = "CHANGE"
        
        if arduino['sd_timer'] >= 3 :                                   #Si le timer a atteint les 3s
            sd_timer_reset = True                                       #On reset le timer de 3s
            send_SDtoDataBase(arduino['id'], sensor_name, arduino['sensor_data'][sensor_name])#On envoie la valeur en BDD       #Fonction Corentin
            console_message = "5s elapsed since last send"

        cpt += 1
        
    if sd_timer_reset == True :
        arduino['sd_timer'] = 0
        sd_timer_thread = SDTimer(arduino)
        sd_timer_thread.start()
        print("Mechanism %s : sensor data : %s --- database update ---" %(arduino['id'], console_message))


def get_actuator_status(message, arduino):
    """
    manages actuator status reception of a Mechanism
    """
    as_timer_reset = False
    actuator_ok = 0
    console_message = ""
    
    cpt = 3
    for actuator_name in arduino['actuator_status'] :                   #Pour chaque actionneur du mecanisme
        
        if actuator_name == True :                                      #Si l'actionneur est valide
            actuator_ok += 1                                            #On incremente le nbre d'actionneur du mecanisme qui sont valide
        
        if message[cpt] == "T" 
        and arduino['actuator_status'][actuator_name] != True :         #Si l'actionneur selectionne vient d'etre valide
            arduino['actuator_status'][actuator_name] = True            #On change la valeur de l'actionneur dans le dictionnaire
            as_timer_reset = True                                       #On reset le timer de 60s
            send_AStoDataBase(arduino['id'], actuator_name, arduino['actuator_status'][actuator_name]) #On envoie le statut en BDD                  #Fonction Corentin
            console_message = "CHANGE"
        
        elif arduino['as_timer'] >= 60 :                                #Si le timer a atteint les 60s
            as_timer_reset = True                                       #On reset le timer de 60s
            send_AStoDataBase(arduino['id'], actuator_name, arduino['actuator_status'][actuator_name]) #On envoie le statut en BDD                  #Fonction Corentin
            console_message = "60s elapsed since last send"

        cpt+=1
    
    if actuator_ok == len(arduino['actuator_status']) 
    and arduino['mechanism_status'] == False:                           #Si tous les actionneurs du mecanisme viennent juste d'etre tous valides
        arduino['mechanism_status'] = True                              #On change la valeur de l'etat du mecanisme dans le dictionnaire
    
    elif actuator_ok != len(arduino['actuator_status']) 
    and arduino['mechanism_status'] == True:                            #Si tous les actionneurs du mecanisme ne sont plus valides
        arduino['mechanism_status'] = False                             #On change la valeur de l'etat du mecanisme dans le dictionnaire
    
    if as_timer_reset == True :                                         #Si on reset le timer de 60s
        send_MStoDataBase(arduino['id'], arduino['mechanism_status'])   #On envoie l'etat du mecanisme en BDD                                       #Fonction Corentin
        arduino['as_timer'] = 0
        as_timer_thread = ASTimer(arduino)
        as_timer_thread.start()
        print("Mechanism %s : actuator status : %s --- database update ---" %(arduino['id'], console_message))


def read_message(answer) :
    """
    convert an answer's Arduino(ASCII decimal) to String
    """
    l = []
    for letter in answer:
        if letter == 255:
            break
        l.append(chr(letter))

    message="".join(l)

    return message


def convertStrToListHex(strCharacter):
    """
    convert socket message(String) to Hexadecimal
    """
   lstHex = []
   for c in strCharacter:
      lstHex.append(ord(c))
   return lstHex


def send_order(arduino):
    """
    send order to Arduino
    """
    if arduino['ordre'] == True :                                   #On verifie si la Raspberry a reçu un ordre
        socket_message = get_socketMessage()#"4TXXX"                #On recupere le message socket d'ordre                      #Fonction Thomas
        order = convertStrToListHex(socket_message)                 #On convertit le message socket en Hexadecimal
        bus.write_i2c_block_data(arduino['address'], 0, order)      #On envoie le message socket a l’Arduino assignee
        arduino['ordre'] = False
        print("Mechanism %s : ORDER SENT" %arduino['id'])


class ArduinoCom(Thread):
    """
    Arduino thread
    """
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
