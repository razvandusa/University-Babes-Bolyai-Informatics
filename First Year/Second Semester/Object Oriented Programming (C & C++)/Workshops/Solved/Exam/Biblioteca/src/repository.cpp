#include "../headers/repository.h"
void Repository::load_from_file() {
    std::ifstream fin(filename);
    lista_carti.clear();
    std::string line;
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string id_string, cod_string, titlu, autor, gen;
        std::getline(ss, id_string, ' ');
        std::getline(ss, cod_string, ' ');
        std::getline(ss, titlu, ' ');
        std::getline(ss, autor, ' ');
        std::getline(ss, gen, ' ');
        int id = std::stoi(id_string);
        int cod = std::stoi(cod_string);
        Carte c(id, cod, titlu, autor, gen);
        lista_carti.push_back(c);
    }
}

void Repository::write_to_file() {
    std::ofstream fout(filename);
    for (auto &c : lista_carti) {
        fout << c.get_id() << " " << c.get_cod() << " " << c.get_titlu() << " " << c.get_autor() << " " << c.get_gen() << '\n';
    }
}