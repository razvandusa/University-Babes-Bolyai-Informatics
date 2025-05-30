import unittest
from datetime import datetime

from Domain.domain import Automobil

class Tests(unittest.TestCase):
    def test_eq(self):
        data = datetime.strptime("20/3/2005","%d/%m/%Y")
        automobil_1 = Automobil(123456789,"Renault",20000,"Fluence",data)
        automobil_2 = Automobil(123456789,"Renault",20000,"Fluence",data)
        self.assertEqual(automobil_1,automobil_2)