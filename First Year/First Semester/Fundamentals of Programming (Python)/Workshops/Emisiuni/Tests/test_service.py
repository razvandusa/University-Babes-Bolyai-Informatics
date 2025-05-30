import unittest

from Domain.emisiune import Emisiune
from Repository.repository import Repository
from Service.service import Service
from Utils.file_utils import clear_file


class TestService(unittest.TestCase):
    def setUp(self):
        self.__emisiuni = [
            Emisiune("Jurnal", "Stiri", "Informatii", 2),
            Emisiune("Reportaj", "Informare", "Viata la sat", 3),
            Emisiune("Divertisment", "Film", "5 Sense", 4),
        ]
        self.__filename = "/Users/razvandusa/PycharmProjects/Emisiuni/Tests/tests.txt"
        self.__repo = Repository(self.__filename)
        self.__service = Service(self.__repo)
        clear_file(self.__filename)
        self.__repo.store_to_file(self.__emisiuni)

    def test_delete_emisiune(self):
        try:
            self.__service.delete_emisiune("Jurnal", "Stiri")
            assert True
        except ValueError:
            assert False

        try:
            self.__service.delete_emisiune("Jurnal", "Stiri")
            assert False
        except ValueError:
            assert True

        try:
            self.__service.delete_emisiune("ProTV", "Stiri")
            assert False
        except ValueError:
            assert True

    def test_update_emisiune(self):
        try:
            self.__service.update_emisiune("Jurnal","Stiri","Informatii",4)
            assert True
        except ValueError:
            assert False

        try:
            self.__service.update_emisiune("ProTV","Stiri","Informatii",10)
            assert False
        except ValueError:
            assert True

    def test_program_emisiuni(self):
        start_hour = 0
        end_hour = 11
        program = self.__service.program_emisiuni(start_hour,end_hour)
        self.assertEqual(len(program),4)
        start_hour = 0
        end_hour = 12
        program = self.__service.program_emisiuni(start_hour, end_hour)
        self.assertEqual(len(program), 4)

    def tearDown(self):
        clear_file(self.__filename)
        self.__repo.store_to_file(self.__emisiuni)