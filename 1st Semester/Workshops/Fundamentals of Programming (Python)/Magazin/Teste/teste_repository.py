import unittest

from Domain.produs import Produs
from Repository.repository import Repository

filename = "/Users/razvandusa/PycharmProjects/Magazin/Teste/teste_fisier.txt"
class Tests(unittest.TestCase):
    def setUp(self):
        self.repository = Repository(filename)
        with open(filename,"w"):
            pass

    def test_adaugare_produs(self):
        self.repository.adaugare_produs(142, "branza", 50)
        lista_produse = self.repository.get_all()
        self.assertEqual(1, len(lista_produse))

    def test_stergere_produse(self):
        self.repository.adaugare_produs(142, "branza", 50)
        self.repository.adaugare_produs(754, "paine", 5)
        self.repository.stergere_produse(7)
        lista_produse = self.repository.get_all()
        self.assertEqual(lista_produse, [Produs(142, "branza", 50)])

    def test_undo(self):
        self.repository.adaugare_produs(142, "branza", 50)
        self.repository.stergere_produse(4)
        self.repository.undo()
        lista_produse = self.repository.get_all()
        self.assertEqual(1, len(lista_produse))

    def test_filtrare_produse(self):
        self.repository.adaugare_produs(142, "branza", 50)
        self.repository.adaugare_produs(754, "paine", 5)
        self.repository.filtrare_produse()
        lista_produse = self.repository.get_all()
        lista_produse_filtrate = self.repository.get_lista_produse_filtrate()
        self.assertEqual(lista_produse_filtrate, lista_produse)

        self.repository.set_filtru_text("branza")
        self.repository.filtrare_produse()
        lista_produse_filtrate = self.repository.get_lista_produse_filtrate()
        self.assertEqual(lista_produse_filtrate, [Produs(142, "branza", 50)])

        self.repository.set_filtru_text("")
        self.repository.set_filtru_pret(20)
        self.repository.filtrare_produse()
        lista_produse_filtrate = self.repository.get_lista_produse_filtrate()
        self.assertEqual(lista_produse_filtrate, [Produs(754, "paine", 5)])