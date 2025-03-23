from datetime import datetime


class Automobil:
    def __init__(self, id : int, marca : str, pret : int, model : str, data : datetime):
        self.__id = id
        self.__marca = marca
        self.__pret = pret
        self.__model = model
        self.__data = data

    def __eq__(self, other):
        return self.__id == other.__id and self.__marca == other.__marca and self.__pret == other.__pret and self.__model == other.__model and self.__data == other.__data

    def __str__(self):
        return str(self.__id) + ',' + self.__marca + ',' + str(self.__pret) + ',' + self.__model + ',' + datetime.strftime(self.__data,"%d/%m/%Y")

    @property
    def id(self):
        return self.__id

    @property
    def marca(self):
        return self.__marca

    @property
    def pret(self):
        return self.__pret

    @property
    def model(self):
        return self.__model

    @property
    def data(self):
        return self.__data

    @id.setter
    def id(self, value : int):
        self.__id = value

    @marca.setter
    def marca(self, value : str):
        self.__marca = value

    @pret.setter
    def pret(self, value : int):
        self.__pret = value

    @model.setter
    def model(self, value : str):
        self.__model = value

    @data.setter
    def data(self, value : datetime):
        self.__data = value