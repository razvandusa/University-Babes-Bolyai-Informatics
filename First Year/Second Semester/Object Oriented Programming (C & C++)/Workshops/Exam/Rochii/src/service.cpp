#include "../headers/service.h"



int Service::convert_marime(Rochie &rochie) {
    if (rochie.get_marime() == "XS") {
        return 0;
    }
    if (rochie.get_marime() == "S") {
        return 1;
    }
    if (rochie.get_marime() == "M") {
        return 2;
    }
    if (rochie.get_marime() == "L") {
        return 3;
    }
    if (rochie.get_marime() == "XL") {
        return 4;
    }
    if (rochie.get_marime() == "XXL") {
        return 5;
    }
}

bool Service::compara_marimi(Rochie &a, Rochie &b) {
    return convert_marime(a) <= convert_marime(b);
}

void Service::inchiriaza(int cod) {
    std::vector<Rochie>& lista_rochii = repository.get_all();
    for (auto& rochie : lista_rochii) {
        if (rochie.get_cod() == cod) {
            if (rochie.get_disponibilitate() == "True") {
                rochie.set_disponibilitate("False");
                repository.write_to_file();
            }
            break;
        }
    }
}

void Service::sortare_marime() {
    std::vector<Rochie>& lista_rochii = repository.get_all();
    std::sort(lista_rochii.begin(), lista_rochii.end(),compara_marimi);
    repository.write_to_file();
}

void Service::sortare_pret() {
    std::vector<Rochie>& lista_rochii = repository.get_all();
    std::sort(lista_rochii.begin(), lista_rochii.end(),[](Rochie &a, Rochie &b) {
       return (a.get_pret() < b.get_pret());
    });
}