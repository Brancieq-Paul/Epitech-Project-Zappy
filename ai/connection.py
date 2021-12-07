##
## EPITECH PROJECT, 2021
## YEP
## File description:
## connection
##

import socket

class Connection:

    #Handle connection

    @classmethod
    def connection(cls, host:str, port:int, team:str) -> bool:
        cls.host = host
        if host == "localhost":
            host = socket.gethostbyname(socket.gethostname())
        cls.port = port
        cls.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        cls.socket.connect((cls.host, cls.port))
        print("Connection:", cls.recv())
        cls.send(team)
        print("Connection:", cls.recv())

    #Send

    @classmethod
    def send(cls, msg:str) -> bool:
        msg += "\n"
        cls.socket.send(msg.encode())

    #Receive

    @classmethod
    def recv(cls) -> list:
        resp = ""
        while resp == "" or resp[-1] != '\n':
            resp += cls.socket.recv(1024).decode('utf-8')
        return resp.split("\n")[:-1]