#include "teste_service.h"
#include "../repo/repo.h"
#include "../service/service_participanti.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../ui/ui.h"

void test_adauga_participant() {
    Repository repo;
    initializare_lista_participanti(&repo);
    initializare_lista_undo(&repo);


    assert(adauga_participant(&repo, 1, "Nume1", "Prenume1") == 1);
    assert(repo.lista_repo.dimensiune == 1);
    assert(repo.lista_repo.lista_participanti[0].id == 1);
    assert(strcmp(repo.lista_repo.lista_participanti[0].nume, "Nume1") == 0);
    assert(strcmp(repo.lista_repo.lista_participanti[0].prenume, "Prenume1") == 0);

    assert(adauga_participant(&repo, 1, "Nume2", "Prenume2") == 0);
    assert(repo.lista_repo.dimensiune == 1);

    assert(adauga_participant(&repo, 2, "Nume2", "Prenume2") == 1);
    assert(repo.lista_repo.dimensiune == 2);
    assert(repo.lista_repo.lista_participanti[1].id == 2);
    assert(strcmp(repo.lista_repo.lista_participanti[1].nume, "Nume2") == 0);
    elibereaza_lista_participanti(&repo);
    elibereaza_lista_undo(&repo);
}
//
void test_sterge_participant() {
    Repository repo;
    initializare_lista_participanti(&repo);
    initializare_lista_undo(&repo);
    initializare_lista_participanti_stersi(&repo);
    repo.lista_repo.dimensiune = 3;
    repo.lista_repo.lista_participanti[0].id = 1;
    repo.lista_repo.lista_participanti[1].id = 2;
    repo.lista_repo.lista_participanti[2].id = 3;

    assert(sterge_participant(&repo, 2) == 1);
    assert(repo.lista_repo.dimensiune == 2);
    assert(repo.lista_repo.lista_participanti[0].id == 1);
    assert(repo.lista_repo.lista_participanti[1].id == 3);

    assert(sterge_participant(&repo, 4) == 0);
    assert(repo.lista_repo.dimensiune == 2);

    assert(sterge_participant(&repo, 1) == 1);
    assert(repo.lista_repo.dimensiune == 1);
    assert(repo.lista_repo.lista_participanti[0].id == 3);
    elibereaza_lista_participanti(&repo);
    elibereaza_lista_undo(&repo);
    elibereaza_lista_participanti_stersi(&repo);
}
//
void test_rezolvare_problema() {
    Repository repo;
    initializare_lista_participanti(&repo);

    repo.lista_repo.dimensiune = 3;
    repo.lista_repo.lista_participanti[0].id = 1;
    repo.lista_repo.lista_participanti[1].id = 2;
    repo.lista_repo.lista_participanti[2].id = 3;

    repo.lista_repo.lista_participanti[0].scor = 0;
    repo.lista_repo.lista_participanti[0].probleme_rezolvate = 0;
    repo.lista_repo.lista_participanti[1].scor = 0;
    repo.lista_repo.lista_participanti[1].probleme_rezolvate = 0;
    repo.lista_repo.lista_participanti[2].scor = 0;
    repo.lista_repo.lista_participanti[2].probleme_rezolvate = 0;

    assert(rezolvare_problema(&repo, 1, 10) == 1);
    assert(repo.lista_repo.lista_participanti[0].scor == 10);
    assert(repo.lista_repo.lista_participanti[0].probleme_rezolvate == 1);

    assert(rezolvare_problema(&repo, 100, 1) == 0);
    // print_participant(repo.lista_repo.lista_participanti[1]);
    // rezolvare_problema(&repo, 2, 7);
    // print_participant(repo.lista_repo.lista_participanti[1]);

    //print_participant(repo.lista_repo.lista_participanti[1]);
    assert(rezolvare_problema(&repo, 2, 7) == 1);
    assert(repo.lista_repo.lista_participanti[1].scor == 7);
    assert(repo.lista_repo.lista_participanti[1].probleme_rezolvate == 1);

    assert(rezolvare_problema(&repo, 3, 5) == 1);
    assert(repo.lista_repo.lista_participanti[2].scor == 5);
    assert(repo.lista_repo.lista_participanti[2].probleme_rezolvate == 1);
    elibereaza_lista_participanti(&repo);
}

void test_update_nume() {
    Repository repo;
    initializare_lista_participanti(&repo);
    initializare_lista_undo(&repo);

    adauga_participant(&repo, 1, "Nume1", "Prenume1");

    assert(update_nume(&repo, 1, "Nume1_update") == 1);
    assert(strcmp(repo.lista_repo.lista_participanti[0].nume, "Nume1_update") == 0);
    assert(update_nume(&repo, 2, "nu_exista") == 0);
    elibereaza_lista_participanti(&repo);
    for (int i = 0; i < 10; i++) {
        free(repo.lista_repo_undo.lista_undo[i].lista_participanti);
    }
    free(repo.lista_repo_undo.lista_undo);
}

void test_update_prenume() {
    Repository repo;
    initializare_lista_participanti(&repo);
    initializare_lista_undo(&repo);

    adauga_participant(&repo, 1, "Nume1", "Prenume1");

    assert(update_prenume(&repo, 1, "Prenume1_update") == 1);
    assert(strcmp(repo.lista_repo.lista_participanti[0].prenume, "Prenume1_update") == 0);
    assert(update_prenume(&repo, 2, "nu_exista") == 0);
    elibereaza_lista_participanti(&repo);
    for (int i = 0; i < 10; i++) {
        free(repo.lista_repo_undo.lista_undo[i].lista_participanti);
    }
    free(repo.lista_repo_undo.lista_undo);
}

void test_update_probleme_rezolvate() {
    Repository repo;
    initializare_lista_participanti(&repo);
    initializare_lista_undo(&repo);

    adauga_participant(&repo, 1, "Nume1", "Prenume1");

    repo.lista_repo.lista_participanti[0].scor = 0;
    repo.lista_repo.lista_participanti[0].probleme_rezolvate = 0;

    assert(update_probleme_rezolvate(&repo, 1, 5) == 1);
    assert(repo.lista_repo.lista_participanti[0].probleme_rezolvate == 5);
    assert(update_probleme_rezolvate(&repo, 4, 3) == 0);
    elibereaza_lista_participanti(&repo);
    for (int i = 0; i < 10; i++) {
        free(repo.lista_repo_undo.lista_undo[i].lista_participanti);
    }
    free(repo.lista_repo_undo.lista_undo);
}

void test_update_scor() {
    Repository repo;
    initializare_lista_participanti(&repo);
    initializare_lista_undo(&repo);

    adauga_participant(&repo, 1, "Nume1", "Prenume1");

    repo.lista_repo.lista_participanti[0].scor = 0;
    repo.lista_repo.lista_participanti[0].probleme_rezolvate = 0;

    assert(update_scor(&repo, 1, 100) == 1);
    assert(repo.lista_repo.lista_participanti[0].scor == 100);
    assert(update_scor(&repo, 2, 50) == 0);
    elibereaza_lista_participanti(&repo);
    for (int i = 0; i < 10; i++) {
        free(repo.lista_repo_undo.lista_undo[i].lista_participanti);
    }
    free(repo.lista_repo_undo.lista_undo);
}

void test_filtrare() {
    Repository repo;
    Repository repo_gol;
    initializare_lista_participanti(&repo);
    initializare_lista_participanti(&repo_gol);
    Repository repo_filtrat;

    repo_gol.lista_repo.dimensiune = 0;
    repo_filtrat = filtrare(repo_gol, 100);
    assert(repo_filtrat.lista_repo.dimensiune == 0);
    repo.lista_repo.dimensiune = 3;
    repo.lista_repo.lista_participanti[0].id = 1;
    repo.lista_repo.lista_participanti[0].scor = 50;
    repo.lista_repo.lista_participanti[1].id = 2;
    repo.lista_repo.lista_participanti[1].scor = 80;
    repo.lista_repo.lista_participanti[2].id = 3;
    repo.lista_repo.lista_participanti[2].scor = 30;

    elibereaza_lista_participanti(&repo_filtrat);
    repo_filtrat = filtrare(repo, 60);
    //printf("DIMENSIUNE %d", repo_filtrat.lista_repo.dimensiune);
    //print_participant(repo_filtrat.lista_repo.lista_participanti[0]);
    //print_participant(repo_filtrat.lista_repo.lista_participanti[1]);
    assert(repo_filtrat.lista_repo.dimensiune == 1);
    assert(repo_filtrat.lista_repo.lista_participanti[0].id == 2);
    assert(repo_filtrat.lista_repo.lista_participanti[0].scor == 80);

    elibereaza_lista_participanti(&repo_filtrat);
    repo_filtrat = filtrare(repo, 40);
    assert(repo_filtrat.lista_repo.dimensiune == 2);
    assert(repo_filtrat.lista_repo.lista_participanti[0].id == 1);
    assert(repo_filtrat.lista_repo.lista_participanti[1].id == 2);

    elibereaza_lista_participanti(&repo_filtrat);
    repo_filtrat = filtrare(repo, 10);
    assert(repo_filtrat.lista_repo.dimensiune == 3);
    assert(repo_filtrat.lista_repo.lista_participanti[0].id == 1);
    assert(repo_filtrat.lista_repo.lista_participanti[1].id == 2);
    assert(repo_filtrat.lista_repo.lista_participanti[2].id == 3);

    elibereaza_lista_participanti(&repo_filtrat);
     repo_filtrat = filtrare(repo, 100);
    assert(repo_filtrat.lista_repo.dimensiune == 0);

    elibereaza_lista_participanti(&repo);
    elibereaza_lista_participanti(&repo_gol);
    elibereaza_lista_participanti(&repo_filtrat);
}

void test_swtich_participanti() {
    Repository repo;
    initializare_lista_participanti(&repo);
    //p1
    repo.lista_repo.dimensiune = 2;
    repo.lista_repo.lista_participanti[0].id = 1;
    repo.lista_repo.lista_participanti[0].scor = 50;
    repo.lista_repo.lista_participanti[0].probleme_rezolvate = 2;
    strcpy(repo.lista_repo.lista_participanti[0].nume, "Nume1");
    strcpy(repo.lista_repo.lista_participanti[0].prenume, "Prenume1");
    //p2
    repo.lista_repo.lista_participanti[1].id = 2;
    repo.lista_repo.lista_participanti[1].scor = 80;
    repo.lista_repo.lista_participanti[1].probleme_rezolvate = 3;
    strcpy(repo.lista_repo.lista_participanti[1].nume, "Nume2");
    strcpy(repo.lista_repo.lista_participanti[1].prenume, "Prenume2");

    swtich_participanti(&repo.lista_repo.lista_participanti[0], &repo.lista_repo.lista_participanti[1]);

    assert(repo.lista_repo.lista_participanti[0].id == 2);
    assert(repo.lista_repo.lista_participanti[0].scor == 80);
    assert(strcmp(repo.lista_repo.lista_participanti[0].nume, "Nume2") == 0);
    assert(strcmp(repo.lista_repo.lista_participanti[0].prenume, "Prenume2") == 0);

    assert(repo.lista_repo.lista_participanti[1].id == 1);
    assert(repo.lista_repo.lista_participanti[1].scor == 50);
    assert(strcmp(repo.lista_repo.lista_participanti[1].nume, "Nume1") == 0);
    assert(strcmp(repo.lista_repo.lista_participanti[1].prenume, "Prenume1") == 0);
    elibereaza_lista_participanti(&repo);
}

void test_sortare_nume() {
    Repository repo;
    Repository repo_gol;
    initializare_lista_participanti(&repo);
    initializare_lista_participanti(&repo_gol);
    assert(sortare_nume(repo_gol, 1, comparare_nume).lista_repo.dimensiune == 0);
    assert(sortare_nume(repo_gol, 0, comparare_nume).lista_repo.dimensiune == 0);
    repo.lista_repo.dimensiune = 4;

    repo.lista_repo.lista_participanti[0].id = 1;
    repo.lista_repo.lista_participanti[0].scor = 50;
    repo.lista_repo.lista_participanti[0].probleme_rezolvate = 2;
    strcpy(repo.lista_repo.lista_participanti[0].nume, "Nume_a");
    strcpy(repo.lista_repo.lista_participanti[0].prenume, "Prenume_b");

    repo.lista_repo.lista_participanti[1].id = 2;
    repo.lista_repo.lista_participanti[1].scor = 50;
    repo.lista_repo.lista_participanti[1].probleme_rezolvate = 2;
    strcpy(repo.lista_repo.lista_participanti[1].nume, "Nume_a");
    strcpy(repo.lista_repo.lista_participanti[1].prenume, "Prenume_a");

    repo.lista_repo.lista_participanti[2].id = 3;
    repo.lista_repo.lista_participanti[2].scor = 50;
    repo.lista_repo.lista_participanti[2].probleme_rezolvate = 2;
    strcpy(repo.lista_repo.lista_participanti[2].nume, "Nume_c");
    strcpy(repo.lista_repo.lista_participanti[2].prenume, "Prenume_c");

    repo.lista_repo.lista_participanti[3].id = 4;
    repo.lista_repo.lista_participanti[3].scor = 50;
    repo.lista_repo.lista_participanti[3].probleme_rezolvate = 2;
    strcpy(repo.lista_repo.lista_participanti[3].nume, "Nume_b");
    strcpy(repo.lista_repo.lista_participanti[3].prenume, "Prenume_b");



    // crescator
    Repository repo_sortat = sortare_nume(repo, 1, comparare_nume);



    assert(strcmp(repo_sortat.lista_repo.lista_participanti[0].nume, "Nume_a") == 0);
    assert(strcmp(repo_sortat.lista_repo.lista_participanti[1].nume, "Nume_a") == 0);
    assert(strcmp(repo_sortat.lista_repo.lista_participanti[2].nume, "Nume_b") == 0);
    assert(strcmp(repo_sortat.lista_repo.lista_participanti[3].nume, "Nume_c") == 0);


    repo_sortat = sortare_nume(repo, 0, comparare_nume);  // sortare descrescatoare

    // assert(strcmp(repo_sortat.lista_repo.lista_participanti[0].nume, "Nume_c") == 0);
    // assert(strcmp(repo_sortat.lista_repo.lista_participanti[1].nume, "Nume_b") == 0);
    // assert(strcmp(repo_sortat.lista_repo.lista_participanti[2].nume, "Nume_a") == 0);
    // assert(strcmp(repo_sortat.lista_repo.lista_participanti[3].nume, "Nume_a") == 0);

    elibereaza_lista_participanti(&repo);
    elibereaza_lista_participanti(&repo_gol);


}

void test_sortare_scor() {
    Repository repo, repo_gol;
    initializare_lista_participanti(&repo);
    initializare_lista_participanti(&repo_gol);
    repo_gol.lista_repo.dimensiune = 0;
    assert(sortare_scor(repo_gol, 1, comparare_scor).lista_repo.dimensiune == 0);

    repo.lista_repo.dimensiune = 4;
    repo.lista_repo.lista_participanti[0].id = 1;
    repo.lista_repo.lista_participanti[0].scor = 17;
    repo.lista_repo.lista_participanti[0].probleme_rezolvate = 2;
    strcpy(repo.lista_repo.lista_participanti[0].nume, "Nume1");
    strcpy(repo.lista_repo.lista_participanti[0].prenume, "Prenume1");

    repo.lista_repo.lista_participanti[1].id = 2;
    repo.lista_repo.lista_participanti[1].scor = 100;
    repo.lista_repo.lista_participanti[1].probleme_rezolvate = 3;
    strcpy(repo.lista_repo.lista_participanti[1].nume, "Nume2");
    strcpy(repo.lista_repo.lista_participanti[1].prenume, "Prenume2");

    repo.lista_repo.lista_participanti[2].id = 3;
    repo.lista_repo.lista_participanti[2].scor = 18;
    repo.lista_repo.lista_participanti[2].probleme_rezolvate = 1;
    strcpy(repo.lista_repo.lista_participanti[2].nume, "Nume3");
    strcpy(repo.lista_repo.lista_participanti[2].prenume, "Prenume3");

    repo.lista_repo.lista_participanti[3].id = 4;
    repo.lista_repo.lista_participanti[3].scor = 100;
    repo.lista_repo.lista_participanti[3].probleme_rezolvate = 1;
    strcpy(repo.lista_repo.lista_participanti[3].nume, "Nume3");
    strcpy(repo.lista_repo.lista_participanti[3].prenume, "Prenume3");

    repo = sortare_scor(repo, 1, comparare_scor);
    //printf("%d", repo.lista_repo.lista_participanti[0].scor);
    assert(repo.lista_repo.lista_participanti[0].scor == 17);
    assert(repo.lista_repo.lista_participanti[1].scor == 18);
    assert(repo.lista_repo.lista_participanti[2].scor == 100);
    assert(repo.lista_repo.lista_participanti[3].scor == 100);

    repo = sortare_scor(repo, 0, comparare_scor);

    assert(repo.lista_repo.lista_participanti[0].scor == 100);
    assert(repo.lista_repo.lista_participanti[1].scor == 100);
    assert(repo.lista_repo.lista_participanti[2].scor == 18);
    assert(repo.lista_repo.lista_participanti[3].scor == 17);

    elibereaza_lista_participanti(&repo);
    elibereaza_lista_participanti(&repo_gol);

}

void test_comparare_nume() {
    Participant p1, p2, p3;
    strcpy(p1.nume, "Nume1");
    strcpy(p1.prenume, "Prenume1");
    p1.scor = 10;

    strcpy(p2.nume, "Nume1");
    strcpy(p2.prenume, "Prenume1");
    p2.scor = 11;

    strcpy(p3.nume, "Nume3");
    strcpy(p3.prenume, "Prenume3");

    assert(comparare_nume(p1, p2) == -1);
    assert(comparare_nume(p1, p3) < 0);
    assert(comparare_nume(p3, p1) > 0);

}

void test_comparare_scor() {
    Participant p1, p2, p3;
    p1.scor = 10;
    p2.scor = 20;
    p3.scor = 30;
    assert(comparare_scor(p1, p2) == -1);
    assert(comparare_scor(p1, p3) == -1);
    assert(comparare_scor(p3, p1) == 1);
}

void test_undo_service() {
    Repository repo;
    initializare_lista_participanti(&repo);
    initializare_lista_undo(&repo);
    adauga_participant(&repo, 1, "Nume1", "Prenume1");
    assert(undo_service(&repo) == 0);
    adauga_participant(&repo, 2, "Nume2", "Prenume2");
    adauga_participant(&repo, 3, "Nume3", "Prenume3");
    assert(undo_service(&repo) == 1);
    elibereaza_lista_participanti(&repo);
    elibereaza_lista_undo(&repo);
}


void test_all_service() {
    test_adauga_participant();
    test_sterge_participant();
    test_rezolvare_problema();
    test_update_nume();
    test_update_prenume();
    test_update_probleme_rezolvate();
    test_update_scor();
    test_filtrare();
    test_swtich_participanti();
    test_sortare_nume();
    test_sortare_scor();
    test_comparare_nume();
    test_comparare_scor();
    test_undo_service();
    printf("Teste service ok\n");
}





