#!usr/bin/python2.7

import smbus
import time

bus=smbus.SMBus(1)
address1= 0x12
address2= 0x13

print("Envoi de la valeur 3 a l'Arduino1 ")
bus.write_byte(address1,3)
# Pause de 1 seconde pour laisser le temps au traitement de se faire. 
time.sleep(1)
reponse=bus.read_byte(address1)
print("La reponse de l'Arduino1 :", reponse)

print("Envoi de la valeur 1 a l'Arduino2 ")
bus.write_byte(address2,1)
time.sleep(1)

reponse=bus.read_i2c_block_data(address2,0x32)
l = []
for r in reponse:
	if r==255: 
		break
	l.append(chr(r))
reponse="".join(l)
print("La reponse de l'Arduino2 :", reponse)
