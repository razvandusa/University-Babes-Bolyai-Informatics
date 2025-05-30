import colorama
from colorama import Fore, Style

from Service.service import Service


class Console:
    def __init__(self, service: Service):
        self.__service = service

    @staticmethod
    def info():
        print(Fore.GREEN + "Comenzi :" + Style.RESET_ALL)
        print("1. nume + tip -> emisiunea se sterge")
        print(
            "2. nume + tip + durata + descriere -> se actualizeaza durata si descrierea emisiunii"
        )
        print("3. ora de inceput + ora de sfarsit -> se tipareste programul")
        print("4. blocheaza un tip de emisiune")
        print("5. deblocheaza un tip de emisiune")
        print("e. Exit")

    def delete_emisiune_UI(self):
        try:
            nume = input("Scrie numele emisiunii pe care vrei sa o stergi: ")
            tip = input("Scrie tipul emisiunii pe care vrei sa o stergi: ")
            self.__service.delete_emisiune(nume, tip)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def update_emisiune_UI(self):
        try:
            nume = input("Scrie numele emisiunii pe care vrei sa o modifici: ")
            tip = input("Scrie tipul emisiunii pe care vrei sa o modifici: ")
            descriere = input("Scrie noua descriere pe care vrei ca emisiunea ta sa o aiba: ")
            durata = int(input("Scrie noua durata pe care vrei ca emisiunea ta sa o aiba: "))
            self.__service.update_emisiune(nume,tip,descriere,durata)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def program_emisiuni_UI(self):
        try:
            start_hour = int(input("Scrie ora de start a programului: "))
            end_hour = int(input("Scrie ora de sfarsit a programului: "))
            actual_hour = start_hour
            program = self.__service.program_emisiuni(start_hour,end_hour)
            for emisiune in program:
                print(f"{actual_hour}.00 {emisiune}")
                actual_hour += emisiune.durata
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def add_to_blocked_list_UI(self):
        try:
            tip = input("Alege tip-ul emisiunii pe care vrei sa o blochezi: ")
            self.__service.add_to_blocked_list(tip)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def remove_from_blocked_list_UI(self):
        try:
            tip = input("Alege tip-ul emisiunii pe care vrei sa o deblochezi: ")
            self.__service.remove_from_blocked_list(tip)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def run(self):
        run = True
        while run:
            self.info()
            optiune = input().lower()
            match optiune:
                case "1":
                    self.delete_emisiune_UI()
                case "2":
                    self.update_emisiune_UI()
                case "3":
                    self.program_emisiuni_UI()
                case "4":
                    self.add_to_blocked_list_UI()
                case "5":
                    self.remove_from_blocked_list_UI()
                case "e":
                    run = False
                case _:
                    print("Aceasta optiune nu exista!")
