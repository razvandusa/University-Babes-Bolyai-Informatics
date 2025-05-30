import unittest

from Repository.repository import Repository
from Service.service import Service

filename = "/Users/razvandusa/PycharmProjects/Magazin/Teste/teste_fisier.txt"
class Tests(unittest.TestCase):
    def setUp(self):
        with open(filename, "w"):
            pass
        self.__repository = Repository(filename)
        self.__service = Service(self.__repository)

    def test_adaugare_produs(self):
        try:
            self.__service.adaugare_produs("Bomboclat","lapte",30)
            self.assertTrue(False)
        except ValueError:
            self.assertTrue(True)

        try:
            self.__service.adaugare_produs(123, "paine", 5)
            self.assertTrue(True)
        except ValueError:
            self.assertTrue(False)

        try:
            self.__service.adaugare_produs(14, "birou", 0)
            self.assertTrue(False)
        except ValueError:
            self.assertTrue(True)

    def test_stergere_produs(self):
        try:
            self.__service.stergere_produs("g")
            self.assertTrue(False)
        except ValueError:
            self.assertTrue(True)

        try:
            self.__service.stergere_produs(4)
            self.assertTrue(True)
        except ValueError:
            self.assertTrue(False)

    def test_undo(self):
        try:
            self.__service.undo()
            self.assertTrue(False)
        except ValueError:
            self.assertTrue(True)

        self.__service.adaugare_produs(142, "branza", 50)
        self.__service.stergere_produs(1)
        try:
            self.__service.undo()
            self.assertTrue(True)
        except ValueError:
            self.assertTrue(False)

    def test_modificare_filtru(self):
        try:
            self.__service.modificare_filtru("gfb","das")
            self.assertTrue(False)
        except ValueError:
            self.assertTrue(True)

        try:
            self.__service.modificare_filtru("abc",6)
            self.assertTrue(True)
        except ValueError:
            self.assertTrue(False)