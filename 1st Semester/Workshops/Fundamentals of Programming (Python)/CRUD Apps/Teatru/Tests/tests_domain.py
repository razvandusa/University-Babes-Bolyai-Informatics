import unittest
from Domain.piesa import Piesa


class Tests(unittest.TestCase):
    def test_eq(self):
        piesa1 = Piesa("Harap Alb", "Ion Creanga", "Altele", 3)
        piesa2 = Piesa("Harap Alb", "Ion Creanga", "Altele", 3)
        self.assertEqual(piesa1,piesa2)