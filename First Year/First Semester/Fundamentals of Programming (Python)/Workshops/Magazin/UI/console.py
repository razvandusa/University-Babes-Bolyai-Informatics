import colorama
from colorama import Fore, Style

from Service.service import Service


class Console:
    def __init__(self, service : Service):
        self.__service = service

    @staticmethod
    def meniu():
        print("Alege optiunea:")
        print("1 - Adauga un produs")
        print("2 - Sterge un produs")
        print("3 - Filtrare produs")
        print("4 - Undo")
        print("e - Iesire")

    def adaugare_produs_ui(self):
        id = input("Introduceti ID-ul produsului: ")
        denumire  = input("Introduceti denumirea produsului: ")
        pret = input("Introduceti pretul produsului: ")
        try:
            self.__service.adaugare_produs(id, denumire, pret)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def stergere_produs_ui(self):
        cifra = input("Stergeti produsele ale caror ID-uri contin cifra: ")
        try:
            self.__service.stergere_produs(cifra)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def modificare_filtru_ui(self):
        text = input("Seteaza filtru pentru text: ")
        pret = input("Seteaza filtru pentru pret: ")
        try:
            self.__service.modificare_filtru(text,pret)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def undo_ui(self):
        try:
            self.__service.undo()
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def afisare_filtru_lista_filtrata(self):
        filtru_text,filtru_pret = self.__service.get_filtru()
        lista_produse_filtrate = self.__service.get_lista_produse_filtrate()
        print(f"Filtrul pentru text este: {filtru_text}")
        print(f"Filtrul pentru pret este: {filtru_pret}")
        print("Lista filtrata este: ")
        for produs in lista_produse_filtrate:
            print(produs)

    def run(self):
        run = True
        while run:
            self.meniu()
            optiune = input("Optiune: ")
            if optiune == "1":
                self.adaugare_produs_ui()
            elif optiune == "2":
                self.stergere_produs_ui()
            elif optiune == "3":
                self.modificare_filtru_ui()
            elif optiune == "4":
                self.undo_ui()
            elif optiune == "e":
                run = False
            else:
                print("Aceasta optiune nu exista!")
            if run:
                self.afisare_filtru_lista_filtrata()