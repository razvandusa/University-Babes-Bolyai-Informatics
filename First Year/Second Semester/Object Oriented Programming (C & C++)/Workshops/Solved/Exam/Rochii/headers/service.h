#pragma once
#include "repository.h"

class Service {
private:
    Repository &repository;

public:
    Service(Repository &repository) : repository(repository) {}

    void load_from_file() {
        repository.load_from_file();
    }

    void write_to_file() {
        repository.write_to_file();
    }

    static int convert_marime(Rochie &rochie);

    static bool compara_marimi(Rochie &a, Rochie &b);

    void sortare_marime();

    void sortare_pret();

    void inchiriaza(int cod);

    std::vector<Rochie>& get_all() const {
        return repository.get_all();
    }
};
