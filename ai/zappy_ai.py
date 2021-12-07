#!/usr/bin/env python3
##
# EPITECH PROJECT, 2021
# YEP
# File description:
# ai
##

from re import search
from typing import TextIO
from ai.actions import BasesActions
from ai.connection import Connection
from ai.memory import AiMemory
from ai.memory import Direction
import sys
import signal
import time


def signal_handler(sig, frame):
    print('\nKilled by admin')
    sys.exit(0)


class Ai:

    # Init

    def __init__(self, isServerTest:bool) -> None:
        if isServerTest:
            print("Test on test server")
        self.memory = AiMemory(isServerTest)

    # Process

    def incantPhase(self):
        if not self.setdownIncant():
            self.setdownphase = False
            self.needlook = True
        elif self.memory.haveAllNeededOnGround() and not self.memory.actionLauched:
            self.incant()
            self.setdownphase = False

    def look_for_food(self):
        print("Actual pos:", self.memory.position)
        print("Actual inventory:", self.memory.inventoryMap)
        next_food_pos = self.memory.findObject("food")
        if (next_food_pos != None):
            print("Detect food:", next_food_pos)
            if self.memory.posHasObject(self.memory.position, "food"):
                print("We are on it !")
                self.take("food")
                if self.memory.lastLook >= 21:
                    print("We should look")
                    self.needlook = True
            else:
                print("This way...")
                self.goTo(next_food_pos)
        else:
            print("Search for food")
            self.goForward()
            self.needlook = True

    def look_for_needed(self):
        print("Actual pos:", self.memory.position)
        print("Actual inventory:", self.memory.inventoryMap)
        next_needed_pos = self.memory.searchForNeeded()
        if (next_needed_pos != None):
            print("Detect needed:", next_needed_pos)
            if self.memory.posHasNeeded(self.memory.position):
                print("We are on it !")
                self.takeNeeded()
                if self.memory.lastLook >= 21:
                    print("We should look")
                    self.needlook = True
            else:
                print("This way...")
                self.goTo(next_needed_pos)
        else:
            print("Search for needed")
            self.goForward()
            self.needlook = True

    def _init_id(self):
        if self.memory.initCount != 3:
            self.broadcast(self.memory.broadcastResp["NEW"])
        elif self.memory.initCount != 4:
            self.memory.id = 0

    def loop(self):
        signal.signal(signal.SIGINT, signal_handler)
        self.needlook = True
        self.needFood = False
        self.setdownphase = False
        while(1):
            if self.setdownphase:
                print("Incant phase")
                self.incantPhase()
            elif self.memory.lastInventory >= 126:
                print("I am hungry ?")
                self.inventory()
            elif self.needlook:
                self.look()
                self.needlook = False
            elif self.memory.posHasObject(self.memory.position, "food"):
                self.take("food")
            elif self.memory.inventoryMap["food"] < 10:
                self.look_for_food()
            elif self.memory.posHasNeeded(self.memory.position):
                self.takeNeeded()
            elif not self.memory.haveAllNeeded():
                self.look_for_needed()
            else:
                self.setdownphase = True
                self.incantPhase()
            print()
            self.computeServerResponse()

    # Updates infos

    def look(self):
        if not self.memory.actionLauched:
            print("Look")
            BasesActions.look()
            self.memory.look()

    def inventory(self):
        if not self.memory.actionLauched:
            print('Inventory')
            BasesActions.inventory()
            self.memory.inventory()

    # Movments

    def turnRight(self):
        if not self.memory.actionLauched:
            print("Turn Right")
            BasesActions.right()
            self.memory.turnRight()

    def turnLeft(self):
        if not self.memory.actionLauched:
            print("Turn Left")
            BasesActions.left()
            self.memory.turnLeft()

    def goForward(self):
        if not self.memory.actionLauched:
            print("Go forward")
            BasesActions.forward()
            self.memory.goForward()

    def getDir(self, targetPos: list) -> Direction:
        diff = self.memory.diffPos(self.memory.position, targetPos)
        if diff[1] != 0:
            if diff[1] > 0:
                ret = Direction.NORTH
            else:
                ret = Direction.SOUTH
        elif diff[0] != 0:
            if diff[0] > 0:
                ret = Direction.EST
            else:
                ret = Direction.WEST
        else:
            ret = None
        return ret

    def turnDir(self, direction: Direction) -> bool:
        if self.memory.direction == direction:
            return True
        if self.memory.direction == Direction((direction.value - 1) % 4):
            self.turnRight()
        else:
            self.turnLeft()
        return False

    def goTo(self, pos: list) -> bool:
        if pos == self.memory.position:
            return True
        direction = self.getDir(pos)
        isTurned = False
        if direction:
            isTurned = self.turnDir(direction)
        if isTurned:
            self.goForward()
        return False

    # Objects

    def take(self, object: str):
        if not self.memory.actionLauched:
            print("Take " + object)
            BasesActions.take(object)
            self.memory.take(object)

    def takeNeeded(self):
        for item in self.memory.need.keys():
            if not self.memory.haveEnough(item):
                if self.memory.posHasObject(self.memory.position, item):
                    self.take(item)
                    return

    def setdown(self, object: str):
        if not self.memory.actionLauched:
            print("Set down " + object)
            BasesActions.setdown(object)
            self.memory.setdown(object)

    def setdownIncant(self):
        if self.memory.haveAllNeededOnGround():
            return True
        for item in self.memory.need.keys():
            if not self.memory.haveEnoughOnGround(item):
                if not self.memory.inventoryMap[item] > 0:
                    return False
                self.setdown(item)
            if not self.memory.haveNotToMuchOnGround(item):
                self.take(item)
        return True


    def computeServerResponse(self):
        resp = BasesActions.receive()
        print("From server:\n" + str(resp))
        self.memory.computeServerResponse(resp)

    #Interact

    def incant(self):
        if not self.memory.actionLauched:
            print("Incant")
            BasesActions.incantation()
            self.memory.incant()

    def broadcast(self, msg):
        iden = self.memory.id+"|"+self.memory.msgid+"|"
        transmission = iden+msg
        if not self.memory.actionLauched:
            print("Broadcast:", transmission)
            BasesActions.broadcast(transmission)
            self.memory.broadcast()


flags = {"-h" : "machine", "-p" : "port", "-n": "team"}
myargs = {"machine" : "localhost", "port" : None, "team" : None}
isServerTest = False
raws = sys.argv[1:]
current_flag = None
for raw in raws:
    if raw[0] == '-':
        if raw == "-help":
            print(open('./ai/help.txt', 'r').read())
            exit(0)
        if raw == "-test":
            if current_flag != None:
                print("Missing argument for flag")
                exit(0)
            isServerTest = True
        elif not raw in flags.keys():
            print("Invalid option:", raw)
            exit(0)
        else:
            current_flag = flags[raw]
    else:
        if current_flag == None:
            print("Invalid arg:", raw)
        else:
            myargs[current_flag] = raw
            current_flag = None
if myargs["port"] == None or myargs["team"] == None:
    print(open('ai/help.txt', 'r').read())
    exit(0)

if __name__ == "__main__":
    Connection.connection(myargs["machine"], int(myargs["port"]), myargs["team"])
    ai = Ai(isServerTest)
    ai.loop()
    print("Ended")
