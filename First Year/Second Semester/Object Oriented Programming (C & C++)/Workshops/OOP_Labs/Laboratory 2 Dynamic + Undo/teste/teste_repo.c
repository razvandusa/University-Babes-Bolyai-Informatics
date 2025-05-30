#include "../repo/repo.h"
#include "../model/participant.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
// #include <stdlib.h>

void test_initializare_lista_participanti() {
    Repository repo;
    initializare_lista_participanti(&repo);
    assert(repo.lista_repo.capacitate == 10);
    assert(repo.lista_repo.dimensiune == 0);
    elibereaza_lista_participanti(&repo);
}

void test_initializare_lista_undo() {
    Repository repo;
    initializare_lista_undo(&repo);
    assert(repo.lista_repo_undo.capacitate == 10);
    assert(repo.lista_repo_undo.dimensiune == 0);
    elibereaza_lista_undo(&repo);
}

void test_initializare_lista_stersi() {
    Repository repo;
    initializare_lista_participanti_stersi(&repo);
    assert(repo.lista_repo_stersi.capacitate == 10);
    assert(repo.lista_repo_stersi.dimensiune == 0);
    elibereaza_lista_participanti_stersi(&repo);
}

void test_dealocare() {
    Repository repo;
    initializare_lista_participanti(&repo);
    initializare_lista_undo(&repo);
    repo.lista_repo.dimensiune = 3;
    repo.lista_repo_undo.dimensiune = 1;

    // Verificăm dacă memoria a fost alocată corect
    assert(repo.lista_repo.lista_participanti != NULL);
    assert(repo.lista_repo_undo.lista_undo[0].lista_participanti != NULL);

    // Populăm lista de participanți pentru a verifica mai ușor
    repo.lista_repo.lista_participanti[0].id = 1;
    strcpy(repo.lista_repo.lista_participanti[0].nume, "Nume1");
    strcpy(repo.lista_repo.lista_participanti[0].prenume, "Prenume1");

    repo.lista_repo_undo.lista_undo[0].lista_participanti[0].id = 1;
    strcpy(repo.lista_repo_undo.lista_undo->lista_participanti[0].nume, "Nume1");
    strcpy(repo.lista_repo_undo.lista_undo->lista_participanti[0].prenume, "Prenume1");

    repo.lista_repo.lista_participanti[1].id = 2;
    strcpy(repo.lista_repo.lista_participanti[1].nume, "Nume2");
    strcpy(repo.lista_repo.lista_participanti[1].prenume, "Prenume2");

    repo.lista_repo.lista_participanti[2].id = 3;
    strcpy(repo.lista_repo.lista_participanti[2].nume, "Nume3");
    strcpy(repo.lista_repo.lista_participanti[2].prenume, "Prenume3");

    // Apelăm funcția de eliberare a memoriei
    elibereaza_lista_participanti(&repo);
    elibereaza_lista_undo(&repo);

    // Verificăm dacă lista de participanți a fost eliberată corect
    assert(repo.lista_repo.lista_participanti == NULL);  // lista ar trebui să fie NULL
    assert(repo.lista_repo.dimensiune == 0);  // dimensiunea ar trebui să fie 0
    assert(repo.lista_repo.capacitate == 0);  // capacitatea ar trebui să fie 0
    assert(repo.lista_repo_undo.lista_undo == NULL);
    assert(repo.lista_repo_undo.dimensiune == 0);
    assert(repo.lista_repo_undo.capacitate == 0);

    // Verificăm dacă nu putem accesa elemente din lista eliberată
    // Comportamentul de accesare directă a listei după eliberare ar trebui să ducă la erori sau la comportamente necontrolate,
    // dar nu este necesar să testăm acest lucru în mod explicit (doar să nu accesăm acea zonă de memorie).

    //printf("Testul pentru elibereaza_lista_participanti a trecut cu succes.\n");
}

void test_find() {
    Repository repo;
    initializare_lista_participanti(&repo);
    repo.lista_repo.dimensiune = 3;
    repo.lista_repo.lista_participanti[0].id = 1;
    repo.lista_repo.lista_participanti[1].id = 2;
    repo.lista_repo.lista_participanti[2].id = 3;
    assert(find(&repo, 1) == 0);
    assert(find(&repo, 2) == 1);
    assert(find(&repo, 3) == 2);
    assert(find(&repo, 4) == -1);
    elibereaza_lista_participanti(&repo);
}
//
void test_store() {
    Repository repo;
    initializare_lista_participanti(&repo);
    initializare_lista_undo(&repo);
    //adaugare participant
    assert(store(&repo, 1, "Nume1", "Prenume1") == 1);
    assert(repo.lista_repo.dimensiune == 1);
    assert(repo.lista_repo.lista_participanti[0].id == 1);
    assert(strcmp(repo.lista_repo.lista_participanti[0].nume, "Nume1") == 0);
    assert(strcmp(repo.lista_repo.lista_participanti[0].prenume, "Prenume1") == 0);
    //adaugare, id existent
    assert(store(&repo, 1, "Nume2", "Prenume2") == 0);
    assert(repo.lista_repo.dimensiune == 1);  // Dimensiunea nu ar trebui să se schimbe
    //adaugare participant
    assert(store(&repo, 2, "Nume2", "Prenume2") == 1);
    assert(repo.lista_repo.dimensiune == 2);
    assert(repo.lista_repo.lista_participanti[1].id == 2);
    assert(strcmp(repo.lista_repo.lista_participanti[1].nume, "Nume2") == 0);
    elibereaza_lista_participanti(&repo);

    initializare_lista_participanti(&repo);
    store(&repo, 1, "Nume1", "Prenume1");
    store(&repo, 2, "Nume2", "Prenume2");
    store(&repo, 3, "Nume3", "Prenume3");
    store(&repo, 4, "Nume4", "Prenume4");
    store(&repo, 5, "Nume5", "Prenume5");
    store(&repo, 6, "Nume6", "Prenume6");
    store(&repo, 7, "Nume7", "Prenume7");
    store(&repo, 8, "Nume8", "Prenume8");
    store(&repo, 9, "Nume9", "Prenume9");
    store(&repo, 10, "Nume10", "Prenume10");
    store(&repo, 11, "Nume11", "Prenume11");
    // printf("%d   ", repo.lista_repo.dimensiune);
    // printf("%d", repo.lista_repo.capacitate);
    assert(repo.lista_repo.capacitate == 20);
    elibereaza_lista_participanti(&repo);
    elibereaza_lista_undo(&repo);
}

void test_store_undo() {
    Repository repo;
    initializare_lista_participanti(&repo);
    initializare_lista_undo(&repo);
    store(&repo, 1, "Nume1", "Prenume1");
    store_undo(&repo,repo.lista_repo);
    assert(repo.lista_repo.dimensiune == 1);
    assert(repo.lista_repo_undo.lista_undo->lista_participanti[0].id == 1);
    elibereaza_lista_participanti(&repo);
    elibereaza_lista_undo(&repo);
}

void test_store_sters() {
    Repository repo;
    initializare_lista_participanti_stersi(&repo);
    store_sters(&repo,1,"Nume1","Prenume1",4,4);
    store_sters(&repo,2,"Nume1","Prenume1",4,4);
    store_sters(&repo,3,"Nume1","Prenume1",4,4);
    store_sters(&repo,4,"Nume1","Prenume1",4,4);
    store_sters(&repo,5,"Nume1","Prenume1",4,4);
    store_sters(&repo,6,"Nume1","Prenume1",4,4);
    store_sters(&repo,7,"Nume1","Prenume1",4,4);
    store_sters(&repo,8,"Nume1","Prenume1",4,4);
    store_sters(&repo,9,"Nume1","Prenume1",4,4);
    store_sters(&repo,10,"Nume1","Prenume1",4,4);
    store_sters(&repo,11,"Nume1","Prenume1",4,4);
    assert(repo.lista_repo_stersi.dimensiune == 11);
    elibereaza_lista_participanti_stersi(&repo);
}

void test_undo() {
    Repository repo;
    initializare_lista_participanti(&repo);
    initializare_lista_undo(&repo);
    store(&repo, 1, "Nume1", "Prenume1");
    store(&repo, 2, "Nume2", "Prenume2");
    // printf("%d\n", repo.lista_repo_undo.dimensiune);
    // for (int i = 0; i < repo.lista_repo_undo.dimensiune; i++) {
    //     for (int j = 0; j < repo.lista_repo_undo.lista_undo[i].dimensiune; j++) {
    //         printf("%d\n",repo.lista_repo_undo.lista_undo[i].lista_participanti[j].id);
    //         printf("%s\n",repo.lista_repo_undo.lista_undo[i].lista_participanti[j].nume);
    //         printf("%s\n",repo.lista_repo_undo.lista_undo[i].lista_participanti[j].prenume);
    //     }
    // }
    undo(&repo);
    assert(repo.lista_repo_undo.dimensiune == 0);
    assert(repo.lista_repo.dimensiune == 1);
    elibereaza_lista_participanti(&repo);
    elibereaza_lista_undo(&repo);
}

void test_delete() {
    Repository repo;
    initializare_lista_participanti(&repo);
    initializare_lista_undo(&repo);
    initializare_lista_participanti_stersi(&repo);
    repo.lista_repo.dimensiune = 3;
    repo.lista_repo.lista_participanti[0].id = 1;
    repo.lista_repo.lista_participanti[1].id = 2;
    repo.lista_repo.lista_participanti[2].id = 3;

    assert(delete(&repo, 2) == 1);
    assert(repo.lista_repo.dimensiune == 2);
    assert(repo.lista_repo.lista_participanti[0].id == 1);
    assert(repo.lista_repo.lista_participanti[1].id == 3);

    assert(delete(&repo, 4) == 0);
    assert(repo.lista_repo.dimensiune == 2);

    assert(delete(&repo, 1) == 1);
    assert(repo.lista_repo.dimensiune == 1);
    assert(repo.lista_repo.lista_participanti[0].id == 3);

    elibereaza_lista_participanti(&repo);
    elibereaza_lista_undo(&repo);
    elibereaza_lista_participanti_stersi(&repo);
}

void test_update() {
    Repository repo;
    initializare_lista_participanti(&repo);
    initializare_lista_undo(&repo);
    repo.lista_repo.dimensiune = 4;
    repo.lista_repo.lista_participanti[0].id = 1;
    repo.lista_repo.lista_participanti[1].id = 2;
    repo.lista_repo.lista_participanti[2].id = 3;
    repo.lista_repo.lista_participanti[3].id = 4;
    //participant existent
    assert(update(&repo, 2, "Nume2_updated", "Prenume2_updated", 5, 100) == 1);
    assert(strcmp(repo.lista_repo.lista_participanti[1].nume, "Nume2_updated") == 0);
    assert(strcmp(repo.lista_repo.lista_participanti[1].prenume, "Prenume2_updated") == 0);
    assert(repo.lista_repo.lista_participanti[1].probleme_rezolvate == 5);
    assert(repo.lista_repo.lista_participanti[1].scor == 100);
    assert(update(&repo, 4, "Nume4_update", "Prenume", -5, -100) == 0);
    //id inexistent
    assert(update(&repo, -5, "Nume4", "Prenume4", 3, 50) == 0);
    elibereaza_lista_participanti(&repo);
    elibereaza_lista_undo(&repo);
}

void test_all_repo() {
   test_initializare_lista_participanti();
    test_initializare_lista_undo();
    test_dealocare();
    test_find();
    test_store();
    test_store_undo();
    test_undo();
   test_delete();
   test_update();
    test_store_sters();
    test_initializare_lista_stersi();
   printf("Teste repo ok\n");
 }
