#include <assert.h>

#include "../Repository/repository.h"

void test_oferta_valida()
{
    //Test date valide
    assert(oferta_valida("munte","Romania","10/09/2020",500) == 1);

    //Teste date vide
    assert(oferta_valida("","Romania","10/09/2020",500) == 0);
    assert(oferta_valida("munte","","10/09/2020",500) == 0);
    assert(oferta_valida("munte","Romania","",500) == 0);

    //Test pret negativ
    assert(oferta_valida("munte","Romania","10/09/2020",-500) == 0);

    //Teste date invalide
    assert(oferta_valida("altceva","Romania","10/09/2020",500) == 0);
    assert(oferta_valida("munte","Romania","40/01/2000",4000) == 0);
    assert(oferta_valida("munte","Romania","20/15/2000",4000) == 0);
    assert(oferta_valida("munte","Romania","10092020",500) == 0);
}

void test_oferte_egale()
{
    //Test tipuri egale
    date_oferta *oferta_1 = constructor_oferta("munte","Romania","10/09/2020",500);
    date_oferta *oferta_2 = constructor_oferta("munte","Romania","10/09/2020",500);
    date_oferta *oferta_3 = constructor_oferta("mare","Romania","10/09/2020",500);
    assert(oferte_egale(oferta_1,oferta_2) == 1);
    assert(oferte_egale(oferta_1,oferta_3) == 0);
    destructor_oferta(oferta_1);
    destructor_oferta(oferta_2);
    destructor_oferta(oferta_3);

    //Test destinatii egale
    oferta_1 = constructor_oferta("munte","Romania","10/09/2020",500);
    oferta_2 = constructor_oferta("munte","Romania","10/09/2020",500);
    oferta_3 = constructor_oferta("munte","Italia","10/09/2020",500);
    assert(oferte_egale(oferta_1,oferta_2) == 1);
    assert(oferte_egale(oferta_1,oferta_3) == 0);
    destructor_oferta(oferta_1);
    destructor_oferta(oferta_2);
    destructor_oferta(oferta_3);

    //Test dati de plecare egale
    oferta_1 = constructor_oferta("munte","Romania","10/09/2020",500);
    oferta_2 = constructor_oferta("munte","Romania","10/09/2020",500);
    oferta_3 = constructor_oferta("munte","Romania","10/10/2020",500);
    assert(oferte_egale(oferta_1,oferta_2) == 1);
    assert(oferte_egale(oferta_1,oferta_3) == 0);
    destructor_oferta(oferta_1);
    destructor_oferta(oferta_2);
    destructor_oferta(oferta_3);

    //Test preturi egale
    oferta_1 = constructor_oferta("munte","Romania","10/09/2020",500);
    oferta_2 = constructor_oferta("munte","Romania","10/09/2020",500);
    oferta_3 = constructor_oferta("munte","Romania","10/09/2020",5100);
    assert(oferte_egale(oferta_1,oferta_2) == 1);
    assert(oferte_egale(oferta_1,oferta_3) == 0);

    destructor_oferta(oferta_1);
    destructor_oferta(oferta_2);
    destructor_oferta(oferta_3);
}