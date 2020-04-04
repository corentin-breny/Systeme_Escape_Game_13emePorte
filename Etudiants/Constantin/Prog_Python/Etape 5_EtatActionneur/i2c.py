#!usr/bin/python3.7

import smbus
import time
from threading import Thread, RLock

bus=smbus.SMBus(1)

arduinos = [
        #{'address': 0x12, 'em_status': "NOT_OK", 'em_timer': 0, 'ea_status' : {'S_Echiquier':"NOT_OK"}, 'ea_timer' : 0},
        #{'address': 0x13, 'em_status': "NOT_OK", 'em_timer': 0, 'ea_status' : {'S_Lion':"NOT_OK"}, 'ea_timer' : 0},
        # {'address': 0x14, 'em_status': "NOT_OK", 'em_timer': 0, 'ea_status' : {'S_Meuble':"NOT_OK",'S_Terre':"NOT_OK"}, 'ea_timer' : 0},
        {'address': 0x15, 'em_status': "NOT_OK", 'em_timer': 0, 'ea_status' : {'S_Dragon':"NOT_OK",'S_Fumee':"NOT_OK",'S_Led':"NOT_OK",'S_Feu':"NOT_OK"}, 'ea_timer' : 0},
        # {'address': 0x16, 'em_status': "NOT_OK", 'em_timer': 0, 'ea_status' : {'S_Frigo':"NOT_OK",'S_Fontaine':"NOT_OK", 'S_Eau':"NOT_OK"}, 'ea_timer' : 0},
        # {'address': 0x17, 'em_status': "NOT_OK", 'em_timer': 0, 'ea_status' : {'S_Vanne':"NOT_OK",'S_Chien':"NOT_OK",'S_Led':"NOT_OK",'S_Air':"NOT_OK"}, 'ea_timer' : 0},
        # {'address': 0x18, 'em_status': "NOT_OK", 'em_timer': 0, 'ea_status' : {'S_Katana':"NOT_OK"}, 'ea_timer' : 0},
        {'address': 0x19, 'em_status': "NOT_OK", 'em_timer': 0, 'ea_status' : {'S_Tableau':"NOT_OK",'S_Led':"NOT_OK"}, 'ea_timer' : 0}#,
        # {'address': 0x20, 'em_status': "NOT_OK", 'em_timer': 0, 'ea_status' : {'S_PorteFinal':"NOT_OK"}, 'ea_timer' : 0}
     ]
     
verrou = RLock()

class MinuteurEA(Thread):

    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino
        
    def run(self):
        while self.arduino['ea_timer'] < 5 :
            time.sleep(1)
            self.arduino['ea_timer'] += 1

class MinuteurEM(Thread):

    def __init__(self, arduino):
        Thread.__init__(self)
        self.arduino = arduino
        
    def run(self):
        while self.arduino['em_timer'] < 60 :
            time.sleep(1)
            self.arduino['em_timer'] += 1

def recieve_actuator_status(mechanism_answer, arduino):
    """
    manages the acuator status reception of the Arduinos
    """
    minuteur_ea_reset = 0
    
    cpt = 7
    for a in arduino['ea_status'] :
                
        if arduino['ea_timer'] >= 5 :
            message = "actuator status : 5s elapsed since last send"
            minuteur_ea_reset = 1
                    
        if mechanism_answer[cpt] == "T" and arduino['ea_status'][a] != "OK":
            arduino['ea_status'][a] = "OK"
            message = "ACTUATOR STATUS HAS CHANGED"
            minuteur_ea_reset = 1
                           
        cpt+=1
                    
    if minuteur_ea_reset == 1 :
        print("--- Mechanism %s ---\n%s\n--- Envoie au serveur ---"  %(mechanism_answer[0], message))
        arduino['ea_timer'] = 0
        thread_minuteur_ea = MinuteurEA(arduino)
        thread_minuteur_ea.start() 
        #Corentin : Envoyer ETAT ACTIONNEUR ARDUINO reponse[0] = self.arduino['em_status'][a] en BDD
    

def recieve_mechanism_status(mechanism_answer, arduino):
    """
    manages the mechanism status reception of the Arduinos
    """
    minuteur_em_reset = 0
    
    if arduino['em_timer'] >= 60 :
        message = "mechanism status : 60s elapsed since last send"
        minuteur_em_reset = 1
                    
    if mechanism_answer[3] == "T" and arduino['em_status'] != "OK" :
        arduino['em_status'] = "OK"
        message = "MECHANISM STATUS HAS CHANGED"
        minuteur_em_reset = 1
                
    if minuteur_em_reset == 1 :
        print("--- Mechanism %s ---\n%s\n--- Envoie au serveur ---"  %(mechanism_answer[0], message))
        arduino['em_timer'] = 0
        thread_minuteur_em = MinuteurEM(arduino)
        thread_minuteur_em.start() 
        #Corentin : Envoyer ETAT MECANISME ARDUINO reponse[0] = self.arduino['em_status'] en BDD

def convertir_message(reponse) :
    """
    convert the message to String
    """
    l = []
    for r in reponse:
        if r==255: 
            break
        l.append(chr(r))
        
    message="".join(l)
    
    return message

class EchangeArduino(Thread):

    def __init__(self, arduino) :
        Thread.__init__(self)
        self.arduino = arduino
        
    def run(self):
        #while True:
        i = 0
        while i < 10 :
            with verrou :
            
                print("Arduino communication")
                bus.write_byte(self.arduino['address'],1)
                time.sleep(1)

                reponse=bus.read_i2c_block_data(self.arduino['address'],0x32)
                
                message = convertir_message(reponse)
                
                recieve_mechanism_status(message, self.arduino)
                
                recieve_actuator_status(message, self.arduino)
                   
            i += 1
           
 
def ask_status():
    """
    ask the mechanism and actuator status of the Arduinos
    """
    for arduino in arduinos :
    
        thread_minuteur_ea = MinuteurEA(arduino)
        thread_minuteur_ea.start()
        
        thread_minuteur_em = MinuteurEM(arduino)
        thread_minuteur_em.start()
        
        thread = EchangeArduino(arduino)
        thread.start()


def main():
    
    ask_status()
    
main()
