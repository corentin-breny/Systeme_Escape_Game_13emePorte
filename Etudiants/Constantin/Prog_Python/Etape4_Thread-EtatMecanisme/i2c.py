#!usr/bin/python3.7

import smbus
import time
from threading import Thread, RLock

bus=smbus.SMBus(1)

EM = [
        {'address': 0x15, 'status': "NOT_OK", 'timer': 0},
        {'address': 0x19, 'status': "NOT_OK", 'timer': 0}
     ]
     
verrou = RLock()

class Minuteur(Thread):

    def __init__(self, em):
        Thread.__init__(self)
        self.em = em
        
    def run(self):
        while self.em['timer'] < 5 : #60 :
            time.sleep(1)
            self.em['timer'] += 1

class EtatMecanisme(Thread):

    def __init__(self, em, address, status):
        Thread.__init__(self)
        self.em = em
        self.address = address
        self.status = status
        
    def run(self):
        #while True:
        i = 0
        while i < 20:
            with verrou :
                minuteur_reset = 0
                
                print("Arduino communication")
                bus.write_byte(self.address,1)
                time.sleep(1)

                reponse=bus.read_i2c_block_data(self.address,0x32)
                l = []
                for r in reponse:
                    if r==255: 
                        break
                    l.append(chr(r))
                reponse="".join(l)
                
                if self.em['timer'] >= 5 :#60 :
                    print("--- Arduino %s : 5s elapsed ---" %reponse[0]) #print("---Arduino %s 60s elapsed---" %reponse[0])
                    print("Mechanism status : %s" %reponse)
                    minuteur_reset = 1
                    #Corentin : Envoyer f"ETAT MECANISME {reponse[0]}" = self.em['status'] en BDD
                    
                if reponse[3] == "T" and self.em['status'] != "OK" :
                    print("--- Arduino %s : MECHANISM STATUS HAS CHANGED ---" %reponse[0])
                    print("Mechanism status : %s" %reponse)
                    self.em['status'] = "OK"
                    minuteur_reset = 1
                    #Corentin : Envoyer f"ETAT MECANISME {reponse[0]}" = OK en BDD
                
                if minuteur_reset == 1 :
                    self.em['timer'] = 0
                    thread_minuteur = Minuteur(self.em)
                    thread_minuteur.start()
            i += 1
           

def ask_mechanism_status():
    """
    ask the status mechanism of the Arduinos
    """
    for em in EM :
        thread_minuteur = Minuteur(em)
        thread_minuteur.start()
        thread = EtatMecanisme(em, em['address'], em['status'])
        thread.start()

    
    
def ask_informations():
    """
    call the functions to receive mechanism status and Sensor Value
    """
    ask_mechanism_status()

def main():
    
    ask_informations()
    
main()
