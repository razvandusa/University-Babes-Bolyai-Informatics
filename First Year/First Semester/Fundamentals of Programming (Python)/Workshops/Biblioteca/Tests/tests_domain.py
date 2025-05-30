import unittest

from Domain.carte import Carte


class Tests(unittest.TestCase):
    def test_eq(self):
        carte_I = Carte(123456789,"La țigănci","Mircea Eliade",1959)
        carte_II = Carte(123456789, "La țigănci", "Mircea Eliade", 1959)
        self.assertEqual(carte_I,carte_II)