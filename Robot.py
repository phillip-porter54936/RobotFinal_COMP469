from scanner import Scanner
import serial
import os
# -*- coding: utf-8 -*-
"""
Created on Thu Nov 30 11:27:54 2017

@author: zolta
"""

class Robot:
    scanner = None
    position = 0.0
    ser = None #serial port
    isMoving = False

    def __init__(self):
        self.scanner = Scanner()
        self.ser = serial.Serial('/dev/ttyACM%d' % ACM_Port, 9600, parity=serial.PARITY_EVEN)
    
    def getYaw(self):
        return 0
    
    def getRoll(self):
        return 0
    
    def getPitch(self):
        return 0
    
    def move(self, direction):
        isMoving = True
        if direction == 0: #EAST
            #use scanner to check if robot faceing right direction; turn robot if necessary
            correctDirection = False
            while not correctDirection:
                turn(90)
        elif direction == 1: #NORTH

        elif direction == 2: #WEST

        elif direction == 3: #SOUTH
        
    def turn(self, degrees):
        ser.write(bytes())

        