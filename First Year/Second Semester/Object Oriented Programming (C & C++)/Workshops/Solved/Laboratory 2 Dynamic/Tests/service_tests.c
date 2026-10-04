#include <assert.h>
#include <stdlib.h>

#include "../Service/service.h"

void test_adaugare_oferta_service()
{
    lista_de_oferte *lista = constructor_lista(2);
    assert (adaugare_oferta_service(lista,"munte","Romania","10/09/2020",500) == 1);
    assert (adaugare_oferta_service(lista,"altceva","Romania","10/09/2020",500) == 0);
    assert (adaugare_oferta_service(lista,"","Romania","10/09/2020",500) == 0);
    assert (adaugare_oferta_service(lista,"munte","","10/09/2020",500) == 0);
    assert (adaugare_oferta_service(lista,"munte","Romania","",500) == 0);
    assert (adaugare_oferta_service(lista,"munte","Romania","10/09/2020",-2000) == 0);

    destructor_lista(lista);
}

void test_actualizare_oferta_service()
{
    lista_de_oferte *lista = constructor_lista(2);
    adaugare_oferta_service(lista,"munte","Romania","10/09/2020",500);
    date_oferta *oferta = constructor_oferta("munte","Romania","10/09/2020",500);
    date_oferta *oferta_actualizata = constructor_oferta("mare","Italia","10/09/2024",900);
    date_oferta *oferta_inexistenta = constructor_oferta("mare","Italia","10/09/2024",900);
    assert (actualizare_oferta_service(lista,oferta_inexistenta,oferta_actualizata) == 0);
    assert (actualizare_oferta_service(lista,oferta,oferta_actualizata) == 1);

    destructor_lista(lista);
    destructor_oferta(oferta_actualizata);
    destructor_oferta(oferta_inexistenta);
}

void test_sterge_oferta_service()
{
    lista_de_oferte *lista = constructor_lista(2);
    adaugare_oferta_service(lista,"munte","Romania","10/09/2020",500);
    date_oferta *oferta_existenta = constructor_oferta("munte","Romania","10/09/2020",500);
    date_oferta *oferta_inexistenta = constructor_oferta("mare","Italia","10/09/2024",900);
    assert(sterge_oferta_service(lista,oferta_inexistenta) == 0);
    assert(lista->len == 1);
    assert(sterge_oferta_service(lista,oferta_existenta) == 1);
    assert(lista->len == 0);

    destructor_lista(lista);
    destructor_oferta(oferta_existenta);
    destructor_oferta(oferta_inexistenta);
}

void test_ordonare_oferte()
{
    lista_de_oferte *lista = constructor_lista(2);
    date_oferta *oferta_I = constructor_oferta("munte","Romania","10/09/2020",800);
    date_oferta *oferta_II = constructor_oferta("munte","Albania","10/09/2020",500);
    date_oferta *oferta_III = constructor_oferta("mare","Italia","10/09/2020",600);
    adaugare_oferta(lista, oferta_I);
    adaugare_oferta(lista, oferta_II);
    adaugare_oferta(lista, oferta_III);

    //Ordonare crescatoare dupa pret
    lista_de_oferte *lista_ordonata = ordonare_oferte_criteriu_ordine(lista,"pret","crescatoare");
    assert(oferte_egale(&lista_ordonata->oferte[0],oferta_II) == 1);
    assert(oferte_egale(&lista_ordonata->oferte[1],oferta_III) == 1);
    assert(oferte_egale(&lista_ordonata->oferte[2],oferta_I) == 1);

    //Ordonare descrescatoare dupa pret
    lista_ordonata = ordonare_oferte_criteriu_ordine(lista,"pret","descrescatoare");
    assert(oferte_egale(&lista_ordonata->oferte[0],oferta_I) == 1);
    assert(oferte_egale(&lista_ordonata->oferte[1],oferta_III) == 1);
    assert(oferte_egale(&lista_ordonata->oferte[2],oferta_II) == 1);

    //Ordonare crescatoare dupa destinatie
    lista_ordonata = ordonare_oferte_criteriu_ordine(lista,"destinatie","crescatoare");
    assert(oferte_egale(&lista_ordonata->oferte[0],oferta_II) == 1);
    assert(oferte_egale(&lista_ordonata->oferte[1],oferta_III) == 1);
    assert(oferte_egale(&lista_ordonata->oferte[2],oferta_I) == 1);

    //Ordonare descrescatoare dupa destinatie
    lista_ordonata = ordonare_oferte_criteriu_ordine(lista,"destinatie","descrescatoare");
    assert(oferte_egale(&lista_ordonata->oferte[0],oferta_I) == 1);
    assert(oferte_egale(&lista_ordonata->oferte[1],oferta_III) == 1);
    assert(oferte_egale(&lista_ordonata->oferte[2],oferta_II) == 1);
    destructor_oferta(oferta_I);
    destructor_oferta(oferta_II);
    destructor_oferta(oferta_III);
    destructor_lista(lista);
}

void test_filtrare_oferte()
{
    lista_de_oferte *lista = constructor_lista(2);
    date_oferta *oferta_I = constructor_oferta("munte","Romania","10/09/2020",7800);
    date_oferta *oferta_II = constructor_oferta("mare","Albania","10/09/2020",7000);
    adaugare_oferta_service(lista,"munte","Romania","10/09/2020",7800);
    adaugare_oferta_service(lista,"mare","Albania","10/09/2020",7000);

    //Testfiltrare dupa destinatie
    lista_de_oferte *lista_filtrata = filtrare_oferte(lista,"destinatie",functie_comparare_destinatii);
    assert(oferte_egale(&lista_filtrata->oferte[0],oferta_II) == 1);
    assert(oferte_egale(&lista_filtrata->oferte[1],oferta_I) == 1);

    destructor_oferta(oferta_I);
    destructor_oferta(oferta_II);
    destructor_lista(lista);

    lista = constructor_lista(2);
    oferta_I = constructor_oferta("munte","Romania","10/09/2020",7800);
    oferta_II = constructor_oferta("mare","Albania","10/09/2020",7000);
    adaugare_oferta_service(lista,"munte","Romania","10/09/2020",7800);
    adaugare_oferta_service(lista,"mare","Albania","10/09/2020",7000);

    //Test filtrare dupa pret
    lista_filtrata = filtrare_oferte(lista,"pret",functie_comparare_destinatii);
    assert(oferte_egale(&lista_filtrata->oferte[0],oferta_II) == 1);
    assert(oferte_egale(&lista_filtrata->oferte[1],oferta_I) == 1);

    destructor_oferta(oferta_I);
    destructor_oferta(oferta_II);
    destructor_lista(lista);

    lista = constructor_lista(2);
    oferta_I = constructor_oferta("munte","Romania","10/09/2020",7800);
    oferta_II = constructor_oferta("mare","Albania","10/09/2020",7000);
    adaugare_oferta_service(lista,"munte","Romania","10/09/2020",7800);
    adaugare_oferta_service(lista,"mare","Albania","10/09/2020",7000);

    //Test filtrare dupa tip
    lista_filtrata = filtrare_oferte(lista,"tip",functie_comparare_destinatii);
    assert(oferte_egale(&lista_filtrata->oferte[0],oferta_II) == 1);
    assert(oferte_egale(&lista_filtrata->oferte[1],oferta_I) == 1);

    destructor_oferta(oferta_I);
    destructor_oferta(oferta_II);
    destructor_lista(lista);

}