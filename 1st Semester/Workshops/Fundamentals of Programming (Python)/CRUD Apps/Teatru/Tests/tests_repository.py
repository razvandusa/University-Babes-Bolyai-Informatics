import unittest

from Domain.piesa import Piesa
from Repository.repository import Repository
from Utils.file_utils import clear_file
file_path = "/Users/razvandusa/PycharmProjects/Teatru/Tests/tests.txt"
file_path_exported = "/Users/razvandusa/PycharmProjects/Teatru/Tests/exported.txt"

class Tests(unittest.TestCase):
    def setUp(self):
        clear_file(file_path)
        self.repostory = Repository(file_path)

    def test_add_piesa(self):
        piesa = Piesa("Harap Alb", "Ion Creanga", "Altele", 3)
        self.repostory.add_piesa(piesa)
        self.assertEqual(self.repostory.get_all(),[Piesa("Harap Alb", "Ion Creanga", "Altele", 3)])

    def test_modifica_piesa(self):
        piesa_originala = Piesa("Harap Alb", "Ion Creanga", "Altele", 3)
        self.repostory.add_piesa(piesa_originala)
        piesa_modificata = Piesa("Harap Alb", "Ion Creanga","Comedie", 6)
        self.repostory.modificare_piesa(piesa_modificata)
        self.assertEqual(self.repostory.get_all(), [Piesa("Harap Alb", "Ion Creanga", "Comedie", 6)])

    def test_exista_piesa(self):
        piesa = Piesa("Harap Alb", "Ion Creanga", "Altele", 3)
        self.repostory.add_piesa(piesa)
        self.assertTrue(self.repostory.exista_piesa("Harap Alb","Ion Creanga"))

    def test_exporta(self):
        piesa_I = Piesa("Harap Alb", "Ion Creanga", "Altele", 3)
        self.repostory.add_piesa(piesa_I)
        piesa_II = Piesa("Alibaba", "Abdul", "Altele", 5)
        self.repostory.add_piesa(piesa_II)
        self.repostory.exporta(file_path_exported)
        self.assertTrue(self.repostory.get_all(),[piesa_II,piesa_I])