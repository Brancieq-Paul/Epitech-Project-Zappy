from __future__ import annotations
from enum import Enum
import re
import ast

class invChecks(Enum):
    INCANT1 = {"linemate" : 1, "deraumere" : 0, "sibur" : 0, "mendiane" : 0, "phiras" : 0, "thystame" : 0}
    INCANT2 = {"linemate" : 1, "deraumere" : 0, "sibur" : 0, "mendiane" : 0, "phiras" : 0, "thystame" : 9999}

class Direction(Enum):
    NORTH = 0
    EST = 1
    SOUTH = 2
    WEST = 3


class Actions(Enum):
    TURNRIGHT = "TURNRIGHT"
    TURNLEFT = "TURNLEFT"
    GOFORWARD = "GOFORWARD"
    GORIGHT = "GORIGHT"
    GOLEFT = "GOLEFT"
    GOBACK = "GOBACK"
    LOOK = "LOOK"
    INVENTORY = "INVENTORY"
    TAKE = "TAKE"
    SET = "SET"
    BROADCAST = "BROADCAST"
    EJECT = "EJECT",
    INCANT = "INCANT"


class AiMemory:

    vectorsDirection = [[0, 1], [1, 0], [0, -1], [-1, 0]]
    lookSizes = [1, 4, 9, 16, 25, 36, 49, 64, 81]
    linesSizes = [1, 3, 5, 7, 9, 11, 13, 15, 17]

    # Init

    def __init__(self, isServerTest:bool) -> None:
        self.initInventory()
        self.actions = {
            "TURNRIGHT": self._turnRight,
            "TURNLEFT": self._turnLeft,
            "GOFORWARD": self._goForward,
            "LOOK": self._readLook,
            "INVENTORY": self._setInventory,
            "TAKE": self._take,
            "SET": self._setdown,
            "BROADCAST": self._broadcast,
            "EJECT": self._eject,
            "INCANT": self._incant
        }
        self.envHandler = {
            "\s*message\s+[0-9]\s+,\s+[a-z]+\s*": self._receiveBroadcast,
            "\s*eject\s*:\s*[0-9]": self._beingEjected
        }
        self.broadcastResp = {
            "FORMAT" : "[0-9]+|[0-9]+|.*",
            "NEW" : "NEW",
            "ASSIGN" : "ASSIGN [0-9]+"
        }
        self.actionLauched = False
        self.lastLook = 999999
        self.lastInventory = 999999
        self.need = invChecks.INCANT1.value
        self.incantCounter = 0
        self.isServerTest = isServerTest
        self.id = -1
        self.msgid = 0
        self.initCount = 0

    def initInventory(self):
        self.inventoryMap = dict()
        self.inventoryMap["food"] = 0
        self.inventoryMap["linemate"] = 0
        self.inventoryMap["deraumere"] = 0
        self.inventoryMap["sibur"] = 0
        self.inventoryMap["mendiane"] = 0
        self.inventoryMap["phiras"] = 0
        self.inventoryMap["thystame"] = 0
        self.position = [0, 0]
        self.direction = Direction.NORTH
        self.mapMemory = dict()

    # Invntory manage

    def _setInventory(self, response: str):
        response = re.sub("\[", "", response)
        response = re.sub("\]", "", response)
        tab = response.split(",")
        for i in range(len(tab)):
            tab[i] = tab[i].strip()
        for i in range(len(tab)):
            subtab = tab[i].split(" ")
            self.inventoryMap[subtab[0]] = int(subtab[1])
        self._addOld(1)
        self.lastInventory = 0

    def _addToInventory(self, elem: str):
        self.inventoryMap[elem] += 1

    def _removeFromInventory(self, elem: str):
        self.inventoryMap[elem] -= 1

    def inventory(self):
        self.currentAction = Actions.INVENTORY
        self.actionLauched = True

    def _take(self, resp: str):
        if resp == "ok":
            self._addToInventory(self.transfered_object)
            if str(self.position) in self.mapMemory.keys():
                cell = self.mapMemory[str(self.position)]
                if self.transfered_object in cell.keys():
                    cell[self.transfered_object] -= 1
        self._addOld(7)

    def _setdown(self, resp: str):
        if resp == "ok":
            self._removeFromInventory(self.transfered_object)
            if str(self.position) in self.mapMemory.keys():
                cell = self.mapMemory[str(self.position)]
                if self.transfered_object in cell.keys():
                    cell[self.transfered_object] += 1
                else:
                    cell[self.transfered_object] = 1
        self._addOld(7)

    def take(self, totake: str):
        self.currentAction = Actions.TAKE
        self.actionLauched = True
        self.transfered_object = totake

    def setdown(self, toset: str):
        self.currentAction = Actions.SET
        self.actionLauched = True
        self.transfered_object = toset

    def haveEnough(self, item:str):
        if item in self.need.keys():
            quantity = self.need[item]
        else:
            return True
        if self.inventoryMap[item] < quantity:
            return False
        return True

    def haveAllNeeded(self):
        for i in self.need.keys():
            if not self.haveEnough(i):
                return False
        return True

    def haveEnoughOnGround(self, item:str):
        if item in self.need.keys():
            quantity = self.need[item]
        else:
            return True
        if item in self.mapMemory[str(self.position)] and self.mapMemory[str(self.position)][item] < quantity:
            return False
        return True

    def haveNotToMuchOnGround(self, item:str):
        if item in self.need.keys():
            quantity = self.need[item]
        else:
            quantity = 0
        if item in self.mapMemory[str(self.position)] and self.mapMemory[str(self.position)][item] > quantity:
            return False
        return True

    def haveAllNeededOnGround(self):
        for i in self.need.keys():
            if not self.haveEnoughOnGround(i) or not self.haveNotToMuchOnGround(i):
                return False
        return True

    # Movments

    def _setPosition(self, newpos: list):
        self.position = newpos

    def _setDirection(self, newdir: Direction):
        self.direction = newdir

    def _turnRight(self, resp: str):
        if resp == "ok":
            self._setDirection(Direction((self.direction.value + 1) % 4))
        self._addOld(7)

    def _turnLeft(self, resp: str):
        if resp == "ok":
            self._setDirection(Direction((self.direction.value - 1) % 4))
        self._addOld(7)

    def _goForward(self, resp: str):
        if resp == "ok":
            vector_dir = self.vectorsDirection[self.direction.value]
            self._setPosition([self.position[0] + vector_dir[0],
                               self.position[1] + vector_dir[1]])
        self._addOld(7)

    def _goRight(self, resp: str):
        if resp == "ok":
            vector_dir = self.vectorsDirection[(self.direction.value + 1) % 4]
            self._setPosition([self.position[0] + vector_dir[0],
                               self.position[1] + vector_dir[1]])
        self._addOld(7)

    def _goLeft(self, resp: str):
        if resp == "ok":
            vector_dir = self.vectorsDirection[(self.direction.value - 1) % 4]
            self._setPosition([self.position[0] + vector_dir[0],
                               self.position[1] + vector_dir[1]])
        self._addOld(7)

    def _goBack(self, resp: str):
        if resp == "ok":
            vector_dir = self.vectorsDirection[(self.direction.value + 2) % 4]
            self._setPosition([self.position[0] + vector_dir[0],
                               self.position[1] + vector_dir[1]])
        self._addOld(7)

    def turnRight(self):
        self.currentAction = Actions.TURNRIGHT
        self.actionLauched = True

    def turnLeft(self):
        self.currentAction = Actions.TURNLEFT
        self.actionLauched = True

    def goForward(self):
        self.currentAction = Actions.GOFORWARD
        self.actionLauched = True

    # Look

    def _changePos(self, origin: list, vector: list) -> list:
        return [origin[0] + vector[0], origin[1] + vector[1]]

    def diffPos(self, origin: list, target: list) -> list:
        return [target[0] - origin[0], target[1] - origin[1]]

    def _addOld(self, nbr:int):
        self.lastLook += nbr
        for cell in self.mapMemory:
            self.mapMemory[cell]["old"] += nbr
        self.lastInventory += nbr

    def _readLook(self, response: str):
        self._addOld(7)
        self.lastLook = 0
        response = re.sub("\[", '', response)
        response = re.sub("\]", '', response)
        tab = response.split(",")
        anchor = 0
        for i in range(len(tab)):
            tab[i] = tab[i].strip()
        for i in range(len(tab)):
            cellMap = dict()
            cellMap["old"] = 0
            for j in tab[i].split():
                if j != "player":
                    if not j in cellMap.keys():
                        cellMap[j] = 0
                    cellMap[j] += 1
            pos = self.position
            if i >= self.lookSizes[anchor]:
                anchor += 1
            for j in range(anchor):
                pos = self._changePos(
                    pos, self.vectorsDirection[self.direction.value])
            pos_in_total = (i + 1)
            pos_in_line = self.linesSizes[anchor] - \
                abs(self.lookSizes[anchor] - pos_in_total)
            mid_line = self.linesSizes[anchor] // 2 + 1
            if pos_in_line < mid_line:
                for j in range(abs((mid_line) - (pos_in_line))):
                    pos = self._changePos(
                        pos, self.vectorsDirection[(self.direction.value - 1) % 4])
            if pos_in_line > mid_line:
                for j in range(abs((mid_line) - (pos_in_line))):
                    pos = self._changePos(
                        pos, self.vectorsDirection[(self.direction.value + 1) % 4])
            self.mapMemory[str(pos)] = cellMap

    def look(self):
        self.currentAction = Actions.LOOK
        self.actionLauched = True

    def posHasObject(self, pos: list, object: str):
        if not str(pos) in self.mapMemory.keys():
            return False
        map_objects = self.mapMemory[str(pos)]
        if not object in map_objects.keys() or map_objects[object] == 0:
            return False
        return True

    def posHasNeeded(self, pos: list):
        for item in self.need.keys():
            if not str(pos) in self.mapMemory.keys():
                continue
            map_objects = self.mapMemory[str(pos)]
            if not item in map_objects.keys() or map_objects[item] == 0:
                continue
            if self.haveEnough(item):
                continue
            return True
        return False

    def findObject(self, object:str) -> list:
        max_interest = 0.0
        found_pos = None
        for cell_pos in self.mapMemory.keys():
            cell = self.mapMemory[cell_pos]
            cell_pos = ast.literal_eval(cell_pos)
            old = cell["old"]
            if object in cell.keys():
                nbr = cell[object]
                interest = nbr / ((old % 7) + 1)
                if interest > max_interest:
                    max_interest = interest
                    found_pos = cell_pos
        return found_pos

    def searchForNeeded(self) -> list:
        max_interest = 0.0
        found_pos = None
        for item in self.need.keys():
            if self.need[item] == 0 or self.inventoryMap[item] >= self.need[item]:
                continue
            for cell_pos in self.mapMemory.keys():
                cell = self.mapMemory[cell_pos]
                cell_pos = ast.literal_eval(cell_pos)
                old = cell["old"]
                if item in cell.keys():
                    nbr = cell[item]
                    interest = nbr / ((old % 7) + 1)
                    if interest > max_interest:
                        max_interest = interest
                        found_pos = cell_pos
        return found_pos


    # Broadcasts

    def _broadcast(self, resp: str):
        if resp == "ok":
            pass
        self._addOld(7)

    def broadcast(self):
        self.currentAction = Actions.BROADCAST
        self.actionLauched = True

    def _receiveBroadcast(self, resp: str):
        print("Received message:", resp)

    # Eject

    def _beingEjected(self, resp:str):
        print("Have been ejected:", resp)

    def _eject(self, resp:str):
        if resp == "ok":
            pass
        self._addOld(7)

    def eject(self):
        self.currentAction = Actions.EJECT
        self.actionLauched = True

    #Incant

    def _incant(self, resp:str):
        if self.incantCounter != 1:
            if resp == "ko" and not self.isServerTest:
                return
            self.actionLauched = False
            self.incantCounter = 1
        elif resp != "ko":
            self.need = invChecks.INCANT2.value
            self.incantCounter = 0
        else:
            self.incantCounter = 0

    def incant(self):
        self.currentAction = Actions.INCANT
        self.actionLauched = True

    # Exec actions

    def computeServerResponse(self, resp: list):
        used = False
        for i in resp:
            for pattern in self.envHandler.keys():
                if re.match(pattern, i):
                    self.envHandler[pattern](i)
                    used = True
                    break
            if self.actionLauched and not used:
                self.actions[self.currentAction.value](i)
                if self.actionLauched == False:
                    self.actionLauched = True
                else:
                    self.actionLauched = False
            used = False
