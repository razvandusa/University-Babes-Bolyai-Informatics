import unittest

from black import assert_equivalent

from Domain.emisiune import Emisiune
from Repository.repository import Repository
from Utils.file_utils import clear_file


class TestsRepo(unittest.TestCase):
    def setUp(self):
        self.__filename = "/Users/razvandusa/PycharmProjects/Emisiuni/Tests/tests.txt"
        self.__emisiuni = [
            Emisiune("Jurnal", "Stiri", "Informatii", 2),
            Emisiune("Reportaj", "Informare", "Viata la sat", 3),
            Emisiune("Divertisment", "Film", "5 Sense", 4),
        ]
        self.__repository = Repository(self.__filename)
        clear_file(self.__filename)
        self.__repository.store_to_file(self.__emisiuni)

    def test_delete_emisiune(self):
        try:
            self.__repository.delete_emisiune("Jurnal", "Stiri")
            assert True
        except ValueError:
            assert False

        self.assertEqual(
            self.__repository.get_all(),
            [
                Emisiune("Reportaj", "Informare", "Viata la sat", 3),
                Emisiune("Divertisment", "Film", "5 Sense", 4),
            ],
        )

    def test_update_emisiune(self):
        self.__repository.update_emisiune("Reportaj","Informare","Viata la oras",5)
        self.assertEqual(
            self.__repository.get_all(),
            [
                Emisiune("Jurnal", "Stiri", "Informatii", 2),
                Emisiune("Reportaj", "Informare", "Viata la oras", 5),
                Emisiune("Divertisment", "Film", "5 Sense", 4),
            ],
        )

    def test_program_emisiuni(self):
        start_hour = 11
        end_hour = 13
        program = self.__repository.program_emisiuni(start_hour,end_hour)
        self.assertEqual(len(program),1)

        start_hour = 11
        end_hour = 16
        program = self.__repository.program_emisiuni(start_hour, end_hour)
        self.assertLessEqual(len(program), 2)

    def test_add_to_blocked_list(self):
        self.__repository.add_to_blocked_list("Stiri")
        self.assertEqual(self.__repository.get_blocked_list(),[Emisiune("Jurnal", "Stiri", "Informatii", 2)])

    def test_remove_from_blocked_list(self):
        self.__repository.add_to_blocked_list("Stiri")
        self.__repository.remove_from_blocked_list("Stiri")
        self.assertEqual(self.__repository.get_blocked_list(), [])

    def test_exista_emisiune(self):
        self.__repository.add_to_blocked_list("Stiri")
        self.assertTrue(self.__repository.emisiune_blocata("Stiri"))
        self.assertFalse(self.__repository.emisiune_blocata("Film"))

    def tearDown(self):
        clear_file(self.__filename)
        self.__repository.store_to_file(self.__emisiuni)