import random

from Domain.piesa import Piesa
from Utils.sortare_piese import sortare


class Repository:
    def __init__(self, filename):
        self.__filename = filename

    def __load_from_file(self) -> list:
        """
        Functia returneaza lista cu piese din fisier
        :return: list
        """
        lista_piese = []
        with open(self.__filename,"r") as f:
            lines = f.readlines()
            for line in lines:
                titlu, regizor, gen, durata = line.strip().split(',')
                piesa = Piesa(titlu,regizor,gen,int(durata))
                lista_piese.append(piesa)
        return lista_piese

    def __store_to_file(self,lista_piese : list) -> None:
        """
        Functia stocheaza lista cu piese in fisier
        :param lista_piese: lista cu piese
        :return: None
        """
        with open(self.__filename,"w") as f:
            for piesa in lista_piese:
                piesa_line = piesa.titlu + "," + piesa.regizor + "," + piesa.gen + "," + str(piesa.durata) + '\n'
                f.write(piesa_line)

    def add_piesa(self, piesa : Piesa) -> None:
        """
        Functia adauga o piesa in fisier
        :param piesa: Piesa pe care o adaugam
        :return: None
        """
        lista_piese = self.get_all()
        lista_piese.append(piesa)
        self.__store_to_file(lista_piese)

    def modificare_piesa(self, piesa : Piesa) -> None:
        """
        Functia modifica o piesa in fisier
        :param piesa: Piesa pe care o modificam cu datele noi
        :return: None
        """
        lista_piese = self.get_all()
        for p in lista_piese:
            if p.titlu == piesa.titlu and p.regizor == piesa.regizor:
                p.gen = piesa.gen
                p.durata = piesa.durata
        self.__store_to_file(lista_piese)

    def exista_piesa(self, titlu : str, regizor : str) -> bool:
        """
        Functia verifica daca exista o piesa cu titlul si regizorul in lista de piese
        :param titlu: titlul piesei pe care o cautam
        :param regizor: regizorul piesei pe care o cautam
        :return: bool
        """
        lista_piese = self.get_all()
        for piesa in lista_piese:
            if piesa.titlu == titlu and piesa.regizor == regizor:
                return True
        return False

    def exporta(self, filename) -> None:
        """
        Functia exporta piesele in or
        :return: None
        """
        lista_piese = self.get_all()
        sortare(lista_piese)
        with open(filename,"w") as f:
            for piesa in lista_piese:
                piesa_line = piesa.titlu + "," + piesa.regizor + "," + piesa.gen + "," + str(piesa.durata) + '\n'
                f.write(piesa_line)

    def get_all(self):
        lista_piese = self.__load_from_file()
        return lista_piese