##
## EPITECH PROJECT, 2021
## YEP
## File description:
## actions
##

from ai.connection import Connection

class BasesActions:

    #Env

    @classmethod
    def look(cls):
        Connection.send("Look")

    #Interaction

    @classmethod
    def broadcast(cls, message:str):
        Connection.send("Broadcast " + message)

    @classmethod
    def eject(cls):
        Connection.send("Eject")

    #Movments

    @classmethod
    def forward(cls):
        Connection.send("Forward")

    @classmethod
    def left(cls):
        Connection.send("Left")

    @classmethod
    def right(cls):
        Connection.send("Right")

    # Big actions

    @classmethod
    def fork(cls):
        Connection.send("Fork")

    @classmethod
    def incantation(cls):
        Connection.send("Incantation")

    #Object

    @classmethod
    def inventory(cls):
        Connection.send("Inventory")

    @classmethod
    def take(cls, object:str):
        Connection.send("Take " + object)

    @classmethod
    def setdown(cls, object:str):
        Connection.send("Set " + object)

    #Receive

    @classmethod
    def receive(cls) -> list:
        return(Connection.recv())