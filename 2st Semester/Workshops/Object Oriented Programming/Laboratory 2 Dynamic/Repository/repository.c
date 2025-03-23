#include "repository.h"
#include "../Domain/domain.h"
#include <stdlib.h>
#include <string.h>

void adaugare_oferta(lista_de_oferte *lista, date_oferta *oferta) {
    if (lista->len >= lista->cp) {
        //Realocam memorie dubla
        date_oferta *oferte_noi = (date_oferta *) calloc(2 * lista->cp, sizeof(date_oferta));
        for (int i = 0; i < lista->len; i++) {
            // Alocam memorie pentru campurile de tip string
            oferte_noi[i].tip = (char *) malloc(strlen(lista->oferte[i].tip) + 1);
            oferte_noi[i].destinatie = (char *) malloc(strlen(lista->oferte[i].destinatie) + 1);
            oferte_noi[i].data_plecare = (char *) malloc(strlen(lista->oferte[i].data_plecare) + 1);

            // Copiem continutul din lista in oferte_noi
            strcpy(oferte_noi[i].tip, lista->oferte[i].tip);
            strcpy(oferte_noi[i].destinatie, lista->oferte[i].destinatie);
            strcpy(oferte_noi[i].data_plecare, lista->oferte[i].data_plecare);
            oferte_noi[i].pret = lista->oferte[i].pret;

            //Eliberam memoria veche
            free(lista->oferte[i].tip);
            free(lista->oferte[i].destinatie);
            free(lista->oferte[i].data_plecare);
        }
        free(lista->oferte); //Am eliberat memoria alocata pentru ofertele din lista
        lista->oferte = oferte_noi; //Ofertele din lista o sa aiba acelasi pointer ca oferte_noi
        lista->cp *= 2; //Actualizam capacitatea
    }
    // Alocare si copiere date pentru oferta pe care dorim sa o adaugam in lista
    lista->oferte[lista->len].tip = (char *) malloc(strlen(oferta->tip) + 1);
    lista->oferte[lista->len].destinatie = (char *) malloc(strlen(oferta->destinatie) + 1);
    lista->oferte[lista->len].data_plecare = (char *) malloc(strlen(oferta->data_plecare) + 1);

    strcpy(lista->oferte[lista->len].tip, oferta->tip);
    strcpy(lista->oferte[lista->len].destinatie, oferta->destinatie);
    strcpy(lista->oferte[lista->len].data_plecare, oferta->data_plecare);
    lista->oferte[lista->len].pret = oferta->pret;

    lista->len = lista->len + 1;
}

void actualizeaza_oferta(lista_de_oferte *lista, date_oferta *oferta, date_oferta *oferta_actualizata) {
    for (int i = 0; i <= lista->len; i++) {
        if (oferte_egale(&lista->oferte[i], oferta)) { //Aici am gasit oferta pe care dorim sa o actualizam
            //Se reactualizeaza datele 
            strcpy(lista->oferte[i].tip, oferta_actualizata->tip);
            strcpy(lista->oferte[i].destinatie, oferta_actualizata->destinatie);
            strcpy(lista->oferte[i].data_plecare, oferta_actualizata->data_plecare);
            lista->oferte[i].pret = oferta_actualizata->pret;
            destructor_oferta(oferta); //Se distruge oferta pe care am dat-o ca si parametru pentru ca nu mai avem nevoie de ea
            break;
        }
    }
}

void sterge_oferta(lista_de_oferte *lista, date_oferta *oferta) {
    //Cautam oferta pe care o stergem in lista
    for (int i = 0; i < lista->len; i++) {
        if (oferte_egale(&lista->oferte[i], oferta)) { //Cand am gasit oferta pe care vrem sa o stergem ii dam swap pana pe ultima pozitie
            for (int j = i; j < lista->len - 1; j++) {
                swap_oferte(lista, j, j + 1);
            }
            lista->len -= 1; //Scadem lungimea cu 1 pentru ca am sters o oferta
            break;
        }
    }
}

void swap_oferte(lista_de_oferte *lista, int first_ind, int second_ind) {
    //Copiem in aux datele primei oferte deoarece o sa fie modificata mai tarziu
    date_oferta *aux = constructor_oferta(lista->oferte[first_ind].tip, lista->oferte[first_ind].destinatie,
                                          lista->oferte[first_ind].data_plecare, lista->oferte[first_ind].pret);

    //Eliberam memoria ocupata de prima oferta deoarece este posibil ca memoria ocupata de a doua oferta sa fie diferita
    //si atunci trebuie sa reinitializam memoria primei oferte sa coincida cu a doua oferta. Dupa o sa copiem datele
    free(lista->oferte[first_ind].tip);
    lista->oferte[first_ind].tip = malloc(strlen(lista->oferte[second_ind].tip) + 1);
    strcpy(lista->oferte[first_ind].tip, lista->oferte[second_ind].tip);

    free(lista->oferte[first_ind].destinatie);
    lista->oferte[first_ind].destinatie = malloc(strlen(lista->oferte[second_ind].destinatie) + 1);
    strcpy(lista->oferte[first_ind].destinatie, lista->oferte[second_ind].destinatie);

    free(lista->oferte[first_ind].data_plecare);
    lista->oferte[first_ind].data_plecare = malloc(strlen(lista->oferte[second_ind].data_plecare) + 1);
    strcpy(lista->oferte[first_ind].data_plecare, lista->oferte[second_ind].data_plecare);

    lista->oferte[first_ind].pret = lista->oferte[second_ind].pret;
    //Eliberam memoria ocupata de a doua oferta deoarece este posibil ca memoria ocupata de prima oferta sa fie diferita
    //si atunci trebuie sa reinitializam memoria celei de a doua oferta sa coincida cu prima. Dupa o sa copiem datele
    free(lista->oferte[second_ind].tip);
    lista->oferte[second_ind].tip = malloc(strlen(aux->tip) + 1);
    strcpy(lista->oferte[second_ind].tip, aux->tip);

    free(lista->oferte[second_ind].destinatie);
    lista->oferte[second_ind].destinatie = malloc(strlen(aux->destinatie) + 1);
    strcpy(lista->oferte[second_ind].destinatie, aux->destinatie);

    free(lista->oferte[second_ind].data_plecare);
    lista->oferte[second_ind].data_plecare = malloc(strlen(aux->data_plecare) + 1);
    strcpy(lista->oferte[second_ind].data_plecare, aux->data_plecare);

    lista->oferte[second_ind].pret = aux->pret;

    destructor_oferta(aux); //Distrugem aux pentru ca nu mai avem nevoie de el
}

int exista_oferta(lista_de_oferte *lista, date_oferta *oferta) {
    for (int i = 0; i < lista->len; i++) {
        if (oferte_egale(&lista->oferte[i], oferta)) {
            return i; //Returnam indicele ofertei daca o gasim
        }
    }
    return -1;
}
