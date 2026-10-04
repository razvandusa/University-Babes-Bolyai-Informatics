#include "../headers/service.h"
void Service::sortare_titlu() {
    std::vector<Carte>& lista_carti = get_all();
    std::sort(lista_carti.begin(), lista_carti.end(), comparare_criteriu_sortare);
}

std::vector<Carte> Service:: filtrare_gen(const std::string& gen_cautat) {
    std::vector<Carte>& lista_carti = get_all();
    std::vector<Carte> lista_filtrata;
    std::copy_if(lista_carti.begin(), lista_carti.end(),
                 std::back_inserter(lista_filtrata),
                 [&gen_cautat](Carte& c) {
                     return c.get_gen() == gen_cautat;
                 });
    return lista_filtrata;
}