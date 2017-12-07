from Robot_Control.scanner import Scanner
import serial
import os
# -*- coding: utf-8 -*-
"""
Created on Thu Nov 30 11:27:54 2017

@author: zolta
"""

class Robot:
    ORIENTATIONS    = ['east','north', 'west', 'south']
    GET_ORIENTATION = lambda x : Robot.ORIENTATIONS.index(x)

    TURN_CMD = lambda x: bytes("TURN %s;" % x)
    MOVE_CMD = lambda x: bytes("MOVE %s;" % x)
    CONFIRM  = lambda x: bytes("CONF %s" % x)

    def __init__(self):
        ACM_Port = 0
        while not os.path.exists('/dev/ttyACM%d' % ACM_Port):
            ACM_Port += 1

        self.scanner = Scanner()
        self.ser = serial.Serial('/dev/ttyACM%d' % ACM_Port, 9600, parity=serial.PARITY_EVEN)
        self.orientation = Robot.GET_ORIENTATION('north')
        self.isMoving    = False
        self.position    = (0,0)

    def turn(self, degrees):
        isMoving = True
        cmd = Robot.TURN_CMD(degrees)
        self.ser.write(cmd)

        resp = self.ser.read_all().split(';')

        if len(resp) > 1:
            if resp[0] != cmd[:-1] or resp[1] != Robot.CONFIRM(cmd)[:-1]:
                print("Turn error")
        elif resp[0] == cmd[:-1]:
            if self.ser.read_all() != Robot.CONFIRM(cmd)[:-1]:
                print("Turn error")

        self.orientation = (self.orientation + 1) % len(Robot.ORIENTATIONS)

        isMoving = False

    def move(self, direction):
        isMoving = True

        # Orient to direction
        while direction != self.orientation:
            self.turn(90)

        # TODO
        # Measure front and back obstacles


        # Move forward
        cmd = Robot.MOVE_CMD(1)
        self.ser.write(cmd)
        resp = self.ser.read_all().split(';')

        if len(resp) > 1:
            if resp[0] != cmd[:-1] or resp[1] != Robot.CONFIRM(cmd)[:-1]:
                print("Move error")
        elif resp[0] == cmd[:-1]:
            if self.ser.read_all() != Robot.CONFIRM(cmd)[:-1]:
                print("Move error")

        # TODO
        # Assert that movement has occured

        isMoving = False
        


        