import unittest

from Repository.repository import Repository
from Service.service import Service

file_path = "/Users/razvandusa/PycharmProjects/Automobile/Tests/tests_fisier.txt"
class Tests(unittest.TestCase):
    def setUp(self):
        self.repository = Repository(file_path)
        self.service = Service(self.repository)

    def test_add_automobil(self):
        try:
            self.service.add_automobil("123456789", "Renault", "20000", "Fluence", "20/3/2005")
            self.assertTrue(True)
        except ValueError:
            self.assertTrue(False)

        try:
            self.service.add_automobil("abc", "Renault", "20000", "Fluence", "20/3/2005")
            self.assertTrue(False)
        except ValueError:
            self.assertTrue(True)

        try:
            self.service.add_automobil("123456789", "Renault", "abc", "Fluence", "20/3/2005")
            self.assertTrue(False)
        except ValueError:
            self.assertTrue(True)

        try:
            self.service.add_automobil("123456789", "Renault", "20000", "Fluence", "2005/3/20")
            self.assertTrue(False)
        except ValueError:
            self.assertTrue(True)

    def test_delete_automobile(self):
        try:
            self.service.delete_automobile("3")
            self.assertTrue(True)
        except ValueError:
            self.assertTrue(False)

        try:
            self.service.delete_automobile("200")
            self.assertTrue(False)
        except ValueError:
            self.assertTrue(True)

        try:
            self.service.delete_automobile("abc")
            self.assertTrue(False)
        except ValueError:
            self.assertTrue(True)

    def test_modificare_filtru(self):
        try:
            self.service.modificare_filtru("Renault","10000")
            self.assertTrue(True)
        except ValueError:
            self.assertTrue(False)

        try:
            self.service.modificare_filtru("Renault", "abc")
            self.assertTrue(False)
        except ValueError:
            self.assertTrue(True)

    def test_undo(self):
        try:
            self.service.undo()
            self.assertTrue(False)
        except ValueError:
            self.assertTrue(True)