from datetime import datetime

from Domain.domain import Automobil


class Repository:
    def __init__(self, filename):
        self.__filename = filename
        self.__filtru = ["",-1]
        self.__lista_automobile_filtrate = []
        self.__lista_undo = []

    def __load_from_file(self) -> list:
        """
        Functia incarca din fisier lista cu automobile
        :return: lista cu automobile
        """
        lista_automobile = []
        with open(self.__filename,"r") as f:
            lines = f.readlines()
            for line in lines:
                id, marca, pret, model, data = line.strip().split(',')
                data = datetime.strptime(data,"%d/%m/%Y")
                automobil = Automobil(int(id),marca,int(pret),model,data)
                lista_automobile.append(automobil)
        return lista_automobile

    def __store_to_file(self, lista_automobile : list) -> None:
        """
        Functia incarca in fisier lista cu automobile
        :return: None
        """
        with open(self.__filename,"w") as f:
            for automobil in lista_automobile:
                data = str(automobil.data.day) + '/' + str(automobil.data.month) + '/' + str(automobil.data.year)
                automobil_line = str(automobil.id) + ',' + automobil.marca + ',' + str(automobil.pret) + ',' + automobil.model + ',' + data + '\n'
                f.write(automobil_line)

    def add_automobil(self, automobil : Automobil) -> None:
        """
        Functia adauga un automobil in fisier
        :param automobil: Automobilul pe care il adaugam
        :return: None
        """
        lista_automobile = self.get_all()
        lista_automobile.append(automobil)
        self.__lista_undo.append([])
        self.__store_to_file(lista_automobile)

    def delete_automobile(self, cifra : int) -> int:
        """
        Functia sterge toate automobilele care contin cifra in pretul lor si returneaza numarul de automobile sterse
        :param cifra: cifra citita
        :return: numarul de automobile sterse
        """
        lista_automobile = self.get_all()
        lista_automobile_ramase = [automobil for automobil in lista_automobile if str(cifra) not in str(automobil.pret)]
        self.__store_to_file(lista_automobile_ramase)
        lista_automobile_sterse = [automobil for automobil in lista_automobile if str(cifra) in str(automobil.pret)]
        self.__lista_undo.append(lista_automobile_sterse)
        return len(lista_automobile_sterse)

    def modificare_filtru(self, marca : str, pret : int) -> None:
        """
        Functia modifica filtrul
        :return: None
        """
        self.__filtru[0] = marca
        self.__filtru[1] = pret

    def filtrare_automobile(self) -> None:
        """
        Functia modifica lista de automobile dupa filtrul curent
        :return: None
        """
        filtru_marca = self.get_filtru_marca()
        filtru_pret = self.get_filtru_pret()
        lista_automobile = self.get_all()
        if filtru_pret == -1:
            self.__lista_automobile_filtrate = [automobil for automobil in lista_automobile if filtru_marca in automobil.marca]
        else:
            self.__lista_automobile_filtrate = [automobil for automobil in lista_automobile if filtru_marca in automobil.marca and automobil.pret < filtru_pret]

    def expirat(self) -> None:
        """
        Functia modifica toate masinile ale caror ITP a expirat punand un * in fata marcii
        :return: None
        """
        lista_automobile = self.get_all()
        for automobil in lista_automobile:
            if automobil.data < datetime.today() and automobil.marca[0] != '*':
                automobil.marca = '*' + automobil.marca
        self.__store_to_file(lista_automobile)

    def undo(self):
        """
        Functia realizeaza operatia de undo
        :return: None
        """
        lista_automobile = self.get_all()
        ultimele_automobile = self.__lista_undo.pop()
        if ultimele_automobile == []:
            lista_automobile.pop()
        else:
            for automobil in ultimele_automobile:
                lista_automobile.append(automobil)
        self.__store_to_file(lista_automobile)

    def get_filtru_marca(self):
        return self.__filtru[0]

    def get_filtru_pret(self):
        return self.__filtru[1]

    def get_all(self):
        return self.__load_from_file()

    def get_lista_automobile_filtrate(self):
        return self.__lista_automobile_filtrate

    def get_lista_undo(self):
        return self.__lista_undo