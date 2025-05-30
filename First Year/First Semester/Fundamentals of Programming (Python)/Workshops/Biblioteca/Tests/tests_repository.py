import unittest

from Domain.carte import Carte
from Repository.repository import Repository
from Utils.file_utils import clear_file

file_path = "/Users/razvandusa/PycharmProjects/Biblioteca/Tests/tests_fisier"
class Tests(unittest.TestCase):
    def setUp(self):
        clear_file(file_path)
        self.repository = Repository(file_path)

    def test_add_carte(self):
        carte = Carte(123456789,"La țigănci","Mircea Eliade",1959)
        self.repository.add_carte(carte)
        self.assertEqual(self.repository.get_all(),[carte])

    def test_sterge_carti(self):
        carte = Carte(123456789, "La țigănci", "Mircea Eliade", 1959)
        self.repository.add_carte(carte)
        self.repository.add_carte(carte)
        self.repository.sterge_carti(9)
        self.assertEqual(len(self.repository.get_all()),0)

        carte = Carte(123456789, "La țigănci", "Mircea Eliade", 1959)
        self.repository.add_carte(carte)
        self.repository.sterge_carti(2)
        self.assertEqual(len(self.repository.get_all()), 1)

    def test_modifica_filtru(self):
        carte_I = Carte(123456789, "La țigănci", "Mircea Eliade", 1959)
        carte_II = Carte(123456788, "La Balamuc", "Ioan Slavici", 1032)
        self.repository.add_carte(carte_I)
        self.repository.add_carte(carte_II)
        self.repository.modificare_filtru("La",20)
        self.assertEqual(self.repository.get_lista_carti_filtrate(), (["La", 20], [carte_I, carte_II]))

    def test_undo(self):
        carte = Carte(123456789, "La țigănci", "Mircea Eliade", 1959)
        self.repository.add_carte(carte)
        self.repository.sterge_carti(9)
        self.repository.undo()
        self.assertEqual(self.repository.get_all(), [carte])