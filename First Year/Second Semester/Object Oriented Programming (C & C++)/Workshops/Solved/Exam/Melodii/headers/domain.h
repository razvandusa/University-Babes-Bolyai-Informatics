#pragma once
#include <string>
#include <utility>

class Melodie {
public:
    Melodie(const int id, std::string titlu, std::string artist, const int rank) : id(id), titlu(std::move(titlu)), artist(std::move(artist)), rank(rank) {}

    int get_id() const { return id; }

    std::string get_titlu() const { return titlu; }

    std::string get_artist() const { return artist; }

    int get_rank() const { return rank; }

    void set_titlu(std::string titlu) { this->titlu = std::move(titlu); }

    void set_rank(int rank) { this->rank = rank; }

private:
    int id;
    std::string titlu;
    std::string artist;
    int rank;
};