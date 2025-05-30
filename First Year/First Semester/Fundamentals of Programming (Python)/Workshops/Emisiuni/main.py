from Repository.repository import Repository
from Service.service import Service
from UI.console import Console

filename = "/Users/razvandusa/PycharmProjects/Emisiuni/emisiuni.txt"
repository = Repository(filename)
service = Service(repository)
console = Console(service)
console.run()
