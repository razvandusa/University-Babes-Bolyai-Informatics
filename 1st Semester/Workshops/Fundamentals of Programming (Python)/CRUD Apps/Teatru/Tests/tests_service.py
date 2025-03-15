import unittest

from Repository.repository import Repository
from Service.service import Service
from Utils.file_utils import clear_file

file_path = "/Users/razvandusa/PycharmProjects/Teatru/Tests/tests.txt"

class Tests(unittest.TestCase):
    def setUp(self):
        clear_file(file_path)
        clear_file("/Users/razvandusa/PycharmProjects/Teatru/Tests/exported.txt")
        self.repository = Repository(file_path)
        self.service = Service(self.repository)

    def test_add_piesa(self):
        titlu, regizor, gen, durata = "Antonio","Gabor","Drama",200
        try:
            self.service.add_piesa(titlu,regizor,gen,durata)
            assert True
        except ValueError:
            assert False

        titlu, regizor, gen, durata = "", "", "Drama", 200
        try:
            self.service.add_piesa(titlu,regizor,gen,durata)
            assert False
        except ValueError:
            assert True

        titlu, regizor, gen, durata = "Antonio", "Gabor", "Drama", -33
        try:
            self.service.add_piesa(titlu, regizor, gen, durata)
            assert False
        except ValueError:
            assert True

    def test_modifica_piesa(self):
        titlu, regizor, gen, durata = "Antonio", "Gabor", "Drama", 200
        self.service.add_piesa(titlu, regizor, gen, durata)
        try:
            self.service.modifica_piesa("Camelia","Orlando","Comedie",30)
            assert False
        except ValueError:
            assert True

        try:
            self.service.modifica_piesa("Antonio","Gabor","Comedie",30)
            assert True
        except ValueError:
            assert False

    def test_generare_titlu_regizor(self):
        titlu = self.service.generare_titlu_regizor()
        self.assertTrue(8 <= len(titlu) <= 12)
        self.assertTrue(' ' in titlu)

    def test_generare_gen(self):
        gen = self.service.generare_gen()
        self.assertTrue(gen in ["Comedie", "Drama", "Satira", "Altele"])

    def test_generare_durata(self):
        durata = self.service.generare_durata()
        self.assertTrue(isinstance(durata,int))

    def test_creeaza_piese(self):
        n = 4
        self.service.creeaza_piese(n)
        self.assertEqual(len(self.repository.get_all()),4)

        n = "test"
        try:
            self.service.creeaza_piese(n)
            assert False
        except ValueError:
            assert True

    def test_exporta(self):
        filename = "/Users/razvandusa/PycharmProjects/Teatru/Tests/exported.txt"
        try:
            self.service.exporta("alibaba.txt")
            assert False
        except ValueError:
            assert True

        try:
            self.service.exporta(filename)
            assert True
        except ValueError:
            assert False