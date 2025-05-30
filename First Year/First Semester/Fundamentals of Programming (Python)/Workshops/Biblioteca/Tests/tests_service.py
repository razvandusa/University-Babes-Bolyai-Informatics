import unittest

from Domain.carte import Carte
from Repository.repository import Repository
from Service.service import Service
from Utils.file_utils import clear_file

file_path = "/Users/razvandusa/PycharmProjects/Biblioteca/Tests/tests_fisier"
class Tests(unittest.TestCase):
    def setUp(self):
        clear_file(file_path)
        self.repository = Repository(file_path)
        self.service = Service(self.repository)

    def test_aduaga_carte(self):
        try:
            self.service.adauga_carte(123456789,"La țigănci","Mircea Eliade",1959)
            assert True
        except ValueError:
            assert False

        try:
            self.service.adauga_carte("doua milioane", "La țigănci", "Mircea Eliade", 1959)
            assert False
        except ValueError:
            assert True

        try:
            self.service.adauga_carte(123456789, "La țigănci", "Mircea Eliade", "o mie noua sute")
            assert False
        except ValueError:
            assert True

    def test_sterge_carti(self):
        self.service.adauga_carte(123456789, "La țigănci", "Mircea Eliade", 1959)
        try:
            self.service.sterge_carte(100)
            assert False
        except ValueError:
            assert True

        try:
            self.service.sterge_carte("cinci")
            assert False
        except ValueError:
            assert True

        try:
            self.service.sterge_carte(9)
            self.assertEqual(len(self.repository.get_all()),0)
            assert True
        except ValueError:
            assert False

    def test_modificare_filtru_carti(self):
        self.service.adauga_carte(123456789, "La țigănci", "Mircea Eliade", 1959)
        try:
            self.service.modificare_filtru("La",20)
            self.assertEqual(self.repository.get_lista_carti_filtrate(), (["La", 20], [Carte(123456789, "La țigănci", "Mircea Eliade", 1959)]))
            assert True
        except ValueError:
            assert False

    def test_undo(self):
        try:
            self.service.undo()
            assert False
        except ValueError:
            assert True

        self.service.adauga_carte(123456789, "La țigănci", "Mircea Eliade", 1959)
        self.service.sterge_carte(9)
        self.service.undo()
        self.assertEqual(self.repository.get_all(),[Carte(123456789, "La țigănci", "Mircea Eliade", 1959)])
