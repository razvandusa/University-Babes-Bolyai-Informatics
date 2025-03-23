#include "stdio.h"
#include "domain.h"
#include <stdlib.h>
#include "string.h"

date_oferta *constructor_oferta(char *tip, char *destinatie, char *data_plecare, int pret) {
    //Alocam suficienta memorie pentru a retine datele unei oferte
    date_oferta *oferta = (date_oferta *) malloc(sizeof(date_oferta));
    oferta->tip = (char *) malloc((strlen(tip) + 1));
    oferta->destinatie = (char *) malloc((strlen(destinatie) + 1));
    oferta->data_plecare = (char *) malloc((strlen(data_plecare) + 1));

    //Copiem datele date din parametrii functiei in oferta data
    strcpy(oferta->tip, tip);
    strcpy(oferta->destinatie, destinatie);
    strcpy(oferta->data_plecare, data_plecare);
    oferta->pret = pret;
    return oferta;
}

void destructor_oferta(date_oferta *oferta) {
    //Eliberam memoria pentru oferta
    free(oferta->tip);
    free(oferta->destinatie);
    free(oferta->data_plecare);
    free(oferta);
}

int oferta_valida(char *tip, char *destinatie, char *data_plecare, int pret) {
    if (strcmp(tip, "munte") != 0 && strcmp(tip, "mare") != 0 && strcmp(tip, "citybreak") != 0)
        return 0;

    if (strlen(data_plecare) == 0)
        return 0;

    if (data_plecare[2] != '/' || data_plecare[5] != '/')
        return 0;

    if ((data_plecare[0] - '0') * 10 + (data_plecare[1] - '0') > 30)
        return 0;

    if ((data_plecare[3] - '0') * 10 + (data_plecare[4] - '0') > 12)
        return 0;

    if (strlen(destinatie) == 0)
        return 0;

    if (pret < 0)
        return 0;

    return 1;
}

lista_de_oferte *constructor_lista(int cp) {
    //Alocam suficienta memorie pentru lista
    lista_de_oferte *lista = (lista_de_oferte *) malloc(sizeof(lista_de_oferte));
    lista->oferte = (date_oferta *) calloc(cp, sizeof(date_oferta));
    //Initializam datele listei
    lista->cp = cp;
    lista->len = 0;
    return lista;
}

void destructor_lista(lista_de_oferte *lista) {
    //Eliberam memoria fiecarui camp al fiecarei oferte din lista
    for (int i = 0; i < lista->cp; i++) {
        free(lista->oferte[i].tip);
        free(lista->oferte[i].destinatie);
        free(lista->oferte[i].data_plecare);
    }
    free(lista->oferte);
    free(lista);
}

int oferte_egale(date_oferta *oferta_1, date_oferta *oferta_2) {
    if (strcmp(oferta_1->tip, oferta_2->tip) != 0)
        return 0;

    if (strcmp(oferta_1->destinatie, oferta_2->destinatie) != 0)
        return 0;

    if (strcmp(oferta_1->data_plecare, oferta_2->data_plecare) != 0)
        return 0;

    if (oferta_1->pret != oferta_2->pret)
        return 0;

    return 1;
}
