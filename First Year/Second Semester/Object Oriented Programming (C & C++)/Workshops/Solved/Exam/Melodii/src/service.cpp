#include "../headers/service.h"
void Service::delete_melodie(const int id) {
    std::string artist;
    for (auto& melodie : repository.get_melodii()) {
        if (melodie.get_id() == id) {
            artist = melodie.get_artist();
            break;
        }
    }

    int count = repository.count_artist(artist);
    if (count != 1) {
        repository.delete_melodie(id);
    } else {
        throw std::invalid_argument("Nu se poate sterge ultima melodie a unui artist!");
    }

}