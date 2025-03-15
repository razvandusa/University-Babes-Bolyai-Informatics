import unittest
from datetime import datetime

from Domain.domain import Automobil
from Repository.repository import Repository

file_path = "/Users/razvandusa/PycharmProjects/Automobile/Tests/tests_fisier.txt"
class Tests(unittest.TestCase):
    def setUp(self):
        with open(file_path, "w"):
            pass
        self.repository = Repository(file_path)
        data = datetime.strptime("20/3/2005", "%d/%m/%Y")
        automobil_1 = Automobil(123456789, "Renault", 20000, "Fluence", data)
        automobil_2 = Automobil(123456789, "Renault", 10000, "Fluence", data)
        automobil_3 = Automobil(123456789, "Renault", 10000, "Fluence", data)
        self.repository.add_automobil(automobil_1)
        self.repository.add_automobil(automobil_2)
        self.repository.add_automobil(automobil_3)

    def test_add_automobil(self):
        data = datetime.strptime("20/3/2005", "%d/%m/%Y")
        automobil = Automobil(123456789, "Renault", 20000, "Fluence", data)
        self.repository.add_automobil(automobil)
        self.assertEqual(len(self.repository.get_all()),4)

    def test_delete_automobile(self):
        contor = self.repository.delete_automobile(1)
        self.assertEqual(len(self.repository.get_all()), 1)
        self.assertEqual(contor, 2)

    def test_modificare_filtru(self):
        marca = "Renault"
        pret = 10001
        self.repository.modificare_filtru(marca,pret)
        self.assertEqual(self.repository.get_filtru_marca(),marca)
        self.assertEqual(self.repository.get_filtru_pret(), pret)

    def test_filtrare_automobile(self):
        marca = "Renault"
        pret = 10001
        self.repository.modificare_filtru(marca, pret)
        self.repository.filtrare_automobile()
        self.assertEqual(len(self.repository.get_lista_automobile_filtrate()),2)

    def test_expirat(self):
        self.repository.expirat()
        lista_automobile = self.repository.get_all()
        lista_automobile_expirate = [automobil for automobil in lista_automobile if '*' in automobil.marca]
        self.assertEqual(len(lista_automobile_expirate),3)

    def test_undo(self):
        data = datetime.strptime("20/3/2005", "%d/%m/%Y")
        automobil = Automobil(123456789, "Renault", 20000, "Fluence", data)
        self.repository.add_automobil(automobil)
        self.repository.undo()
        self.assertEqual(len(self.repository.get_all()), 3)
        self.repository.delete_automobile(1)
        self.repository.undo()
        self.assertEqual(len(self.repository.get_all()), 3)