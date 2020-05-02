#!usr/bin/python2.7

import smbus
import time
from threading import Thread, RLock

bus=smbus.SMBus(1)

arduinos = [
        # {'id': 1, 'address': 0x12, 
        # 'mechanism_status': False, 'no_timer': 0,
        # 'actuator_status' : {'S_Echiquier': False}, 'no_timer' : 0, 
        # 'sensor_data' : {'C_EffetHall1': 0, 'C_EffetHall2': 0}, 'no_timer': 0, 
        # 'ordre' : 0},
        
        # {'id': 2, 'address': 0x13, 
        # 'mechanism_status': False, 'no_timer': 0,
        # 'actuator_status' : {'S_Lion': False}, 'no_timer' : 0, 
        # 'sensor_data' : {'C_EffetHall': 0}, 'no_timer': 0, 
        # 'ordre' : 0},
        
        # {'id': 3, 'address': 0x14, 
        # 'mechanism_status': False, 'no_timer': 0,
        # 'actuator_status' : {'S_Meuble': False, 'S_Terre': False}, 'no_timer' : 0, 
        # 'sensor_data' : {'C_EffetHall': 0}, 'no_timer': 0, 
        # 'ordre' : 0},
        
        {'id': 4, 'address': 0x15,  
        'mechanism_status': True,  'no_timer': 0,
        'actuator_status' : {'S_Dragon': False, 'S_Fumee': False, 'S_Led': False, 'S_Feu': False}, 'no_timer' : 0, 
        'sensor_data' : {'C_Interupteur': False}, 'no_timer': 0, 
        'ordre' : 0},
        
        # {'id': 5, 'address': 0x16,  
        # 'mechanism_status': False, 'no_timer': 0,
        # 'actuator_status' : {'S_Frigo': False, 'S_Fontaine': False, 'S_Led': False, 'S_Eau': False}, 'no_timer' : 0, 
        # 'sensor_data' : {'C_Humidite': 0}, 'no_timer': 0, 
        # 'ordre' : 0},
        
        # {'id': 6, 'address': 0x17, 
        # 'mechanism_status': False, 'no_timer': 0,
        # 'actuator_status' : {'S_Vanne': False, 'S_Chien': False, 'S_Led': False, 'S_Air': False}, 'no_timer' : 0, 
        # 'sensor_data' : {'C_Vanne1': False, 'C_Vanne2': False, 'C_Vanne3': False, 'C_Vanne4': False, 'C_Vanne5': False, 'C_Vanne6': False, 'C_Vanne7': False, 'C_Bouton': False}, 'no_timer': 0, 
        # 'ordre' : 0},
        
        # {'id': 7, 'address': 0x18, 
        # 'mechanism_status': False, 'no_timer': 0,
        # 'actuator_status' : {'S_Katana': False}, 'no_timer' : 0, 
        # 'sensor_data' : {'C_Interupteur': False}, 'no_timer': 0, 
        # 'ordre' : 0},
        
        {'id': 8, 'address': 0x19, 
        'mechanism_status': False, 'no_timer': 0,
        'actuator_status' : {'S_Tableau': False, 'S_Led': False}, 'no_timer' : 0, 
        'sensor_data' : {'C_Poids': 0}, 'no_timer': 0, 
        'ordre' : 0},#8221}#,
        
        # {'id': 9, 'address': 0x20, 
        # 'mechanism_status': False, 'no_timer': 0,
        # 'actuator_status' : {'S_Led': False, 'S_PorteFinal': False}, 'no_timer' : 0, 
        # 'sensor_data' : {'C_Bouton': False}, 'no_timer': 0, 
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
        no_thread = self.arduino['no_timer']                         #On definit le numero du thread
        
        while self.running:
            time.sleep(3)                                           #On attend 3 secondes
            
            if self.arduino['no_timer'] != no_thread :               #Si le thread n'est plus le timer actuel
                self.running = False                                #On arrete le thread    
            else :                                                  #Sinon
                console_message = "3s elapsed since last send"
                send_SDtoDataBase(self.arduino, console_message)    #On envoie la valeur des capteurs en BDD                       #Fonction Corentin
                

class ASTimer(Thread):
    """
    Le thread qui correspond au timer de 60s des actionneurs
    """
    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino
        self.running = True
        
    def run(self):
        no_thread = self.arduino['no_timer']                         #On definit le numero du thread                    
        
        while self.running:
            time.sleep(60)                                          #On attend 60 secondes
            
            if self.arduino['no_timer'] != no_thread :               #Si le thread n'est plus le timer actuel
                self.running = False                                #On arrete le thread    
            else :                                                  #Sinon
                console_message = "60s elapsed since last send"
                send_AStoDataBase(self.arduino, console_message)    #On envoie l'etat des actionneurs en BDD                       #Fonction Corentin


class MSTimer(Thread):
    """
    Le thread qui correspond au timer de 60s de l'etat des mecanismes
    """
    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino
        self.running = True

    def run(self):
        no_thread = self.arduino['no_timer']                         #On definit le numero du thread                    
        
        while self.running:
            time.sleep(60)                                          #On attend 60 secondes
            
            if self.arduino['no_timer'] != no_thread :               #Si le thread n'est plus le timer actuel
                self.running = False                                #On arrete le thread    
            else :                                                  #Sinon
                console_message = "60s elapsed since last send"
                send_MStoDataBase(self.arduino, console_message)    #On envoie l'etat des mecanismes en BDD                       #Fonction Corentin


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
    ResetTimer = False
    
    cpt = 11
    for sensor_name in arduino['sensor_data'] :                         #Pour chaque capteur du mecanisme
        
        #Si le capteur a une valeur boolean True et si le capteur selectionne vient d'etre valide
        if message[cpt] == 'T' and arduino['sensor_data'][sensor_name] == False :
            arduino['sensor_data'][sensor_name] = True                  #On change la valeur du capteur dans le dictionnaire
            ResetTimer = True                                           #On reset le timer
        
        #Si le capteur a une valeur boolean False et si le capteur selectionne vient d'etre invalide        
        elif message[cpt] == 'F' and arduino['sensor_data'][sensor_name] == True :
            arduino['sensor_data'][sensor_name] = False                 #On change la valeur du capteur dans le dictionnaire
            ResetTimer = True                                           #On reset le timer

        elif message[-1] == 'X':                                        #Si le capteur possede une valeur numerique
            data_sensor,cpt = get_sensor_int_data(message, cpt)         #On recupere la valeur numerique
            if data_sensor != arduino['sensor_data'][sensor_name] :     #Si la valeur numerique vient de changer
                arduino['sensor_data'][sensor_name] = data_sensor       #On change la valeur du capteur dans le dictionnaire
                ResetTimer = True                                       #On reset le timer
        
        cpt += 1
    
    if ResetTimer == True :                                             #Pour reset le timer
        arduino['no_timer'] += 1                                        #On incremente la valeur "no_timer" dans le dictionnaire
        no_timer_thread = SDTimer(arduino)                              #On cree un nouveau thread
        no_timer_thread.start()                                         #On lance le thread
        
        console_message = "CHANGE"
        send_SDtoDataBase(arduino, console_message)                     #On envoie la valeur des actionneurs en BDD                       #Fonction Corentin


def get_actuator_status(message, arduino):
    """
    Recuperer l'etat de tous les actionneurs d'un mecanisme
    """
    ResetTimer = False
    
    cpt = 5
    for actuator_name in arduino['actuator_status'] :                   #Pour chaque actionneur du mecanisme
        
        #Si l'actionneur a une valeur boolean True et si l'actionneur selectionne vient d'etre valide
        if message[cpt] == 'T' and arduino['actuator_status'][actuator_name] == False :
            arduino['actuator_status'][actuator_name] = True            #On change la valeur de l'actionneur dans le dictionnaire
            ResetTimer = True                                           #On reset le timer
            
        
        #Si l'actionneur a une valeur boolean False et si l'actionneur selectionne vient d'etre invalide    
        elif message[cpt] == 'F' and arduino['actuator_status'][actuator_name] == True :
            arduino['actuator_status'][actuator_name] = False           #On change la valeur de l'actionneur dans le dictionnaire 
            ResetTimer = True                                           #On reset le timer
        
        cpt+=1
    
    if ResetTimer == True :                                             #Pour reset le timer
        arduino['no_timer'] += 1                                        #On incremente la valeur "no_timer" dans le dictionnaire
        no_timer_thread = ASTimer(arduino)                              #On cree un nouveau thread
        no_timer_thread.start()                                         #On lance le thread
        
        console_message = "CHANGE"
        send_AStoDataBase(arduino, console_message)                     #On envoie la valeur des actionneurs en BDD                       #Fonction Corentin
    


def get_mechanism_status(message, arduino):
    """
    Recuperer l'etat d'un mecanisme
    """
    ResetTimer = False
      
    #Si le mecanisme a une valeur boolean True et si le mecanisme vient d'etre valide
    if message[2] == 'T' and arduino['mechanism_status'] == False :
        arduino['mechanism_status'] = True                              #On change la valeur du mecanisme dans le dictionnaire
        ResetTimer = True                                               #On reset le timer
    
    #Si le mecanisme a une valeur boolean False et si le mecanisme vient d'etre invalide
    elif message[2] == 'F' and arduino['mechanism_status'] == True : 
        arduino['mechanism_status'] = False                             #On change la valeur du mecanisme dans le dictionnaire
        ResetTimer = True                                               #On reset le timer
        
    if ResetTimer == True :                                             #Pour reset le timer    
        arduino['no_timer'] += 1                                        #On incremente la valeur "no_timer" dans le dictionnaire
        no_timer_thread = MSTimer(arduino)                              #On cree un nouveau thread
        no_timer_thread.start()                                         #On lance le thread
        
        console_message = "CHANGE"
        send_MStoDataBase(arduino, console_message)                     #On envoie l'etat du mecanisme en BDD                       #Fonction Corentin


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
    
    if arduino['ordre'] != 0 :                                          #On verifie si l'Arduino a recu un ordre
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
        while True: #A decommenter
        # i = 0 #A supprimer
        # while i < 10 : #A supprimer

            print("Arduino communication")

            send_order(self.arduino) 

            message = get_message(self.arduino) #msFasFFFFsdF Mecanisme 4   msFasFFXXsd0X Mecanisme 8
                
            get_mechanism_status(message, self.arduino)
                
            get_actuator_status(message, self.arduino)
                
            get_sensor_data(message, self.arduino)

            time.sleep(1)

            # i += 1 #A supprimer


def execute():
    """
    Lancer les threads du programme pour chaque Arduino
    """
    for arduino in arduinos :
        
        no_timer_thread = MSTimer(arduino)
        no_timer_thread.start()
        
        no_timer_thread = ASTimer(arduino)
        no_timer_thread.start()

        no_timer_thread = SDTimer(arduino)
        no_timer_thread.start()

        thread = ArduinoCom(arduino)
        thread.start()


def main():

    execute()

main()
