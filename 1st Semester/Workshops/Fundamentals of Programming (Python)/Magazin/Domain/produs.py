class Produs:
    def __init__(self, id : int, denumire : str, pret : int):
        self.__id = id
        self.__denumire = denumire
        self.__pret = pret

    def __str__(self):
        return str(self.__id) + ',' + self.__denumire + ',' + str(self.__pret)

    def __eq__(self, other):
        return self.__id == other.__id and self.__pret == other.__pret and self.__denumire == other.__denumire

    @property
    def id(self):
        return self.__id

    @property
    def denumire(self):
        return self.__denumire

    @property
    def pret(self):
        return self.__pret

    @id.setter
    def id(self, value):
        self.__id = value

    @denumire.setter
    def denumire(self, value):
        self.__denumire = value

    @pret.setter
    def pret(self, value):
        self.__pret = value