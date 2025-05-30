from Domain.carte import Carte


class Repository:
    def __init__(self, filename):
        self.__filename = filename
        self.__filtru = ["",-1]
        self.__lista_carti_filtrate = self.get_all()
        self.__lista_carti_sterse = []

    def __load_from_file(self) -> list:
        """
        Functia incarca toate cartile dintr-un fisier text intr-o lista
        :return: lista cu carti
        """
        lista_carti = []
        with open(self.__filename,"r") as f:
            lines = f.readlines()
            for line in lines:
                id,titlu,autor,anAparitie = line.strip().split(',')
                carte = Carte(int(id),titlu,autor,int(anAparitie))
                lista_carti.append(carte)
        return lista_carti

    def __store_to_file(self, lista_carti : list) -> None:
        """
        Functia stocheaza intr-un fisier o lista cu carti
        :param lista_carti: lista cu carti pe care o stocam
        :return: None
        """
        with open(self.__filename,"w") as f:
            for carte in lista_carti:
                carte_line = str(carte.id) + ',' + carte.titlu + ',' + carte.autor + ',' + str(carte.anAparitie) + '\n'
                f.write(carte_line)

    def add_carte(self, carte : Carte) -> None:
        """
        Functia adauga o carte in fisier
        :param carte: cartea pe care o adaugam
        :return: None
        """
        lista_carti = self.get_all()
        lista_carti.append(carte)
        self.__store_to_file(lista_carti)

    def sterge_carti(self, cifra : int) -> None:
        """
        Functia sterge cartile pentru care anul de aparitie contine cifra data
        :param cifra: cifra data
        :return: None
        """
        lista_carti = self.get_all()
        self.__lista_carti_sterse.append([carte for carte in lista_carti if str(cifra) in str(carte.anAparitie)])
        lista_carti = [carte for carte in lista_carti if str(cifra) not in str(carte.anAparitie)]
        self.__store_to_file(lista_carti)

    def modificare_filtru(self, text : str, numar : int) -> None:
        """
        Functia modifica filtrul
        :param text: noul filtru pentru text
        :param numar: noul filtru pentru numar
        :return: None
        """
        self.__filtru =[text,numar]
        self.__lista_carti_filtrate = self.get_all()
        self.__lista_carti_filtrate = [carte for carte in self.__lista_carti_filtrate if text in carte.titlu]

    def undo(self) -> None:
        """
        Functia realizeaza operatia de undo pentru ultima operatie de stergere
        :return: None
        """
        lista_carti = self.get_all()
        ultimele_carti_sterse = self.__lista_carti_sterse[-1]
        for carte in ultimele_carti_sterse:
            lista_carti.append(carte)
        self.__store_to_file(lista_carti)

    def get_all(self) -> list:
        """
        Functia returneaza toate cartile dintr-un fisier
        :return: lista cu carti
        """
        lista_carti = self.__load_from_file()
        return lista_carti

    def get_lista_carti_filtrate(self) -> tuple[list,list]:
        """
        Functia returneaza filtrul si lista cartilor
        :return: filtru + lista_cartilor filtrate
        """
        self.modificare_filtru(self.__filtru[0],self.__filtru[1])
        return self.__filtru,self.__lista_carti_filtrate

    def get_lista_carti_sterse(self) -> list:
        """
        Functia returneaza lista de carti sterse
        :return: lista cartilor sterse
        """
        return self.__lista_carti_sterse