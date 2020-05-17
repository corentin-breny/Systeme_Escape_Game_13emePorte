#!usr/bin/python2.7

import smbus                        #librairie necessaire pour la communication i2c
import time                         #librairie principalement necessaire pour les timers
from threading import Thread, RLock #librairie necessaire pour les threads

bus=smbus.SMBus(1)

arduinos = [
        # {'id': 1, 'address': 0x12, 
        # 'mechanism_status': False, 'ms_noTimer': 0,
        # 'actuator_status' : {'S_Echiquier': False, 'S_Led': False}, 'as_noTimer' : 0, 
        # 'sensor_data' : {'C_EffetHall1': False, 'C_EffetHall2': False}, 'sd_noTimer': 0, 
        # 'order' : 0},
        
        # {'id': 2, 'address': 0x13, 
        # 'mechanism_status': False, 'ms_noTimer': 0,
        # 'actuator_status' : {'S_Lion': False, 'S_Led': False}, 'as_noTimer' : 0, 
        # 'sensor_data' : {'C_EffetHall': False}, 'sd_noTimer': 0, 
        # 'order' : 0},
        
        # {'id': 3, 'address': 0x14, 
        # 'mechanism_status': False, 'ms_noTimer': 0,
        # 'actuator_status' : {'S_Meuble': False, 'S_Led': False, 'S_Terre': False}, 'as_noTimer' : 0, 
        # 'sensor_data' : {'C_EffetHall': False}, 'sd_noTimer': 0, 
        # 'order' : 0},
        
        {'id': 4, 'address': 0x15,  
        'mechanism_status': True,  'ms_noTimer': 0,
        'actuator_status' : {'S_Dragon': False, 'S_Fumee': False, 'S_Led': False, 'S_Feu': False}, 'as_noTimer' : 0, 
        'sensor_data' : {'C_Interupteur': False}, 'sd_noTimer': 0, 
        'order' : 402212},
        
        # {'id': 5, 'address': 0x16,  
        # 'mechanism_status': False, 'ms_noTimer': 0,
        # 'actuator_status' : {'S_Frigo': False, 'S_Fontaine': False, 'S_Led': False, 'S_Eau': False}, 'as_noTimer' : 0, 
        # 'sensor_data' : {'C_Humidite': 0}, 'sd_noTimer': 0, 
        # 'order' : 0},
        
        # {'id': 6, 'address': 0x17, 
        # 'mechanism_status': False, 'ms_noTimer': 0,
        # 'actuator_status' : {'S_Vanne': False, 'S_Chien': False, 'S_Led': False, 'S_Air': False}, 'as_noTimer' : 0, 
        # 'sensor_data' : {'C_Vanne1': False, 'C_Vanne2': False, 'C_Vanne3': False, 'C_Vanne4': False, 'C_Vanne5': False, 'C_Vanne6': False, 'C_Vanne7': False, 'C_Bouton': False}, 'sd_noTimer': 0, 
        # 'order' : 0},
        
        # {'id': 7, 'address': 0x18, 
        # 'mechanism_status': False, 'ms_noTimer': 0,
        # 'actuator_status' : {'S_Katana': False}, 'as_noTimer' : 0, 
        # 'sensor_data' : {'C_Interupteur': False}, 'sd_noTimer': 0, 
        # 'order' : 0},
        
        {'id': 8, 'address': 0x19, 
        'mechanism_status': True, 'ms_noTimer': 0,
        'actuator_status' : {'S_Tableau': False, 'S_Led': False}, 'as_noTimer' : 0, 
        'sensor_data' : {'C_Poids': 50}, 'sd_noTimer': 0, 
        'order' : 8022}#,
        
        # {'id': 9, 'address': 0x20, 
        # 'mechanism_status': False, 'ms_noTimer': 0,
        # 'actuator_status' : {'S_Led': False, 'S_PorteFinal': False}, 'as_noTimer' : 0, 
        # 'sensor_data' : {'C_Bouton': False}, 'sd_noTimer': 0, 
        # 'order' : 0}
     ]

verrou = RLock()

#Thomas :
        #Structure du msgSocket : [1 a 9](noMecanisme) [0 ou 1 ou 2](Etat du mecanisme) [0 ou 1 ou 2][0 ou 1 ou 2](Etat des actionneurs)(Si il y a 2 actionneurs) ex : 8221

def get_socketMessage():
    """
    Recuperer le message Socket
    """
    #Thomas : Ecrire code

    # NE PAS OUBLIER CETTE PARTIE :
    # socket_message = 8221
    # for arduino in arduinos :
        # if socket_message[0] == arduino['id']:
            # arduino['order'] = socket_message
    

def send_SDtoDataBase(arduino, console_message):
    """
    Envoyer la valeur de tous les capteurs d'un mecanisme en BDD
    """
    #for sensor_name in arduino['sensor_data'] :                     #Pour chaque capteur du mecanisme
        #Envoyer en BDD sachant que :
        #arduino['id'] : correspond a l'id de l'Arduino
        #sensor_name : correspond au nom de l'actionneur
        #arduino['sensor_data'][sensor_name] : correspond a la valeur de l'actionneur
    
    #Corentin : Ecrire code
    print("Mechanism %s : sensor data : %s --- database update ---" %(arduino['id'], console_message))


def send_AStoDataBase(arduino, console_message):
    """
    Envoyer l'etat de tous les actionneurs d'un mecanisme en BDD
    """
    #for actuator_name in arduino['actuator_status'] :               #Pour chaque actionneur du mecanisme
        #Envoyer en BDD sachant que :
        #arduino['id'] : correspond a l'id de l'Arduino
        #actuator_name : correspond au nom de l'actionneur
        #arduino['actuator_status'][actuator_name] : correspond a la valeur de l'actionneur
       
    #Corentin : Ecrire code
    print("Mechanism %s : actuator status : %s --- database update ---" %(arduino['id'],console_message))


def send_MStoDataBase(arduino, console_message):
    """
    Envoyer l'etat d'un mecanisme en BDD
    """
    #Envoyer en BDD sachant que :
    #arduino['id'] : correspond a l'id de l'Arduino
    #arduino['mechanism_status'] : correspond au statut du mecanisme
    
    #Corentin : Ecrire code
    print("Mechanism %s : mechanism status : %s --- database update ---"  %(arduino['id'], console_message))


class SDTimer(Thread):
    """
    Le thread qui correspond au timer de 3s des capteurs
    """
    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino
        self.running = True

    def run(self):
        console_message = "4s elapsed since last send"
        no_thread = self.arduino['sd_noTimer']                          #On definit le numero du thread
        
        while self.running:
            time.sleep(4)                                               #On attend 4 secondes
            
            if self.arduino['sd_noTimer'] != no_thread :                #Si le thread n'est plus le timer actuel
                self.running = False                                    #On arrete le thread    
            else :                                                      #Sinon
                send_SDtoDataBase(self.arduino, console_message)        #On envoie la valeur des capteurs en BDD                       #Fonction Corentin
                

class ASTimer(Thread):
    """
    Le thread qui correspond au timer de 60s des actionneurs
    """
    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino
        self.running = True
        
    def run(self):
        console_message = "60s elapsed since last send"
        no_thread = self.arduino['as_noTimer']                          #On definit le numero du thread                    
        
        while self.running:
            time.sleep(60)                                              #On attend 60 secondes
            
            if self.arduino['as_noTimer'] != no_thread :                #Si le thread n'est plus le timer actuel
                self.running = False                                    #On arrete le thread    
            else :                                                      #Sinon
                send_AStoDataBase(self.arduino, console_message)        #On envoie l'etat des actionneurs en BDD                       #Fonction Corentin


class MSTimer(Thread):
    """
    Le thread qui correspond au timer de 60s de l'etat des mecanismes
    """
    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino
        self.running = True

    def run(self):
        console_message = "60s elapsed since last send"
        no_thread = self.arduino['ms_noTimer']                          #On definit le numero du thread                    
        
        while self.running:
            time.sleep(60)                                              #On attend 60 secondes
            
            if self.arduino['ms_noTimer'] != no_thread :                #Si le thread n'est plus le timer actuel
                self.running = False                                    #On arrete le thread    
            else :                                                      #Sinon
                send_MStoDataBase(self.arduino, console_message)        #On envoie l'etat des mecanismes en BDD                       #Fonction Corentin


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
    
    int_ds = int(data_sensor)
    
    return (int_ds,cpt)


def get_sensor_data(message, arduino):
    """
    Recuperer la valeur de tous les capteurs d'un mecanisme
    """
    ResetTimer = False
    console_message = "CHANGE"
    
    cpt = 11                                                            #La partie capteur du message commence au 12eme caractere
    for sensor_name in arduino['sensor_data'] :                         #Pour chaque capteur du mecanisme
   
        if message[cpt] == "T" :
            if arduino['sensor_data'][sensor_name] != True :            #Si le capteur selectionne vient d'etre valide
                arduino['sensor_data'][sensor_name] = True              #On change la valeur du capteur dans le dictionnaire
                ResetTimer = True                                       #On reset le timer
        
        elif message[cpt] == "F" :
            if arduino['sensor_data'][sensor_name] != False :           #Si le capteur selectionne vient d'etre invalide
                arduino['sensor_data'][sensor_name] = False             #On change la valeur du capteur dans le dictionnaire
                ResetTimer = True                                       #On reset le timer

        elif message[-1] == "X":                                        #Si le capteur possede une valeur numerique
            data_sensor,cpt = get_sensor_int_data(message, cpt)         #On recupere la valeur numerique
            if data_sensor != arduino['sensor_data'][sensor_name] :     #Si la valeur numerique vient de changer
                arduino['sensor_data'][sensor_name] = data_sensor       #On change la valeur du capteur dans le dictionnaire
                ResetTimer = True                                       #On reset le timer
        
        cpt += 1
    
    if ResetTimer == True :                                             #Pour reset le timer
        arduino['sd_noTimer'] += 1                                      #On incremente la valeur "_noTimer" dans le dictionnaire
        thread = SDTimer(arduino)                                       #On cree un nouveau thread
        thread.start()                                                  #On lance le nouveau thread
        
        send_SDtoDataBase(arduino, console_message)                     #On envoie la valeur des actionneurs en BDD                       #Fonction Corentin


def get_actuator_status(message, arduino):
    """
    Recuperer l'etat de tous les actionneurs d'un mecanisme
    """
    ResetTimer = False
    console_message = "CHANGE"
    
    cpt = 5                                                             #La partie capteur du message commence au 6eme caractere
    for actuator_name in arduino['actuator_status'] :                   #Pour chaque actionneur du mecanisme
           
        if message[cpt] == "T" :
            if arduino['actuator_status'][actuator_name] != True :      #Si l'actionneur selectionne vient d'etre valide
                arduino['actuator_status'][actuator_name] = True        #On change la valeur de l'actionneur dans le dictionnaire
                ResetTimer = True                                       #On reset le timer
                  
        elif message[cpt] == "F" :
            if arduino['actuator_status'][actuator_name] != False :     #Si l'actionneur selectionne vient d'etre invalide
                arduino['actuator_status'][actuator_name] = False       #On change la valeur de l'actionneur dans le dictionnaire 
                ResetTimer = True                                       #On reset le timer
        
        cpt+=1
    
    if ResetTimer == True :                                             #Pour reset le timer
        arduino['as_noTimer'] += 1                                      #On incremente la valeur "_noTimer" dans le dictionnaire
        thread = ASTimer(arduino)                                       #On cree un nouveau thread
        thread.start()                                                  #On lance le nouveau thread
        
        send_AStoDataBase(arduino, console_message)                     #On envoie la valeur des actionneurs en BDD                       #Fonction Corentin
    


def get_mechanism_status(message, arduino):
    """
    Recuperer l'etat d'un mecanisme
    """
    ResetTimer = False
    console_message = "CHANGE"
    
    cpt = 2                                                             #La partie capteur du message commence au 3eme caractere
    if message[cpt] == "T" :
        if arduino['mechanism_status'] == False :                       #Si le mecanisme vient d'etre valide
            arduino['mechanism_status'] = True                          #On change la valeur du mecanisme dans le dictionnaire
            ResetTimer = True                                           #On reset le timer
    
    elif message[cpt] == "F" :
        if arduino['mechanism_status'] == True :                        #Si le mecanisme vient d'etre invalide
            arduino['mechanism_status'] = False                         #On change la valeur du mecanisme dans le dictionnaire
            ResetTimer = True                                           #On reset le timer
        
    if ResetTimer == True :                                             #Pour reset le timer    
        arduino['ms_noTimer'] += 1                                      #On incremente la valeur "_noTimer" dans le dictionnaire
        thread = MSTimer(arduino)                                       #On cree un nouveau thread
        thread.start()                                                  #On lance le nouveau thread
        
        send_MStoDataBase(arduino, console_message)                     #On envoie l'etat du mecanisme en BDD                       #Fonction Corentin


def get_message(arduino) :
    """
    Recuperer le message i2c en une chaine de caractere
    """
    answer = bus.read_i2c_block_data(arduino['address'],0x32)           #On recupere le message i2c
    
    l = []
    for letter in answer:
        if letter == 255:
            break
        l.append(chr(letter))

    message="".join(l)                                                  #On converti le message i2c en une chaine de caractere

    return message #msFasFFFFsdF/msFasFFXXsd0X


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
    Envoyer un order a une Arduino
    """
    #arduino['order'] = 412221 Pour le mecanisme 4
    get_socketMessage()                                                 #Recuperer le dernier message socket                              #Fonction Thomas
    
    if arduino['order'] != 0 :                                          #On verifie si l'Arduino a recu un order
        
        order = convertStrToListHex(str(arduino['order']))              #On convertit le message socket en Hexadecimal
        bus.write_i2c_block_data(arduino['address'], 0, order)          #On envoie le message socket a l'Arduino assignee

        print("Mechanism %s : ORDER SENT : %s" %(arduino['id'],arduino['order']))
        arduino['order'] = 0                                            #On reset l'ordre


class ArduinoCom(Thread):
    """
    Le thread de communication avec une Arduino
    """
    def __init__(self, arduino) :
        Thread.__init__(self)
        self.arduino = arduino
        self.running = True
        
    def run(self):
        while self.running:

            try :
                print("Arduino %s : communication" %self.arduino['id'])

                send_order(self.arduino)                                #On envoie le message d'order a l'Arduino s'il y en a un

                message = get_message(self.arduino)                     #On recupere le message i2c venant de l'Arduino
                
                get_mechanism_status(message, self.arduino)             #On verifie l'etat du mecanimse
                
                get_actuator_status(message, self.arduino)              #On verifie l'etat des actionneurs
                
                get_sensor_data(message, self.arduino)                  #On verifie la valeur des capteurs

                time.sleep(2)                                           #On attend 2 secondes
                
            except :                                                    #Si il y a une erreur quelconque dans l'execution du thread
                self.running = False                                    #On arrete le thread
                thread = ArduinoCom(self.arduino)                       #On cree un nouveau thread
                thread.start()                                          #On lance le nouveau thread


def execute():
    """
    Lancer les threads du programme pour chaque Arduino
    """
    for arduino in arduinos :                                           #Pour chaque Arduino
        
        thread = MSTimer(arduino)                                       #On cree un thread pour le timer de l'etat mecanisme
        thread.start()                                                  #On lance le thread
        
        thread = ASTimer(arduino)                                       #On cree le thread pour le timer des actionneurs
        thread.start()                                                  #On lance le thread

        thread = SDTimer(arduino)                                       #On cree le thread pour le timer des capteurs
        thread.start()                                                  #On lance le thread

        thread = ArduinoCom(arduino)                                    #On cree le thread pour la communication Arduino
        thread.start()                                                  #On lance le thread


def main():

    execute()

main()
