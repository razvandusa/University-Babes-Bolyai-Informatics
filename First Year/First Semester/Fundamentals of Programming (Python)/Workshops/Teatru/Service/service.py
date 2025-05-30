import random

from Domain.piesa import Piesa
from Repository.repository import Repository


class Service:
    def __init__(self, repository : Repository):
        self.__repository = repository

    def add_piesa(self, titlu : str, regizor : str, gen : str, durata : int) -> None:
        """
        Functia adauga o piesa in lista de piese daca aceasta este valida
        :param titlu: titlul piesei
        :param regizor: regizorul piesei
        :param gen: genul piesei
        :param durata: durata piesei
        :return: None
        """
        erori = []
        if titlu == "":
            erori.append("Titlul trebuie sa fie nevid!")
        if regizor == "":
            erori.append("Regizorul trebuie sa fie nevid!")
        try:
            durata = int(durata)
            if durata < 0:
                erori.append("Durata trebuie sa fie pozitiva!")
        except ValueError:
            erori.append("Durata trebuie sa fie intreaga!")
        if gen not in ["Comedie","Drama","Satira","Altele"]:
            erori.append("Genul trebuie sa fie : Comedie, Drama, Satira sau Altele!")
        if not erori:
            piesa = Piesa(titlu,regizor,gen,durata)
            self.__repository.add_piesa(piesa)
        else:
            raise ValueError('\n'.join(erori))

    def modifica_piesa(self, titlu : str, regizor : str, gen : str, durata : int) -> None:
        """
        Functia modifica o piesa deja existenta in lista de piese
        :param titlu: titlul piesei pe care vrem sa o modificam
        :param regizor: regizorul piesei pe care vrem sa o modificam
        :param gen: valoarea noua pentru genul piesei
        :param durata: valoarea noua pentru durata piesei
        :return: None
        """
        erori = []
        if not self.__repository.exista_piesa(titlu, regizor):
            erori.append("Nu exista piesa cu titlul si regizorul specificat!")
        if titlu == "":
            erori.append("Titlul trebuie sa fie nevid!")
        if regizor == "":
            erori.append("Regizorul trebuie sa fie nevid!")
        try:
            durata = int(durata)
            if durata < 0:
                erori.append("Durata trebuie sa fie pozitiva!")
        except ValueError:
            erori.append("Durata trebuie sa fie intreaga!")
        if gen not in ["Comedie", "Drama", "Satira", "Altele"]:
            erori.append("Genul trebuie sa fie : Comedie, Drama, Satira sau Altele!")
        if not erori:
            piesa = Piesa(titlu,regizor,gen,durata)
            self.__repository.modificare_piesa(piesa)
        else:
            raise ValueError('\n'.join(erori))

    @staticmethod
    def generare_titlu_regizor() -> str:
        """
        Functia genereaza un titlu/regizor
        :return: str
        """
        lungime = random.randint(8, 12)
        cuvant = ""
        vocala = ['a', 'e', 'i', 'o', 'u']
        consoana = [
            'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
            'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'
        ]
        for i in range(0, lungime):
            if i == lungime // 2:
                cuvant = cuvant + " "
            else:
                litera_random = None
                if i % 2 == 0:
                    litera_random = random.choice(consoana)
                if i % 2 == 1:
                    litera_random = random.choice(vocala)
                cuvant = cuvant + litera_random
        return cuvant

    @staticmethod
    def generare_gen() -> str:
        """
        Functia genereaza un gen random
        :return: str
        """
        genuri = ["Comedie", "Drama", "Satira", "Altele"]
        numar_random = random.randint(0, 3)
        return genuri[numar_random]

    @staticmethod
    def generare_durata() -> int:
        """
        Functia genereaza o durata random
        :return: int
        """
        durata = random.randint(1, 1000)
        return durata

    def creeaza_piese(self, n : int) -> None:
        """
        Functia genereaza n piese
        :param n: numarul de piese de generat
        :return: None
        """
        try:
            n = int(n)
        except ValueError:
            raise ValueError("Trebuie sa introduci un numar intreg!")
        for i in range(0,n):
            titlu = self.generare_titlu_regizor()
            regizor = self.generare_titlu_regizor()
            gen = self.generare_gen()
            durata = self.generare_durata()
            piesa = Piesa(titlu,regizor,gen,durata)
            self.__repository.add_piesa(piesa)

    def exporta(self, filename) -> None:
        """
        Functia exporta piesele de teatru sortate dupa regizor si titlu intr-un fisier text
        :return: None
        """
        try:
            with open(filename,"r") as f:
                pass
        except FileNotFoundError:
            raise ValueError("Nu s-a putut deschide fisierul!")
        self.__repository.exporta(filename)