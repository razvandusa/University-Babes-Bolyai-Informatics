from Repository.repository import Repository


class Service:
    def __init__(self, repository : Repository):
        self.__repository = repository

    def adaugare_produs(self, id : int, denumire : str, pret : int):
        """
        Functia valideaza datele unui produs si il adauga daca datele sunt valide
        :param id: Id-ul produsului pe care il adaugam
        :param denumire: Denumirea produsului pe care il adaugam
        :param pret: Pretul produsului pe care il adaugam
        :return: None
        """
        try:
            id = int(id)
        except ValueError:
            raise ValueError("Id-ul trebuie sa fie un numar intreg")

        try:
            pret = int(pret)
        except ValueError:
            raise ValueError("Pretul trebuie sa fie un numar intreg")

        if pret <= 0:
            raise ValueError("Pretul trebuie sa fie mai mare decat 0")
        self.__repository.adaugare_produs(id, denumire, pret)

    def stergere_produs(self, cifra : int):
        """
        Functia valideaza daca cifra este intreaga si sterge toate produsele din lista ale caror ID-uri contin acea cifra
        :param cifra: Cifra data
        :return: None
        """
        try:
            cifra = int(cifra)
        except ValueError:
            raise ValueError("Cifra nu este un numar intreg")
        self.__repository.stergere_produse(cifra)

    def undo(self):
        """
        Functia verifica daca se poate reface ultima operatie de stergere si o face
        :return: None
        """
        lista_undo = self.__repository.get_lista_undo()
        if not lista_undo:
            raise ValueError("Nu se poate face undo")
        self.__repository.undo()

    def modificare_filtru(self, text : str, pret : int) -> None:
        """
        Functia valideaza datele de intrare si modifica filtrul
        :return: None
        """
        try:
            pret = int(pret)
        except ValueError:
            raise ValueError("Pretul trebuie sa fie un numar intreg")
        self.__repository.set_filtru_text(text)
        self.__repository.set_filtru_pret(pret)

    def get_lista_produse_filtrate(self):
        self.__repository.filtrare_produse()
        return self.__repository.get_lista_produse_filtrate()

    def get_filtru(self):
        return self.__repository.get_filtru()