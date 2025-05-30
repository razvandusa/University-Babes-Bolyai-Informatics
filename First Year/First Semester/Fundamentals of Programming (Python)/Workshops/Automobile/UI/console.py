from colorama import Fore, Style

from Service.service import Service

class Console:
    def __init__(self, service : Service):
        self.__service = service

    def add_automobil_ui(self):
        id = input("Scrie ID-ul masinii pe care vrei sa o adaugi: ")
        marca = input("Scrie marca masinii pe care vrei sa o adaugi: ")
        pret = input("Scrie pretul masinii pe care vrei sa o adaugi: ")
        model = input("Scrie modelul masinii pe care vrei sa o adaugi: ")
        data = input("Scrie data (formatul : zi/luna/an) la care expira inspectia tehnica a masinii pe care vrei sa o adaugi: ")
        try:
            self.__service.add_automobil(id,marca,pret,model,data)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def delete_automobile_ui(self):
        cifra = input("Scrie cifra pentru care doresti sa se stearga toate automobilele care contin acea cifra in pret: ")
        try:
            contor = self.__service.delete_automobile(cifra)
            print(f"Numarul masinilor sterse este : {contor}")
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def filtrare_automobile_ui(self):
        filtru_marca = input("Filtrul dupa marca este: ")
        filtru_pret = input("Filtrul dupa pret este: ")
        try:
            self.__service.modificare_filtru(filtru_marca,filtru_pret)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def afisare_automobile_filtrate_ui(self):
        filtru_marca = self.__service.get_filtru_marca()
        filtru_pret = self.__service.get_filtru_pret()
        self.__service.expirat()
        self.__service.filtrare_automobile()
        lista_automobile_filtrate = self.__service.get_lista_automobile_filtrate()
        print(f"Filtrul pentru marca este : {filtru_marca}, iar filtrul pentru pret este : {filtru_pret}")
        print("Lista de masini filtrata este :")
        for automobil in lista_automobile_filtrate:
            print(automobil)

    def undo_ui(self):
        try:
            self.__service.undo()
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    @staticmethod
    def meniu():
        print("Alegeti optiunea:")
        print("1. " + Fore.GREEN + "Adauga automobil" + Style.RESET_ALL)
        print("2. " + Fore.GREEN + "Sterge automobile" + Style.RESET_ALL)
        print("3. " + Fore.GREEN + "Filtrare automobile" + Style.RESET_ALL)
        print("4. " + Fore.GREEN + "Undo" + Style.RESET_ALL)
        print("e. " + Fore.RED + "EXIT" + Style.RESET_ALL)

    def run(self):
        run = True
        while run:
            self.meniu()
            optiune = input().strip().lower()
            match optiune:
                case "1":
                    self.add_automobil_ui()
                case "2":
                    self.delete_automobile_ui()
                case "3":
                    self.filtrare_automobile_ui()
                case "4":
                    self.undo_ui()
                case "e":
                    run = False
                case _:
                    pass
            if run:
                self.afisare_automobile_filtrate_ui()