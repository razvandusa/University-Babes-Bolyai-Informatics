from colorama import Fore, Style
from Service.service import Service


class Console:
    def __init__(self, service : Service):
        self.__service = service

    def adauga_piesa_UI(self):
        titlu = input("Scrie titlul piesei pe care vrei sa o adaugi: ")
        regizor = input("Scrie regizorul piesei pe care vrei sa o adaugi: ")
        gen = input("Scrie genul piesei pe care vrei sa o adaugi: ")
        durata =input("Scrie durata piesei pe care vrei sa o adaugi: ")
        try:
            self.__service.add_piesa(titlu,regizor,gen,durata)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def modifica_piesa_UI(self):
        titlu = input("Scrie titlul piesei pe care vrei sa o modifici: ")
        regizor = input("Scrie regizorul piesei pe care vrei sa o modifici: ")
        gen = input("Scrie noul gen pe care vrei sa il aiba piesa ta: ")
        durata = input("Scrie noua durata pe care vrei sa o aiba piesa ta: ")
        try:
            self.__service.modifica_piesa(titlu,regizor,gen,durata)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def creeaza_piese_UI(self):
        n = input("Scrie cate piese doresti sa creezi: ")
        try:
            self.__service.creeaza_piese(n)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def exporta_UI(self):
        filename = input("Scrie numele fisierului in care exporti: ")
        try:
            self.__service.exporta(filename)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    @staticmethod
    def meniu():
        print("Alege optiunea:")
        print("1. " + Fore.GREEN + "Adauga piesa" + Style.RESET_ALL)
        print("2. " + Fore.GREEN + "Modifica piesa" + Style.RESET_ALL)
        print("3. " + Fore.GREEN + "Creeaza piese" + Style.RESET_ALL)
        print("4. " + Fore.GREEN + "Exporta piese" + Style.RESET_ALL)
        print("E. " + Fore.RED + "EXIT" + Style.RESET_ALL)

    def run(self):
        run = True
        while run:
            self.meniu()
            optiune = input().lower()
            match optiune:
                case "1":
                    self.adauga_piesa_UI()
                case "2":
                    self.modifica_piesa_UI()
                case "3":
                    self.creeaza_piese_UI()
                case "4":
                    self.exporta_UI()
                case "e":
                    run = False
                case _:
                    print("Aceasta optiune nu exista!")