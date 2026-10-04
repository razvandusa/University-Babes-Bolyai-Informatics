#include "../Tests/tests.h"
#include "../Service/service.h"
#include <stdio.h>
#include <string.h>
#define RED "\033[1;31m"
#define RESET "\033[0m"

void run_tests()
{
    printf("Ruleaza testele : ...\n");
    //Teste Domain
    test_oferta_valida();
    test_oferte_egale();
    //Teste Repository
    test_adaugare_oferta();
    test_actualizeaza_oferta();
    test_exista_oferta();
    test_swap_oferte();
    test_sterge_oferta();
    //Teste Service
    test_adaugare_oferta_service();
    test_actualizare_oferta_service();
    test_sterge_oferta_service();
    test_ordonare_oferte();
    test_filtrare_oferte();
    printf("Testele au trecut cu succes!\n");
}

void meniu()
{
    printf("\nAlege optiunea :\n");
    printf("1. Adaugarea de noi oferte.\n"
           "2. Actualizare oferte\n"
           "3. Stergere oferta\n"
           "4. Vizualizare oferte ordonate dupa pret, destinatie (crescator/descrescator)\n"
           "5. Vizualizare oferta filtrate dupa un criteriu (destinatie, tip, pret)\n"
           "6. Vizualizare oferte\n"
           "7. Exit\n");
}

void print_oferta(date_oferta *oferta)
{
    printf("Tipul : %s\n",oferta->tip);
    printf("Destinatia : %s\n",oferta->destinatie);
    printf("Data plecarii : %s\n",oferta->data_plecare);
    printf("Pretul : %d\n",oferta->pret);
}

void print_lista_de_oferte(lista_de_oferte *lista)
{
    if (lista->len == 0)
    {
        printf("Lista este goala!");
    }
    else
    {
        for (int i = 0; i < lista->len; i++,printf("\n"))
        {
            printf("Oferta cu numarul : %d\n",i+1);
            print_oferta(&lista->oferte[i]);
        }
    }
}

void adaugare_oferta_ui(lista_de_oferte *lista)
{
    char tip[101],destinatie[101],data_plecare[101];
    int pret;
    printf("Scrie tipul ofertei pe care doresti sa o adaugi : (munte/mare/citybreak)\n");
    scanf("%s",tip);
    printf("Scrie destinatia ofertei pe care doresti sa o adaugi :\n");
    scanf("%s",destinatie);
    printf("Scrie data de plecare ofertei pe care doresti sa o adaugi : (day/month/year)\n");
    scanf("%s",data_plecare);
    printf("Scrie pretul ofertei pe care doresti sa o adaugi :\n");
    scanf("%d",&pret);
    int adaugat = adaugare_oferta_service(lista, tip, destinatie ,data_plecare ,pret);
    if (adaugat == 1)
        printf("S-a adaugat oferta cu succes!");
    else
        printf(RED "Datele citite sunt invalide!" RESET);
}

void actualizare_oferta_ui(lista_de_oferte *lista)
{
    char tip[101],destinatie[101],data_plecare[101];
    int pret;
    printf("Scrie tipul ofertei pe care doresti sa o actualizezi : (munte/mare/citybreak)\n");
    scanf("%s",tip);
    printf("Scrie destinatia ofertei pe care doresti sa o actualizezi :\n");
    scanf("%s",destinatie);
    printf("Scrie data de plecare ofertei pe care doresti sa o actualizezi : (day/month/year)\n");
    scanf("%s",data_plecare);
    printf("Scrie pretul ofertei pe care doresti sa o actualizezi :\n");
    scanf("%d",&pret);
    if (oferta_valida(tip,destinatie,data_plecare,pret) == 0)
    {
        printf(RED "Datele citite sunt invalide!" RESET);
        return ;
    }
    date_oferta *oferta = constructor_oferta(tip,destinatie,data_plecare,pret);
    char tip_actualizat[101],destinatie_actualizata[101],data_plecare_actualizata[101];
    int pret_actualizat;
    printf("Scrie noul tip al ofertei : (munte/mare/citybreak)\n");
    scanf("%s",tip_actualizat);
    printf("Scrie noua destinatie a ofertei :\n");
    scanf("%s",destinatie_actualizata);
    printf("Scrie noua data de plecare a ofertei : (day/month/year)\n");
    scanf("%s",data_plecare_actualizata);
    printf("Scrie noul pret al ofertei :\n");
    scanf("%d",&pret_actualizat);
    if (oferta_valida(tip_actualizat,destinatie_actualizata,data_plecare_actualizata,pret_actualizat) == 0)
    {
        printf(RED "Datele citite sunt invalide!" RESET);
        return ;
    }
    date_oferta *oferta_actualizata = constructor_oferta(tip_actualizat,destinatie_actualizata,data_plecare_actualizata,pret_actualizat);
    int actualizat = actualizare_oferta_service(lista,oferta,oferta_actualizata);
    if (actualizat == 1)
        printf("S-a actualizat oferta cu succes!");
    else
        printf(RED "Oferta nu exista in lista!" RESET);
    destructor_oferta(oferta_actualizata);
}

void sterge_oferta_ui(lista_de_oferte *lista)
{
    char tip[101],destinatie[101],data_plecare[101];
    int pret;
    printf("Scrie tipul ofertei pe care doresti sa o stergi :\n");
    scanf("%s",tip);
    printf("Scrie destinatia ofertei pe care doresti sa o stergi :\n");
    scanf("%s",destinatie);
    printf("Scrie data de plecare ofertei pe care doresti sa o stergi :\n");
    scanf("%s",data_plecare);
    printf("Scrie pretul ofertei pe care doresti sa o stergi :\n");
    scanf("%d",&pret);
    if (oferta_valida(tip,destinatie,data_plecare,pret) == 0)
    {
        printf(RED "Datele citite sunt invalide!" RESET);
        return ;
    }
    date_oferta *oferta = constructor_oferta(tip,destinatie,data_plecare,pret);
    int sters = sterge_oferta_service(lista,oferta);
    if (sters == 1)
        printf("Oferta a fost stersa cu succes!");
    else
        printf(RED "Oferta nu exista in lista!" RESET);
    destructor_oferta(oferta);
}

void ordonare_oferte_ui(lista_de_oferte *lista)
{
    char criteriu[101];

    printf("Scrie criteriul dupa care vrei sa sortezi : (pret/destinatie)\n");
    scanf("%s",criteriu);
    if (strcmp(criteriu,"pret") != 0 && strcmp(criteriu,"destinatie") != 0)
        printf(RED "Datele citite sunt invalide!" RESET);
    else
    {
        char ordine[101];
        printf("Scrie ordinea dupa care vrei sa sortezi : (crescatoare/descrescatoare)\n");
        scanf("%s",ordine);
        if (strcmp(ordine,"crescatoare") != 0 && strcmp(ordine,"descrescatoare") != 0)
            printf(RED "Datele citite sunt invalide!" RESET);
        else
        {
            lista_de_oferte *lista_ordonata = ordonare_oferte_criteriu_ordine(lista, criteriu, ordine);
            print_lista_de_oferte(lista_ordonata);
        }
    }
}

void filtrare_oferte_ui(lista_de_oferte *lista)
{
    char criteriu[101];

    printf("Scrie criteriul dupa care vrei sa sortezi : (destinatie / tip / pret)\n");
    scanf("%s",criteriu);
    if (strcmp(criteriu,"destinatie") != 0 && strcmp(criteriu,"tip") != 0 && strcmp(criteriu,"pret") != 0)
        printf(RED "Datele citite sunt invalide!" RESET);
    else
    {
        lista_de_oferte *lista_filtrata = filtrare_oferte(lista, criteriu, functie_comparare_destinatii);
        print_lista_de_oferte(lista_filtrata);
    }
}

void run()
{
    lista_de_oferte *lista = constructor_lista(2);
    int run = 1,optiune;
    while (run)
    {
        meniu();
        if (scanf("%d",&optiune) == 1 && optiune >= 1 && optiune <= 7)
        {
            switch (optiune){
            case 1:
                adaugare_oferta_ui(lista);
                break;
            case 2:
                actualizare_oferta_ui(lista);
                break;
            case 3:
                sterge_oferta_ui(lista);
                break;
            case 4:
                ordonare_oferte_ui(lista);
                break;
            case 5:
                filtrare_oferte_ui(lista);
                break;
            case 6:
                print_lista_de_oferte(lista);
                break;
            case 7:
                run = 0;
                destructor_lista(lista);
                break;
            default:
                printf(RED "Nu exista aceasta optiune!\n"  RESET);
                break;
            }
        }
        else
        {
            printf(RED "Optiunea invalida!\n" RESET);
            while (getchar() != '\n');
        }
    }
}