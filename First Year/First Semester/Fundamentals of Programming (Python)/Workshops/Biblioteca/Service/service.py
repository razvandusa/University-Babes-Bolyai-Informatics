from Domain.carte import Carte
from Repository.repository import Repository


class Service:
    def __init__(self, repository : Repository):
        self.__repository = repository

    def adauga_carte(self, id : str, titlu : str, autor : str, anAparitie : str) -> None:
        """
        Functia adauga o carte cu datele oferite daca acestea sunt corecte
        :param id: id-ul cartii
        :param titlu: titlul cartii
        :param autor: autorul cartii
        :param anAparitie: anul de aparitie al cartii
        :return: None
        """
        try:
            id = int(id)
        except ValueError:
            raise ValueError("ID-ul trebuie sa fie un intreg!")
        try:
            anAparitie = int(anAparitie)
        except ValueError:
            raise ValueError("Anul aparitiei trebuie sa fie un intreg!")
        carte = Carte(id,titlu,autor,anAparitie)
        self.__repository.add_carte(carte)

    def sterge_carte(self, cifra : str) -> None:
        """
        Functia sterge cartile pentru care anul de aparitie contine cifra data
        :param cifra: cifra data
        :return: None
        """
        try:
            cifra = int(cifra)
        except ValueError:
            raise ValueError("Cifra trebuie sa fie un intreg")
        if cifra >= 10 or cifra < 0:
            raise  ValueError("Cifra trebuie sa fie in intervalul [0,9]!")
        self.__repository.sterge_carti(cifra)

    def modificare_filtru(self, text : str, numar : str) -> None:
        """
        Functia modifica filtrul
        :param text: noul filtru pentru text
        :param numar: noul filtru pentru numar
        :return: None
        """
        try:
            numar = int(numar)
        except ValueError:
            raise ValueError("Numarul trebuie sa fie intreg!")
        self.__repository.modificare_filtru(text,numar)

    def undo(self):
        """
        Functia realizeaza operatia de undo pentru ultima operatie de stergere
        :return: None
        """
        if len(self.__repository.get_lista_carti_sterse()) == 0:
            raise ValueError("Nu se poate face operatia de undo!")
        self.__repository.undo()

    def get_filtru_lista_carti(self) -> tuple[list,list]:
        """
        Functia returneaza filtrul si lista cartilor
        :return: filtru + lista_cartilor filtrate
        """
        filtru, lista_carti = self.__repository.get_lista_carti_filtrate()
        return filtru,lista_carti