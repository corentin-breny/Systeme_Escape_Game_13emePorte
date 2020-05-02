#!usr/bin/python2.7

import smbus
import time
from threading import Thread, RLock

bus=smbus.SMBus(1)

arduinos = [
        # {'id': 1, 'address': 0x12, 
        # 'mechanism_status': False, 'ms_timer': 0,
        # 'actuator_status' : {'S_Echiquier': False}, 'as_timer' : 0, 
        # 'sensor_data' : {'C_EffetHall1': 0, 'C_EffetHall2': 0}, 'sd_timer': 0, 
        # 'ordre' : 0},
        
        # {'id': 2, 'address': 0x13, 
        # 'mechanism_status': False, 'ms_timer': 0,
        # 'actuator_status' : {'S_Lion': False}, 'as_timer' : 0, 
        # 'sensor_data' : {'C_EffetHall': 0}, 'sd_timer': 0, 
        # 'ordre' : 0},
        
        # {'id': 3, 'address': 0x14, 
        # 'mechanism_status': False, 'ms_timer': 0,
        # 'actuator_status' : {'S_Meuble': False, 'S_Terre': False}, 'as_timer' : 0, 
        # 'sensor_data' : {'C_EffetHall': 0}, 'sd_timer': 0, 
        # 'ordre' : 0},
        
        {'id': 4, 'address': 0x15,  
        'mechanism_status': True,  'ms_timer': 0,
        'actuator_status' : {'S_Dragon': False, 'S_Fumee': False, 'S_Led': False, 'S_Feu': False}, 'as_timer' : 0, 
        'sensor_data' : {'C_Interupteur': False}, 'sd_timer': 0, 
        'ordre' : 0},
        
        # {'id': 5, 'address': 0x16,  
        # 'mechanism_status': False, 'ms_timer': 0,
        # 'actuator_status' : {'S_Frigo': False, 'S_Fontaine': False, 'S_Led': False, 'S_Eau': False}, 'as_timer' : 0, 
        # 'sensor_data' : {'C_Humidite': 0}, 'sd_timer': 0, 
        # 'ordre' : 0},
        
        # {'id': 6, 'address': 0x17, 
        # 'mechanism_status': False, 'ms_timer': 0,
        # 'actuator_status' : {'S_Vanne': False, 'S_Chien': False, 'S_Led': False, 'S_Air': False}, 'as_timer' : 0, 
        # 'sensor_data' : {'C_Vanne1': False, 'C_Vanne2': False, 'C_Vanne3': False, 'C_Vanne4': False, 'C_Vanne5': False, 'C_Vanne6': False, 'C_Vanne7': False, 'C_Bouton': False}, 'sd_timer': 0, 
        # 'ordre' : 0},
        
        # {'id': 7, 'address': 0x18, 
        # 'mechanism_status': False, 'ms_timer': 0,
        # 'actuator_status' : {'S_Katana': False}, 'as_timer' : 0, 
        # 'sensor_data' : {'C_Interupteur': False}, 'sd_timer': 0, 
        # 'ordre' : 0},
        
        # {'id': 8, 'address': 0x19, 
        # 'mechanism_status': False, 'ms_timer': 0,
        # 'actuator_status' : {'S_Tableau': False, 'S_Led': False}, 'as_timer' : 0, 
        # 'sensor_data' : {'C_Poids': 0}, 'sd_timer': 0, 
        # 'ordre' : 0},#8221}#,
        
        # {'id': 9, 'address': 0x20, 
        # 'mechanism_status': False, 'ms_timer': 0,
        # 'actuator_status' : {'S_Led': False, 'S_PorteFinal': False}, 'as_timer' : 0, 
        # 'sensor_data' : {'C_Bouton': False}, 'sd_timer': 0, 
        # 'ordre' : 0}
     ]

verrou = RLock()

#Thomas :
        #Structure du msgSocket : [1 a 9](noMecanisme) [0 ou 1 ou 2](Etat du mecanisme) [0 ou 1 ou 2][0 ou 1 ou 2][0 ou 1 ou 2](Etat des actionneurs)(Si il y a 3 actionneurs) ex : 8221

def get_socketMessage():
    """
    Recuperer le message Socket
    """
    #Thomas : Ecrire code

    # NE PAS OUBLIER CETTE PARTIE :
    # socket_message = 8221
    # for arduino in arduinos :
        # if socket_message[0] == arduino['id']:
            # arduino['ordre'] = socket_message
    

def send_SDtoDataBase(arduino_id, sensor_name, sensor_data):
    """
    Envoyer la valeur d'un capteur en BDD
    """
    #Corentin : Ecrire code


def send_AStoDataBase(arduino_id, actuator_name, actuator_status):
    """
    Envoyer la valeur d'un actionneur en BDD
    """
    #Corentin : Ecrire code


def send_MStoDataBase(arduino_id, mechanism_status):
    """
    Envoyer la valeur d'un mecanisme en BDD
    """
    #Corentin : Ecrire code


class SDTimer(Thread):
    """
    Le thread qui correspond au timer de 3s des capteurs
    """
    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino
        self.running = False

    def run(self):
        self.running = True
        
        while self.running:
            time.sleep(1)                                   #Laisser 1s s'ecouler
            self.arduino['sd_timer'] += 1                   #Incrementer la valeur du timer
            
            if self.arduino['sd_timer'] == 3 :              #Si le timer est a 3s
                self.arduino['sd_timer'] = 0                #On reset le timer
                self.running = False                        #On arrete le thread

class ASTimer(Thread):
    """
    Le thread qui correspond au timer de 60s des actionneurs
    """
    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino

    def run(self):
        self.running = True
        
        while self.running:
            time.sleep(1)                                   #Laisser 1s s'ecouler
            self.arduino['as_timer'] += 1                   #Incrementer la valeur du timer
            
            if self.arduino['as_timer'] == 60 :             #Si le timer est a 60s
                self.arduino['as_timer'] = 0                #On reset le timer
                self.running = False                        #On arrete le thread


class MSTimer(Thread):
    """
    Le thread qui correspond au timer de 60s d'un mecanisme
    """
    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino

    def run(self):
        self.running = True
        
        while self.running:
            time.sleep(1)                                   #Laisser 1s s'ecouler
            self.arduino['ms_timer'] += 1                   #Incrementer la valeur du timer
            
            if self.arduino['ms_timer'] == 60 :             #Si le timer est a 60s
                self.arduino['ms_timer'] = 0                #On reset le timer
                self.running = False                        #On arrete le thread


def get_sensor_int_data(message, cpt):
    """
    Recuperer la valeur numerique d'un capteur
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
    Recuperer la valeur de tous les capteurs d'un mecanisme
    """
    console_message =""
    EnvoieBDD = False
    ResetTimer = False
    
    cpt = 11
    for sensor_name in arduino['sensor_data'] :                         #Pour chaque capteur du mecanisme
        
        if arduino['sd_timer'] == 0 :                                   #Si le timer a ete reset
            sd_timer_thread = SDTimer(arduino)                          #On cree un nouveau thread
            sd_timer_thread.start()                                     #On lance le thread
            EnvoieBDD = True                                            #On envoie la valeur du capteur en BDD
            console_message = "3s elapsed since last send"
            
        #Si le capteur a une valeur boolean True et si le capteur selectionne vient d'etre valide
        if message[cpt] == "T" and arduino['sensor_data'][sensor_name] == False :
            arduino['sensor_data'][sensor_name] = True                  #On change la valeur du capteur dans le dictionnaire
            ResetTimer = True                                           #On reset le timer
            EnvoieBDD = True                                            #On envoie la valeur du capteur en BDD
            console_message = "CHANGE"
        
        #Si le capteur a une valeur boolean False et si le capteur selectionne vient d'etre invalide        
        elif message[cpt] == "F" and arduino['sensor_data'][sensor_name] == True :
            arduino['sensor_data'][sensor_name] = False                 #On change la valeur du capteur dans le dictionnaire
            ResetTimer = True                                           #On reset le timer
            EnvoieBDD = True                                            #On envoie la valeur du capteur en BDD
            console_message = "CHANGE"        

        elif message[-1] == "X":                                        #Si le capteur possede une valeur numerique
            data_sensor,cpt = get_sensor_int_data(message, cpt)         #On recupere la valeur numerique
            if data_sensor != arduino['sensor_data'][sensor_name] :     #Si la valeur numerique vient de changer
                arduino['sensor_data'][sensor_name] = data_sensor       #On change la valeur du capteur dans le dictionnaire
                ResetTimer = True                                       #On reset le timer
                EnvoieBDD = True                                        #On envoie la valeur du capteur en BDD
                console_message = "CHANGE"
        
        cpt += 1
    
    if ResetTimer == True :                                             #Pour reset le timer
        arduino['sd_timer'] = 0                                         #On reset le timer
    
    if EnvoieBDD == True :                                              #Pour envoyer la valeur du capteur en BDD
        for sensor_name in arduino['sensor_data'] :                     #Pour chaque capteur du mecanisme
            send_SDtoDataBase(arduino['id'], sensor_name, arduino['sensor_data'][sensor_name])#On envoie la valeur en BDD            #Fonction Corentin
            
        print("Mechanism %s : sensor data : %s --- database update ---" %(arduino['id'], console_message))


def get_actuator_status(message, arduino):
    """
    Recuperer l'etat de tous les actionneurs d'un mecanisme
    """
    console_message = ""
    EnvoieBDD = False
    ResetTimer = False
    
    cpt = 5
    for actuator_name in arduino['actuator_status'] :                   #Pour chaque actionneur du mecanisme
        
        if arduino['as_timer'] == 0 :                                   #Si le timer a ete reset
            as_timer_thread = ASTimer(arduino)                          #On cree un nouveau thread
            as_timer_thread.start()                                     #On lance le thread
            EnvoieBDD = True                                            #On envoie la valeur de l'actionneur en BDD
            console_message = "60s elapsed since last send"
        
        #Si l'actionneur a une valeur boolean True et si l'actionneur selectionne vient d'etre valide
        if message[cpt] == "T" and arduino['actuator_status'][actuator_name] == False :
            arduino['actuator_status'][actuator_name] = True            #On change la valeur de l'actionneur dans le dictionnaire
            ResetTimer = True                                           #On reset le timer
            EnvoieBDD = True                                            #On envoie la valeur de l'actionneur en BDD
            console_message = "CHANGE"
        
        #Si l'actionneur a une valeur boolean False et si l'actionneur selectionne vient d'etre invalide    
        elif message[cpt] == "F" and arduino['actuator_status'][actuator_name] == True :
            arduino['actuator_status'][actuator_name] = False           #On change la valeur de l'actionneur dans le dictionnaire 
            ResetTimer = True                                           #On reset le timer
            EnvoieBDD = True                                            #On envoie la valeur de l'actionneur en BDD
            console_message = "CHANGE"
        
        cpt+=1
    
    if ResetTimer == True :                                             #Pour reset le timer
        arduino['as_timer'] = 0                                         #On reset le timer
        
    if EnvoieBDD == True :                                              #Pour envoyer la valeur du capteur en BDD
        for actuator_name in arduino['actuator_status'] :               #Pour chaque actionneur du mecanisme

            send_AStoDataBase(arduino['id'], actuator_name, arduino['actuator_status'][actuator_name]) #On envoie le statut en BDD        #Fonction Corentin
        
        print("Mechanism %s : actuator status : %s --- database update ---" %(arduino['id'], console_message))
    


def get_mechanism_status(message, arduino):
    """
    Recuperer l'etat d'un mecanisme
    """
    console_message = ""
    EnvoieBDD = False
    
    if arduino['ms_timer'] == 0 :                                       #Si le timer a ete reset
        ms_timer_thread = MSTimer(arduino)                              #On cree un nouveau thread
        ms_timer_thread.start()                                         #On lance le thread
        EnvoieBDD = True                                                #On envoie la valeur de l'actionneur en BDD
        console_message = "60s elapsed since last send"
    
    #Si le mecanisme a une valeur boolean True et si le mecanisme vient d'etre valide
    if message[2] == "T" and arduino['mechanism_status'] == False :
        arduino['mechanism_status'] = True                              #On change la valeur du mecanisme dans le dictionnaire
        arduino['ms_timer'] = 0                                         #On reset le timer
        EnvoieBDD = True                                                #On envoie la valeur du mecanisme en BDD
        console_message = "CHANGE"
    
    #Si le mecanisme a une valeur boolean False et si le mecanisme vient d'etre invalide
    elif message[2] == "F" and arduino['mechanism_status'] == True : 
        arduino['mechanism_status'] = False                             #On change la valeur du mecanisme dans le dictionnaire
        arduino['ms_timer'] = 0                                         #On reset le timer
        EnvoieBDD = True                                                #On envoie la valeur du mecanisme en BDD
        console_message = "CHANGE"
        
    if EnvoieBDD == True :                                              #Pour envoyer la valeur du capteur en BDD
        send_MStoDataBase(arduino['id'], arduino['mechanism_status'])   #On envoie l'etat du mecanisme en BDD                        #Fonction Corentin 
        
        print("Mechanism %s : mechanism status : %s --- database update ---"  %(arduino['id'], console_message))


def get_message(arduino) :
    """
    Recuperer le message i2c en une chaine de caractere
    """
    answer = bus.read_i2c_block_data(arduino['address'],0x32)
    
    l = []
    for letter in answer:
        if letter == 255:
            break
        l.append(chr(letter))

    message="".join(l)

    return message


def convertStrToListHex(strCharacter):
    """
    Convertir une chaine de caractere en Hexadecimal
    """
    lstHex = []
    for c in strCharacter:
        lstHex.append(ord(c))
    return lstHex


def send_order(arduino):
    """
    Envoyer un ordre a une Arduino
    """
    get_socketMessage()                                                 #Recuperer le dernier message socket                              #Fonction Thomas
    #arduino['ordre'] = 8221 Pour le mecanisme 8
    
    if arduino['ordre'] != 0 :                                          #On veriie si l'Arduino a recu un ordre
        order = convertStrToListHex(arduino['ordre'])                   #On convertit le message socket en Hexadecimal
        bus.write_i2c_block_data(arduino['address'], 0, order)          #On envoie le message socket a l'Arduino assignee
        print("Mechanism %s : ORDER SENT : %s" %(arduino['id'],arduino['ordre']))
        arduino['ordre'] = 0


class ArduinoCom(Thread):
    """
    Le thread de communication avec une Arduino
    """
    def __init__(self, arduino) :
        Thread.__init__(self)
        self.arduino = arduino

    def run(self):
        #while True: #A decommenter
        i = 0 #A supprimer
        while i < 10 : #A supprimer
            with verrou :

                #print("Arduino communication")

                send_order(self.arduino) 

                message = get_message(self.arduino) #msFasFFFFsdF Mecanisme 4   msFasFFXXsd0X Mecanisme 8
                
                get_mechanism_status(message, self.arduino)
                
                get_actuator_status(message, self.arduino)
                
                get_sensor_data(message, self.arduino)

                time.sleep(1)

            i += 1 #A supprimer


def execute():
    """
    Lancer les threads du programme pour chaque Arduino
    """
    for arduino in arduinos :
        
        ms_timer_thread = MSTimer(arduino)
        ms_timer_thread.start()
        
        as_timer_thread = ASTimer(arduino)
        as_timer_thread.start()

        sd_timer_thread = SDTimer(arduino)
        sd_timer_thread.start()

        thread = ArduinoCom(arduino)
        thread.start()


def main():

    execute()

main()
