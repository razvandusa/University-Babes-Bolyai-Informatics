from Repository.repository import Repository
from Service.service import Service
from UI.console import Console

file_path = "piese.txt"
repository = Repository(file_path)
service = Service(repository)
console = Console(service)
console.run()