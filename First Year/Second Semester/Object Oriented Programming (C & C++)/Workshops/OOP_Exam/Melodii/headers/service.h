#pragma once
#include <utility>

#include "repository.h"

class Service {
public:
    Service(Repository& repository) : repository(repository) {}

    void write_to_file() { repository.write_to_file(); }

    void load_from_file() { repository.load_from_file(); }

    int count_rank(const int rank) {
        return repository.count_rank(rank);
    }

    void update_melodie(int id, const std::string& titlu, int rank) {
        repository.update_melodie(id, titlu, rank);
    }

    void delete_melodie(int id);

    std::vector<Melodie>& get_melodii() { return repository.get_melodii(); }

private:
    Repository& repository;
};
