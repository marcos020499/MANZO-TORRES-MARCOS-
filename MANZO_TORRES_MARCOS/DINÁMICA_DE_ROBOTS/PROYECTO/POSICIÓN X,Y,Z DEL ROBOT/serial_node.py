#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import rospy
from rosserial_python import SerialClient, RosSerialServer
from serial import SerialException
from time import sleep
import multiprocessing
from serial import Serial
from std_msgs.msg import String
import sys

def menu():

	os.system('cls')
	print ("Selecciona una opción")
	print ("\t1 - mover motores")
	print ("\t2 - apagar motores")
	print ("\t3 - prender led")
	print ("\t9 - salir")
	
	
while True:
	menu()
	opcionMenu = input("inserta un numero valor >> ")
	if opcionMenu==1:
		print ("vamos a mover los motores")
		input("Has pulsado la opción 1...\npulsa una tecla para continuar")
		com = serial.Serial('COM3', baudrate=115200)
		com.write('1')
		
		menu()
	elif opcionMenu==2:
		print ("apagar los motores")
		input("Has pulsado la opción 2...\npulsa una tecla para continuar")
		com = serial.Serial('COM3', baudrate=115200)
		com.write('$G')
		
		menu()
	elif opcionMenu==3:
		print ("en un momento lo atendemos")
		input("Has pulsado la opción 3...\npulsa una tecla para continuar")
		com = serial.Serial('COM3', baudrate=115200)
		com.write('G91X2.0F500')
		
		
		menu()