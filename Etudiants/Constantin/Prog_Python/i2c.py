
#!/usr/bin/python2.7

import smbus
import time

bus=smbus.SMBus(1)
address= 0x12

print("Envoi de la valeur 3")
bus.write_byte(address,")
# Pause de 1 seconde pour laisser le temps au traitement de se faire. 
time.sleep(1)
reponse=bus.read_byte(address)
print("La reponse de l'arduino :", reponse)