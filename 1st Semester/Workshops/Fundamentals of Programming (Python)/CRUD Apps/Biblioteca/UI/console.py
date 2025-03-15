from colorama import Fore, Style

from Service.service import Service


class Console:
    def __init__(self, service : Service):
        self.__service = service

    def add_carte_UI(self):
        id = input("Scrie id-ul cartii pe care vrei sa o adaugi: ")
        titlu = input("Scrie titlul cartii pe care vrei sa o adaugi: ")
        autor = input("Scrie autorul cartii pe care vrei sa o adaugi: ")
        anAparitie = input("Scrie anul aparitiei a cartii pe care vrei sa o adaugi: ")
        try:
            self.__service.adauga_carte(id, titlu, autor, anAparitie)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def sterge_carti_UI(self):
        cifra = input("Scrie cifra pentru care se sterg toate cartile care contin aceasta cifra in anul de aparitie: ")
        try:
            self.__service.sterge_carte(cifra)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def modificare_filtru_UI(self):
        text = input("Cartile o sa fie filtrate dupa titlu care contin textul: ")
        pretul = input("Cartile o sa fie filtrate dupa pretul care este mai mid decat: ")
        try:
            self.__service.modificare_filtru(text,pretul)
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    def afisare_filtru_lista_carti_UI(self):
        filtru, lista_carti_filtrata = self.__service.get_filtru_lista_carti()
        print(f"Filtrul este : {filtru}")
        print(f"Lista cartilor filtrate este :")
        for carte in lista_carti_filtrata:
            print(carte)

    def undo_Ui(self):
        try:
            self.__service.undo()
        except ValueError as msg:
            print(Fore.RED + str(msg) + Style.RESET_ALL)

    @staticmethod
    def meniu():
        print("Alege optiunea:")
        print("1. " + Fore.GREEN + "Adaugare de carte" + Style.RESET_ALL)
        print("2. " + Fore.GREEN + "Sterge carti" + Style.RESET_ALL)
        print("3. " + Fore.GREEN + "Modificare filtru" + Style.RESET_ALL)
        print("4. " + Fore.GREEN + "Undo" + Style.RESET_ALL)
        print("e. " + Fore.RED + "EXIT" + Style.RESET_ALL)

    def run(self):
        run = True
        while run:
            self.meniu()
            optiune = input().lower()
            match optiune:
                case "1":
                    self.add_carte_UI()
                case "2":
                    self.sterge_carti_UI()
                case "3":
                    self.modificare_filtru_UI()
                case "4":
                    self.undo_Ui()
                case "e":
                    run = False
                case _:
                    print("Nu exista aceasta optiune!")
            if run:
                self.afisare_filtru_lista_carti_UI()