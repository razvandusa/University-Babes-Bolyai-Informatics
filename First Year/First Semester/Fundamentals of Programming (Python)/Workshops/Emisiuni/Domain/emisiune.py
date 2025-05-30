class Emisiune:
    """
    Clasa Emisiune retine date importante despre un obiect de tip Emisiune
    """

    def __init__(self, nume: str, tip: str, descriere: str, durata: int):
        self.__nume = nume
        self.__tip = tip
        self.__descriere = descriere
        self.__durata = durata

    def __eq__(self, other):
        return (
            self.__nume == other.__nume
            and self.__tip == other.__tip
            and self.__durata == other.__durata
            and self.__descriere == other.__descriere
        )

    def __str__(self):
        return self.__nume + " " + self.__tip + " " + self.__descriere

    @property
    def nume(self):
        return self.__nume

    @property
    def tip(self):
        return self.__tip

    @property
    def durata(self):
        return self.__durata

    @property
    def descriere(self):
        return self.__descriere

    @nume.setter
    def nume(self, value: str):
        self.__nume = value

    @tip.setter
    def tip(self, value: str):
        self.__tip = value

    @durata.setter
    def durata(self, value: int):
        self.__durata = value

    @descriere.setter
    def descriere(self, value: str):
        self.__descriere = value
