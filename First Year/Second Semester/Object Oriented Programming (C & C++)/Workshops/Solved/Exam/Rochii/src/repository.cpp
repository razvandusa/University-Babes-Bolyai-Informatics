#include "../headers/repository.h"
void Repository::load_from_file() {
    std::ifstream fin(filename);
    lista_rochii.clear();
    std::string line;
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string cod_str, denumire, marime, pret_str, disponibilitate;

        std::getline(ss, cod_str, ',');
        std::getline(ss, denumire, ',');
        std::getline(ss, marime, ',');
        std::getline(ss, pret_str, ',');
        std::getline(ss, disponibilitate, ',');

        int id = std::stoi(cod_str);
        int pret = std::stoi(pret_str);

        Rochie r(id, denumire, marime, pret, disponibilitate);
        lista_rochii.push_back(r);
    }
}

void Repository::write_to_file() {
    std::ofstream fout(filename);
    for (Rochie& r : lista_rochii) {
        fout << r.get_cod() << "," << r.get_denumire() << "," << r.get_marime() << "," << r.get_pret() << "," << r.get_disponibilitate() << std::endl;
    }
}