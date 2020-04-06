#!usr/bin/python2.7

import smbus
import time

bus=smbus.SMBus(1)
ADDRESSES= [0x12,0x13]


def ask_mechanism_status():
    """
    ask the status mechanism of the Arduinos
    """
    
    for address in ADDRESSES :
        print("Envoi de la valeur 1 a l'Arduino")
        bus.write_byte(address,1)
        time.sleep(1)

        reponse=bus.read_i2c_block_data(address,0x32)
        l = []
        for r in reponse:
            if r==255: 
                break
            l.append(chr(r))
        reponse="".join(l)
        print("La reponse de l'Arduino :", reponse)

def ask_informations():
    """
    call the functions to receive mechanism status and Sensor Value
    """
    ask_mechanism_status()

def main():
    
    while True :
    	ask_informations()
    
main()
