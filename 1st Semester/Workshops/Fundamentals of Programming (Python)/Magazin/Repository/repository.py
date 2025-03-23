from Domain.produs import Produs


class Repository:
    def __init__(self, filename):
        self.__filename = filename
        self.__lista_undo = []
        self.__lista_produse_filtrate = []
        self.__filtrare = ["",-1]

    def __load_from_file(self) -> list:
        """
        Functia preia din fisier toate produsele si le pune intr-o lista
        :return: lista cu produse
        """
        lista_produse = []
        with open(self.__filename,"r") as f:
            lines = f.readlines()
            for line in lines:
                id, denumire, pret = line.strip().split(',')
                produs = Produs(int(id),denumire,int(pret))
                lista_produse.append(produs)
        return lista_produse

    def __store_to_file(self, lista_produse : list) -> None:
        """
        Functia o sa stocheze o lista de produse in fisier
        :return: None
        """
        with open(self.__filename,"w") as f:
            for produs in lista_produse:
                produs_line = str(produs.id) + ',' + produs.denumire + ',' + str(produs.pret) + '\n'
                f.write(produs_line)

    def adaugare_produs(self, id : int, denumire : str, pret : int) -> None:
        """
        Functia adauga un produs in fisier
        :param id: Id-ul produsului pe care il adaugam
        :param denumire: Denumirea produsului pe care il adaugam
        :param pret: Pretul produsului pe care il adaugam
        :return: None
        """
        produs = Produs(id, denumire, pret)
        lista_produse = self.get_all()
        lista_produse.append(produs)
        self.__store_to_file(lista_produse)

    def stergere_produse(self, cifra : int):
        """
        Functia sterge toate produsele din lista ale caror ID-uri contin o cifra data
        :param cifra: Cifra data
        :return: None
        """
        lista_produse = self.get_all()
        lista_valida = [produs for produs in lista_produse if str(cifra) not in str(produs.id)]
        self.__lista_undo.append([produs for produs in lista_produse if str(cifra) in str(produs.id)])
        self.__store_to_file(lista_valida)

    def undo(self):
        """
        Functia reface ultima operatie de stergere
        :return: None
        """
        lista_produse = self.get_all()
        ultima_stergere = self.__lista_undo.pop()
        for produs in ultima_stergere:
            lista_produse.append(produs)
        self.__store_to_file(lista_produse)

    def filtrare_produse(self) -> None:
        """
        Functia filtreaza produsele dupa filtrul curent
        :return: None
        """
        lista_produse = self.get_all()
        filtru_text, filtru_pret = self.get_filtru()
        if filtru_pret == -1:
            self.__lista_produse_filtrate = [produs for produs in lista_produse if filtru_text in produs.denumire]
        else:
            self.__lista_produse_filtrate = [produs for produs in lista_produse if filtru_text in produs.denumire and produs.pret < filtru_pret]

    def set_filtru_text(self,text : str):
        self.__filtrare[0] = text

    def set_filtru_pret(self,pret : int):
        self.__filtrare[1] = pret

    def get_all(self):
        lista_produse = self.__load_from_file()
        return lista_produse

    def get_lista_undo(self):
        lista_undo = self.__lista_undo
        return lista_undo

    def get_lista_produse_filtrate(self):
        lista_produse_filtrate = self.__lista_produse_filtrate
        return lista_produse_filtrate

    def get_filtru(self) -> tuple[str,int]:
        filtru_text = self.__filtrare[0]
        filtru_pret = self.__filtrare[1]
        return filtru_text,filtru_pret