#pragma once
#include "repository.h"

class Service {
public:
    Service(Repository& repository) : repository(repository) {}

    void load_from_file() { repository.load_from_file(); }

    void write_to_file() { repository.write_to_file(); }

    int numarTractoareAcelasiTip(const std::string& tip) { return repository.numarTractoareAcelasiTip(tip); }

    void add_tractor(const std::string& id, const std::string& denumire, const std::string &tip,const std::string& numarRoti);

    bool exista_id(int id) { return repository.exista_id(id); }

    std::vector<Tractor>& get_all() { return repository.get_all(); }

private:
    Repository& repository;
};
