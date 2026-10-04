#include "../Repository/repository.h"
#include <string.h>

int adaugare_oferta_service(lista_de_oferte *lista, char *tip, char *destinatie, char *data_plecare, int pret) {
    if (oferta_valida(tip, destinatie, data_plecare, pret) == 0)
        return 0;

    date_oferta *oferta = constructor_oferta(tip, destinatie, data_plecare, pret);
    adaugare_oferta(lista, oferta);
    destructor_oferta(oferta); //Se face o copiere a ofertei in lista deci o distrugem oferta ca parametru ptc nu mai
    //avem nevoie de ea

    return 1;
}

int actualizare_oferta_service(lista_de_oferte *lista, date_oferta *oferta, date_oferta *oferta_actualizata) {
    if (exista_oferta(lista, oferta) == -1)
        return 0;

    actualizeaza_oferta(lista, oferta, oferta_actualizata);
    return 1;
}

int sterge_oferta_service(lista_de_oferte *lista, date_oferta *oferta) {
    if (exista_oferta(lista, oferta) == -1)
        return 0;

    sterge_oferta(lista, oferta);
    return 1;
}

lista_de_oferte *ordonare_oferte_criteriu_ordine(lista_de_oferte *lista, char *criteriu, char *ordine) {
    lista_de_oferte *lista_ordonata = lista;
    if (strcmp(criteriu, "pret") == 0) {
        if (strcmp(ordine, "crescatoare") == 0) {
            for (int i = 0; i < lista_ordonata->len - 1; i++) {
                for (int j = i + 1; j < lista_ordonata->len; j++) {
                    if (lista_ordonata->oferte[i].pret > lista_ordonata->oferte[j].pret)
                        swap_oferte(lista_ordonata, i, j);
                }
            }
        }

        if (strcmp(ordine, "descrescatoare") == 0) {
            for (int i = 0; i < lista_ordonata->len - 1; i++) {
                for (int j = i + 1; j < lista_ordonata->len; j++) {
                    if (lista_ordonata->oferte[i].pret < lista_ordonata->oferte[j].pret)
                        swap_oferte(lista_ordonata, i, j);
                }
            }
        }
    }

    if (strcmp(criteriu, "destinatie") == 0) {
        if (strcmp(ordine, "crescatoare") == 0) {
            for (int i = 0; i < lista_ordonata->len - 1; i++) {
                for (int j = i + 1; j < lista_ordonata->len; j++) {
                    if (strcmp(lista_ordonata->oferte[i].destinatie, lista_ordonata->oferte[j].destinatie) > 0)
                        swap_oferte(lista_ordonata, i, j);
                }
            }
        }

        if (strcmp(ordine, "descrescatoare") == 0) {
            for (int i = 0; i < lista_ordonata->len - 1; i++) {
                for (int j = i + 1; j < lista_ordonata->len; j++) {
                    if (strcmp(lista_ordonata->oferte[i].destinatie, lista_ordonata->oferte[j].destinatie) < 0)
                        swap_oferte(lista_ordonata, i, j);
                }
            }
        }
    }
    return lista_ordonata;
}

int functie_comparare_destinatii(lista_de_oferte *lista, int i, int j) {
    //filtrare dupa destinatie
    return strcmp(lista->oferte[i].destinatie,lista->oferte[j].destinatie);
}

lista_de_oferte *filtrare_oferte(lista_de_oferte *lista, char *criteriu, int (*functie_comparare)(lista_de_oferte *,int,int)) {
    lista_de_oferte *lista_filtrata = lista;
    if (strcmp(criteriu, "destinatie") == 0) {
        //Filtrare dupa destinatie
        for (int i = 0; i < lista_filtrata->len - 1; i++) {
            for (int j = i + 1; j < lista_filtrata->len; j++) {
                if (functie_comparare_destinatii(lista,i,j) > 0)
                    swap_oferte(lista_filtrata, i, j);
            }
        }
    }
    if (strcmp(criteriu, "tip") == 0) {
        //Filtrare dupa tip
        for (int i = 0; i < lista_filtrata->len - 1; i++) {
            for (int j = i + 1; j < lista_filtrata->len; j++) {
                if (strcmp(lista_filtrata->oferte[i].tip, lista_filtrata->oferte[j].tip) > 0)
                    swap_oferte(lista_filtrata, i, j);
            }
        }
    }
    if (strcmp(criteriu, "pret") == 0) {
        //Filtrare dupa pret
        for (int i = 0; i < lista_filtrata->len - 1; i++) {
            for (int j = i + 1; j < lista_filtrata->len; j++) {
                if (lista_filtrata->oferte[i].pret > lista_filtrata->oferte[j].pret)
                    swap_oferte(lista_filtrata, i, j);
            }
        }
    }
    return lista_filtrata;
}