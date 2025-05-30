import random

from Domain.emisiune import Emisiune
from Utils.program_utils import sum_of_hours


class Repository:
    def __init__(self, filename):
        self.__filename = filename
        self.__blocked_list = []

    def load_from_file(self) -> list:
        """
        Aceasta functie va prelua toate emisiunile din fisier
        :return: lista cu emisiuni
        """
        emisiuni = []
        with open(self.__filename, "r") as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                nume, tip, descriere, durata = line.split(",")
                emisiune = Emisiune(nume, tip, descriere, int(durata))
                emisiuni.append(emisiune)
        return emisiuni

    def store_to_file(self, emisiuni: list) -> None:
        """
        Aceasta functie va stoca lista de emisiuni in fisier
        :param emisiuni: lista de emisiuni
        :return: None
        """
        with open(self.__filename, "w") as f:
            for emisiune in emisiuni:
                emisiune_line = (
                    emisiune.nume
                    + ","
                    + emisiune.tip
                    + ","
                    + emisiune.descriere
                    + ","
                    + str(emisiune.durata)
                    + "\n"
                )
                f.write(emisiune_line)

    def delete_emisiune(self, nume: str, tip: str) -> None:
        """
        Functia sterge o emisiune
        :param nume: numele emisiunii
        :param tip: tipul emisiunii
        :return: None
        """
        emisiuni = self.get_all()
        for index, emisiune in enumerate(emisiuni):
            if emisiune.nume == nume and emisiune.tip == tip:
                emisiuni.pop(index)
                self.store_to_file(emisiuni)

    def update_emisiune(self, nume: str, tip: str, descriere: str, durata: int) -> None:
        """
        Functia modifica durata si descrierea unei emisiuni
        :param nume: numele emisiunii
        :param tip: tipul emisiunii
        :param durata: durata noua a emisiunii
        :param descriere: descrierea noua a emisiunii
        :return: None
        """
        emisiuni = self.get_all()
        for emisiune in emisiuni:
            if emisiune.nume == nume and emisiune.tip == tip:
                emisiune.durata = durata
                emisiune.descriere = descriere
                self.store_to_file(emisiuni)

    def program_emisiuni(self, start_hour : int, end_hour : int) -> list:
        """
        Functia pune intr-un interval de timp programe ale caror durata adunata nu depaseste programul
        :param start_hour: ora de inceput
        :param end_hour: ora de sfarsit
        :return: programul cu emisiuni
        """
        emisiuni = self.get_all()
        random.shuffle(emisiuni)
        diferenta = end_hour - start_hour
        program = []
        for emisiune in emisiuni:
            if not self.emisiune_blocata(emisiune.tip) and sum_of_hours(program) + emisiune.durata <= diferenta:
                program.append(emisiune)
        return program

    def add_to_blocked_list(self, tip : str) -> None:
        """
        Functia adauga in lista de tipuri blocate un tip
        :param tip: tip-ul pe care vrem sa il blocam
        :return: None
        """
        emisiuni = self.get_all()
        for emisiune in emisiuni:
            if emisiune.tip == tip and emisiune not in self.__blocked_list:
                self.__blocked_list.append(emisiune)
        self.store_to_file(emisiuni)

    def remove_from_blocked_list(self, tip : str) -> None:
        """
        Functia sterge din lista de tipuri blocate un tip
        :param tip: tip-ul pe care sa il stergem din lista
        :return: None
        """
        emisiuni = self.get_all()
        for emisiune in emisiuni:
            if emisiune.tip == tip:
                self.__blocked_list.remove(emisiune)
        self.store_to_file(emisiuni)

    def emisiune_blocata(self, tip : str) -> bool:
        """
        Functia verifica daca exista un tip in lista cu tipuri de emisiuni blocate
        :param tip: tipul emisiunii
        :return: True/False daca exista sau nu emisiunea
        """
        emisiuni = self.get_blocked_list()
        for emisiune in emisiuni:
            if emisiune.tip == tip:
                return True
        return False

    def get_blocked_list(self) -> list:
        """
        Functia returneaza lista cu tipurile blocate
        :return: lista cu tipurile blocate
        """
        return self.__blocked_list

    def get_all(self) -> list:
        """
        Functia returneaza toate emisiunile
        :return: lista cu emisiuni
        """
        return self.load_from_file()
