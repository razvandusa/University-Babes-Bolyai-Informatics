import unittest
from Domain.emisiune import Emisiune


class TestsDomain(unittest.TestCase):
    def setUp(self):
        self.__emisiune = Emisiune("Jurnal", "Stiri","Informatii", 10)

    def test_property(self):
        self.assertEqual(self.__emisiune.nume, "Jurnal")
        self.assertEqual(self.__emisiune.tip, "Stiri")
        self.assertEqual(self.__emisiune.durata, 10)
        self.assertEqual(self.__emisiune.descriere, "Informatii")

    def test_setter(self):
        self.__emisiune.nume = "Reportaj"
        self.assertEqual(self.__emisiune.nume, "Reportaj")
        self.__emisiune.tip = "Informare"
        self.assertEqual(self.__emisiune.tip, "Informare")
        self.__emisiune.durata = 11
        self.assertEqual(self.__emisiune.durata, 11)
        self.__emisiune.descriere = "Viata la sat"
        self.assertEqual(self.__emisiune.descriere, "Viata la sat")
