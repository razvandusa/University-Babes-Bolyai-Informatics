from Repository.repository import Repository
from Service.service import Service
from UI.console import Console

file_path = "/Users/razvandusa/PycharmProjects/Automobile/fisier.txt"
repository = Repository(file_path)
service = Service(repository)
console = Console(service)
console.run()