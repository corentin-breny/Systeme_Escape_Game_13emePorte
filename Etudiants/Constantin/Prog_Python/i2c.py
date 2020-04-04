#!usr/bin/python3.7

import smbus
import time
from threading import Thread, RLock

bus=smbus.SMBus(1)

arduinos = [
        #{'address': 0x12, 'em_status': "NOT_OK", 'em_timer': 0},
        #{'address': 0x13, 'em_status': "NOT_OK", 'em_timer': 0},
        # {'address': 0x14, 'em_status': "NOT_OK", 'em_timer': 0},
        {'address': 0x15, 'em_status': "NOT_OK", 'em_timer': 0, 'ea_status' : {'S_Dragon':"NOT_OK",'S_Fumee':"NOT_OK",'S_Led':"NOT_OK",'S_FEU':"NOT_OK"}, 'ea_timer' : 0},
        # {'address': 0x16, 'em_status': "NOT_OK", 'em_timer': 0},
        # {'address': 0x17, 'em_status': "NOT_OK", 'em_timer': 0},
        # {'address': 0x18, 'em_status': "NOT_OK", 'em_timer': 0},
        {'address': 0x19, 'em_status': "NOT_OK", 'em_timer': 0, 'ea_status' : {'S_Tableau':"NOT_OK",'S_Led':"NOT_OK"}, 'ea_timer' : 0}#,
        # {'address': 0x20, 'em_status': "NOT_OK", 'em_timer': 0}
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


def recieve_mechanism_status(mechanism_answer, arduino):
    """
    manages the mechanism status reception of the Arduinos
    """
    minuteur_em_reset = 0
    
    if arduino['em_timer'] >= 60 :
        message1 = "mechanism status : 60s elapsed since last send"
        minuteur_em_reset = 1
                    
    if mechanism_answer[3] == "T" and arduino['em_status'] != "OK" :
        arduino['em_status'] = "OK"
        message1 = "MECHANISM STATUS HAS CHANGED"
        minuteur_em_reset = 1
                
    if minuteur_em_reset == 1 :
        print("--- Mechanism %s ---\n%s\n--- Envoie au serveur ---"  %(mechanism_answer[0], message1))
        arduino['em_timer'] = 0
        thread_minuteur_em = MinuteurEM(arduino)
        thread_minuteur_em.start() #Corentin : Envoyer f"ETAT MECANISME ARDUINO{reponse[0]}" = self.arduino['em_status'] en BDD


class EtatMecanisme(Thread):

    def __init__(self, arduino) :
        Thread.__init__(self)
        self.arduino = arduino
        
    def run(self):
        #while True:
        i = 0
        while i < 10 :
            with verrou :
                
                minuteur_ea_reset = 0
                
                print("Arduino communication")
                bus.write_byte(self.arduino['address'],1)
                time.sleep(1)

                reponse=bus.read_i2c_block_data(self.arduino['address'],0x32)
                l = []
                for r in reponse:
                    if r==255: 
                        break
                    l.append(chr(r))
                reponse="".join(l)
                
                recieve_mechanism_status(reponse, self.arduino)
                
                
                
                cpt = 7
                for a in self.arduino['ea_status'] :
                
                    if self.arduino['ea_timer'] >= 5 :
                        message2 = "actuator status : 5s elapsed since last send"
                        minuteur_ea_reset = 1
                    
                    if reponse[cpt] == "T" and self.arduino['ea_status'][a] != "OK":
                        self.arduino['ea_status'][a] = "OK"
                        message2 = "ACTUATOR STATUS HAS CHANGED"
                        minuteur_ea_reset = 1
                        msg = 1
                           
                    cpt+=1
                    
                if minuteur_ea_reset == 1 :
                        print("--- Mechanism %s ---\n%s\n--- Envoie au serveur ---"  %(reponse[0], message2))
                        self.arduino['ea_timer'] = 0
                        thread_minuteur_ea = MinuteurEA(self.arduino)
                        thread_minuteur_ea.start() #Corentin : Envoyer f"ETAT ACTIONNEUR ARDUINO{reponse[0]}" = self.arduino['em_status'][a] en BDD    
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
        
        thread = EtatMecanisme(arduino)
        thread.start()

def main():
    
    ask_status()
    
main()
