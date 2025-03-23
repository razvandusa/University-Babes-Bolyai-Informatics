from sys import audit


class Carte:
    def __init__(self, id : int, titlu : str, autor : str, anAparitie : int):
        self.__id = id
        self.__titlu = titlu
        self.__autor = autor
        self.__anAparitie = anAparitie

    def __eq__(self, other):
        if not isinstance(other,Carte):
            return False
        return self.__id == other.__id and self.__titlu == other.__titlu and self.__autor == other.__autor and self.__anAparitie == other.__anAparitie

    def __str__(self):
        return str(self.__id) + ',' + self.__titlu + ',' + self.__autor + ',' + str(self.anAparitie)

    @property
    def id(self):
        return self.__id

    @property
    def titlu(self):
        return self.__titlu

    @property
    def autor(self):
        return self.__autor

    @property
    def anAparitie(self):
        return self.__anAparitie

    @id.setter
    def id(self, value : int):
        self.__id = value

    @titlu.setter
    def titlu(self,value : str):
        self.__titlu = value

    @autor.setter
    def autor(self, value : str):
        self.__autor = value

    @anAparitie.setter
    def anAparitie(self, value : int):
        self.__anAparitie = value