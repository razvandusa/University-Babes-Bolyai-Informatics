class Piesa:
    def __init__(self, titlu, regizor, gen, durata):
        self.__titlu = titlu
        self.__regizor = regizor
        self.__gen = gen
        self.__durata = durata

    def __eq__(self, other):
        if not isinstance(other, Piesa):
            return False
        return self.__titlu == other.__titlu and self.__regizor == other.__regizor and self.__gen == other.__gen and self.__durata == other.__durata

    def __str__(self):
        return self.__titlu + ',' + self.__regizor + ',' + self.__gen + ',' + str(self.durata)

    @property
    def titlu(self):
        return self.__titlu

    @property
    def regizor(self):
        return self.__regizor

    @property
    def gen(self):
        return self.__gen

    @property
    def durata(self):
        return self.__durata

    @titlu.setter
    def titlu(self, value: str):
        self.__titlu = value

    @regizor.setter
    def regizor(self, value: str):
        self.__regizor = value

    @gen.setter
    def gen(self, value: str):
        self.__gen = value

    @durata.setter
    def durata(self, value: int):
        self.__durata = value