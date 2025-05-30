from Domain.emisiune import Emisiune
from Repository.repository import Repository
from Utils.program_utils import sum_of_hours


class Service:
    def __init__(self, repository: Repository):
        self.__repository = repository

    def delete_emisiune(self, nume: str, tip: str):
        """
        Functia sterge o emisiune si verifica ca aceasta emisiune exista
        :param nume: numele emisiunii
        :param tip: tipul emisiunii
        :return: None
        """
        if self.__repository.emisiune_blocata(tip):
            raise ValueError("emisiune blocata")
        before = self.__repository.get_all()
        self.__repository.delete_emisiune(nume, tip)
        after = self.__repository.get_all()
        if before == after:
            raise ValueError("Nu exista aceasta emisiune in fisier!")

    def update_emisiune(self, nume: str, tip: str, descriere: str, durata: int):
        """
        Functia modifica durata si descrierea unei emisiuni si verifica ca aceasta emisiune exista
        :param nume: numele emisiunii
        :param tip: tipul emisiunii
        :param durata: durata noua a emisiunii
        :param descriere: descrierea noua a emisiunii
        :return: None
        """
        if self.__repository.emisiune_blocata(tip):
            raise ValueError("emisiune blocata")
        before = self.__repository.get_all()
        self.__repository.update_emisiune(nume, tip, descriere, durata)
        after = self.__repository.get_all()
        if before == after:
            raise ValueError("Nu exista aceasta emisiune in fisier!")

    def program_emisiuni(self, start_hour : int, end_hour : int) -> list:
        """
        Functia pune intr-un interval de timp programe ale caror durata adunata nu depaseste programul si adauga programe daca nu sunt suficiente
        :param start_hour: ora de inceput
        :param end_hour: ora de sfarsit
        :return: programul cu emisiuni + rulari de emisiuni
        """
        program = self.__repository.program_emisiuni(start_hour,end_hour)
        emisiuni = self.__repository.get_all()
        valid = True
        while valid:
            valid = False
            for emisiune in emisiuni:
                if not self.__repository.emisiune_blocata(emisiune.tip) and sum_of_hours(program) + emisiune.durata <= end_hour - start_hour :
                    valid = True
                    e = Emisiune(emisiune.nume,emisiune.tip,"****",emisiune.durata)
                    program.append(e)
        return program

    def add_to_blocked_list(self, tip : str):
        """
        Functia adauga in lista de tipuri blocate un tip
        :param tip: tip-ul pe care vrem sa il blocam
        :return: None
        """
        self.__repository.add_to_blocked_list(tip)

    def remove_from_blocked_list(self, tip : str) -> None:
        """
        Functia sterge din lista de tipuri blocate un tip
        :param tip: tip-ul pe care sa il stergem din lista
        :return: None
        """
        self.__repository.remove_from_blocked_list(tip)