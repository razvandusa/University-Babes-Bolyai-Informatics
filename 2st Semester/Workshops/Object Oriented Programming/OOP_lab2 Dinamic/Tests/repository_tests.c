#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../Repository/repository.h"
#include "../Service/service.h"

void test_adaugare_oferta()
{
    date_oferta *oferta_I = constructor_oferta("munte","Romania","10/09/2020",500);
    date_oferta *oferta_II = constructor_oferta("mare","Italia","11/05/2023",1200);
    lista_de_oferte *lista = constructor_lista(2);
    adaugare_oferta(lista,oferta_I);
    adaugare_oferta(lista,oferta_II);
    assert(oferte_egale(oferta_I,&lista->oferte[0]) == 1);
    assert(oferte_egale(oferta_II,&lista->oferte[1]) == 1);
    assert(lista->len == 2);

    destructor_oferta(oferta_I);
    destructor_oferta(oferta_II);
    destructor_lista(lista);
}

void test_actualizeaza_oferta()
{
    date_oferta *oferta = constructor_oferta("munte","Romania","10/09/2020",500);
    lista_de_oferte *lista = constructor_lista(2);
    adaugare_oferta(lista,oferta);
    date_oferta *oferta_actualizata = constructor_oferta("mare","Italia","11/05/2023",1200);
    actualizeaza_oferta(lista,oferta,oferta_actualizata);
    assert(oferte_egale(&lista->oferte[0],oferta_actualizata) == 1);

    destructor_oferta(oferta_actualizata);
    destructor_lista(lista);
}

void test_sterge_oferta()
{
    date_oferta *oferta_I = constructor_oferta("munte","Romania","10/09/2020",500);
    date_oferta *oferta_II = constructor_oferta("mare","Italia","11/05/2023",1200);
    date_oferta *oferta_III = constructor_oferta("mare","Norvegia","11/04/2022",1900);
    lista_de_oferte *lista = constructor_lista(2);
    adaugare_oferta_service(lista,oferta_I->tip,oferta_I->destinatie,oferta_I->data_plecare,oferta_I->pret);
    adaugare_oferta_service(lista,oferta_II->tip,oferta_II->destinatie,oferta_II->data_plecare,oferta_II->pret);
    adaugare_oferta_service(lista,oferta_III->tip,oferta_III->destinatie,oferta_III->data_plecare,oferta_III->pret);
    sterge_oferta_service(lista,oferta_II);
    assert(lista->len == 2);
    assert(oferte_egale(&lista->oferte[0],oferta_I));
    assert(oferte_egale(&lista->oferte[1],oferta_III));

    destructor_oferta(oferta_I);
    destructor_oferta(oferta_II);
    destructor_oferta(oferta_III);
    destructor_lista(lista);
}

void test_swap_oferte()
{
    date_oferta *oferta_I = constructor_oferta("munte","Romania","10/09/2020",500);
    date_oferta *oferta_II = constructor_oferta("mare","Italia","11/05/2023",1200);
    lista_de_oferte *lista = constructor_lista(2);
    adaugare_oferta(lista,oferta_I);
    adaugare_oferta(lista,oferta_II);
    swap_oferte(lista,0,1);
    assert(oferte_egale(&lista->oferte[0],oferta_II) == 1);
    assert(oferte_egale(&lista->oferte[1],oferta_I) == 1);

    destructor_oferta(oferta_I);
    destructor_oferta(oferta_II);
    destructor_lista(lista);
}

void test_exista_oferta()
{
    date_oferta *oferta_I = constructor_oferta("munte","Romania","10/09/2020",500);
    date_oferta *oferta_II = constructor_oferta("mare","Italia","11/05/2023",1200);
    lista_de_oferte *lista = constructor_lista(2);
    adaugare_oferta(lista,oferta_I);
    assert(exista_oferta(lista,oferta_I) == 0);
    assert(exista_oferta(lista,oferta_II) == -1);

    destructor_oferta(oferta_I);
    destructor_oferta(oferta_II);
    destructor_lista(lista);
}