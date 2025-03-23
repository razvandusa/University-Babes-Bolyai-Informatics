from datetime import datetime

from Domain.domain import Automobil
from Repository.repository import Repository


class Service:
    def __init__(self, repository : Repository):
        self.__repository = repository

    def add_automobil(self, id : str, marca : str, pret : str, model : str, data : str) -> None:
        """
        Functia valideaza datele de intrare si adauga un automobil in fisier
        :param id: id-ul masinii pe care o adaugam
        :param marca: marca masinii pe care o adaugam
        :param pret: pretul masinii pe care o adaugam
        :param model: modelul masinii pe care o adaugam
        :param data: data de expirare a ITP-ului a masinii pe care o adaugam
        :return: None
        """
        try:
            id = int(id)
        except ValueError:
            raise ValueError("ID-ul trebuie sa fie un numar intreg!")

        try:
            pret = int(pret)
        except ValueError:
            raise ValueError("Pretul trebuie sa fie un numar intreg!")

        try:
            data = datetime.strptime(data,"%d/%m/%Y")
        except ValueError:
            raise ValueError("Data trebuie sa aiba formatul day/month/year!")

        automobil = Automobil(id,marca,pret,model,data)
        self.__repository.add_automobil(automobil)

    def delete_automobile(self, cifra : str) -> int:
        """
        Functia valideaza datele de intrare si sterge toate automobilele care contin cifra in pretul lor si returneaza numarul de automobile sterse
        :param cifra: cifra citita
        :return: numarul de automobile sterse
        """
        try:
            cifra = int(cifra)
        except ValueError:
            raise ValueError("Cifra trebuie sa fie un intreg!")

        if cifra < 0 or cifra > 9:
            raise ValueError("Cifra trebuie sa apartina intervalului [0,9]!")

        contor = self.__repository.delete_automobile(cifra)
        return contor

    def modificare_filtru(self, marca: str, pret: str) -> None:
        """
        Functia valideaza datele de intrare si modifica filtrul
        :return: None
        """
        try:
            pret = int(pret)
        except ValueError:
            raise ValueError("Pretul trebuie sa fie un intreg!")
        self.__repository.modificare_filtru(marca,pret)

    def filtrare_automobile(self):
        """
        Functia modifica lista de automobile dupa filtrul curent
        :return: None
        """
        self.__repository.filtrare_automobile()

    def expirat(self):
        """
        Functia modifica toate masinile ale caror ITP a expirat punand un * in fata marcii
        :return: None
        """
        self.__repository.expirat()

    def undo(self):
        """
        Functia verifica daca lista de undo este goala si daca nu este atunci face undo
        :return: None
        """
        if not self.__repository.get_lista_undo():
            raise ValueError("Nu se poate realiza operatia de undo!")
        self.__repository.undo()

    def get_filtru_marca(self):
        return self.__repository.get_filtru_marca()

    def get_filtru_pret(self):
        return self.__repository.get_filtru_pret()

    def get_lista_automobile_filtrate(self):
        return self.__repository.get_lista_automobile_filtrate()