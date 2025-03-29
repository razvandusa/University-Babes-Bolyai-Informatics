#include "repo.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void initializare_lista_participanti(Repository* repo) {
    repo->lista_repo.lista_participanti = calloc(sizeof(Participant),10);
    repo->lista_repo.dimensiune = 0;
    repo->lista_repo.capacitate = 10;
}

void initializare_lista_participanti_stersi(Repository* repo) {
    repo->lista_repo_stersi.lista_participanti_stersi = calloc(sizeof(Participant),10);
    repo->lista_repo_stersi.dimensiune = 0;
    repo->lista_repo_stersi.capacitate = 10;
}

void initializare_lista_undo(Repository* repo) {
    repo->lista_repo_undo.lista_undo = malloc(sizeof(ListaParticipanti) * 10);
    for (int i = 0; i < 10; i++) {
        repo->lista_repo_undo.lista_undo[i].lista_participanti = calloc(sizeof(Participant),10);
    }
    repo->lista_repo_undo.dimensiune = 0;
    repo->lista_repo_undo.capacitate = 10;
}

void elibereaza_lista_participanti(Repository* repo) {
    free(repo->lista_repo.lista_participanti);
    repo->lista_repo.lista_participanti = NULL;
    repo->lista_repo.dimensiune = 0;
    repo->lista_repo.capacitate = 0;
}

void elibereaza_lista_participanti_stersi(Repository* repo) {
    free(repo->lista_repo_stersi.lista_participanti_stersi);
    repo->lista_repo_stersi.lista_participanti_stersi = NULL;
    repo->lista_repo_stersi.dimensiune = 0;
    repo->lista_repo_stersi.capacitate = 0;
}

void elibereaza_lista_undo(Repository* repo) {

    for (int i = 0; i < repo->lista_repo_undo.capacitate; i++) {
        if (repo->lista_repo_undo.lista_undo[i].lista_participanti) {
            free(repo->lista_repo_undo.lista_undo[i].lista_participanti);
            repo->lista_repo_undo.lista_undo[i].lista_participanti = NULL;
        }
    }

    free(repo->lista_repo_undo.lista_undo);
    repo->lista_repo_undo.lista_undo = NULL;
    repo->lista_repo_undo.dimensiune = 0;
    repo->lista_repo_undo.capacitate = 0;
}


int find(Repository* repo, int id) {
    for (int i = 0; i < repo->lista_repo.dimensiune; i++) {
        if(repo->lista_repo.lista_participanti[i].id == id) {
            return i;
        }
    }
    return -1;
}

int store(Repository* repo, int id,  char* nume,  char* prenume) {
    if (repo->lista_repo.dimensiune > 0) {
        store_undo(repo,repo->lista_repo);
    }

    if (find(repo, id) != -1) {
        return 0;
    }

    if (repo->lista_repo.dimensiune == repo->lista_repo.capacitate) {
        int new_capacitate = repo->lista_repo.capacitate * 2;
        Participant* new_list = realloc(repo->lista_repo.lista_participanti, new_capacitate * sizeof(Participant));
        // if (new_list == NULL) {
        //     return 0;
        // }
        repo->lista_repo.lista_participanti = new_list;
        repo->lista_repo.capacitate = new_capacitate;
    }

    int dimensiune = repo->lista_repo.dimensiune;
    //lista->lista_participanti[lista->dimensiune].id = id;
    repo->lista_repo.lista_participanti[dimensiune].id = id;

    //folosirea strncpy previne erorile cauzate de nume prea mari primite ca parametri
    strncpy(repo->lista_repo.lista_participanti[dimensiune].nume, nume, 19);
    repo->lista_repo.lista_participanti[dimensiune].nume[20] = '\0';
    strncpy(repo->lista_repo.lista_participanti[dimensiune].prenume, prenume, 19);
    repo->lista_repo.lista_participanti[dimensiune].prenume[20] = '\0';

    repo->lista_repo.lista_participanti[dimensiune].scor = 0;
    repo->lista_repo.lista_participanti[dimensiune].probleme_rezolvate = 0;

    repo->lista_repo.dimensiune++;

    return 1;
}

void store_undo(Repository* repo, ListaParticipanti lista_repo) {
    int curent = repo->lista_repo_undo.dimensiune;

    // Verificam și realocam lista de undo daca este necesar
    if (repo->lista_repo_undo.capacitate == repo->lista_repo_undo.dimensiune) {
        int new_capacitate = (repo->lista_repo_undo.capacitate == 0) ? 2 : repo->lista_repo_undo.capacitate * 2;
        ListaParticipanti* new_undo_list = realloc(repo->lista_repo_undo.lista_undo, new_capacitate * sizeof(ListaParticipanti));

        repo->lista_repo_undo.lista_undo = new_undo_list;
        repo->lista_repo_undo.capacitate = new_capacitate;
    }

    // Asiguram alocarea de memorie pentru lista_participanti
    if (lista_repo.dimensiune >= repo->lista_repo_undo.lista_undo[curent].capacitate) {
        // Cream suficient spatiu pentru fiecare participant
        repo->lista_repo_undo.lista_undo[curent].lista_participanti = realloc(
            repo->lista_repo_undo.lista_undo[curent].lista_participanti,
            lista_repo.dimensiune * sizeof(Participant)
        );
    }

    // Copiem participantii în lista de undo
    for (int i = 0; i < lista_repo.dimensiune; i++) {
        repo->lista_repo_undo.lista_undo[curent].lista_participanti[i] = lista_repo.lista_participanti[i];

        // Copiem numele si prenumele
        repo->lista_repo_undo.lista_undo[curent].lista_participanti[i].nume[sizeof(repo->lista_repo_undo.lista_undo[curent].lista_participanti[i].nume) - 1] = '\0';
        repo->lista_repo_undo.lista_undo[curent].lista_participanti[i].prenume[sizeof(repo->lista_repo_undo.lista_undo[curent].lista_participanti[i].prenume) - 1] = '\0';
    }

    // Actualizam dimensiunile și capacitatile
    repo->lista_repo_undo.lista_undo[curent].dimensiune = lista_repo.dimensiune;
    repo->lista_repo_undo.lista_undo[curent].capacitate = lista_repo.capacitate;
    repo->lista_repo_undo.dimensiune++;
}

void store_sters(Repository* repo, int id,  char* nume,  char* prenume, int scor, int probleme_rezolvate) {

    if (repo->lista_repo_stersi.dimensiune == repo->lista_repo_stersi.capacitate) {
        int new_capacitate = repo->lista_repo_stersi.capacitate * 2;
        Participant* new_list = realloc(repo->lista_repo_stersi.lista_participanti_stersi, new_capacitate * sizeof(Participant));
        // if (new_list == NULL) {
        //     return 0;
        // }
        repo->lista_repo_stersi.lista_participanti_stersi = new_list;
        repo->lista_repo_stersi.capacitate = new_capacitate;
    }

    int dimensiune = repo->lista_repo_stersi.dimensiune;
    //lista->lista_participanti[lista->dimensiune].id = id;
    repo->lista_repo_stersi.lista_participanti_stersi[dimensiune].id = id;

    //folosirea strncpy previne erorile cauzate de nume prea mari primite ca parametri
    strncpy(repo->lista_repo_stersi.lista_participanti_stersi[dimensiune].nume, nume, 19);
    repo->lista_repo_stersi.lista_participanti_stersi[dimensiune].nume[20] = '\0';
    strncpy(repo->lista_repo_stersi.lista_participanti_stersi[dimensiune].prenume, prenume, 19);
    repo->lista_repo_stersi.lista_participanti_stersi[dimensiune].prenume[20] = '\0';
    repo->lista_repo_stersi.lista_participanti_stersi[dimensiune].scor = scor;
    repo->lista_repo_stersi.lista_participanti_stersi[dimensiune].probleme_rezolvate = probleme_rezolvate;

    repo->lista_repo_stersi.dimensiune++;
}

void undo(Repository* repo) {
    //Copiem participantii
    // for (int i = 0; i < repo->lista_repo_undo.dimensiune; i++) {
    //     for (int j = 0; j < repo->lista_repo_undo.lista_undo[i].dimensiune; j++) {
    //         printf("%d\n",repo->lista_repo_undo.lista_undo[i].lista_participanti[j].id);
    //         printf("%s\n",repo->lista_repo_undo.lista_undo[i].lista_participanti[j].nume);
    //         printf("%s\n",repo->lista_repo_undo.lista_undo[i].lista_participanti[j].prenume);
    //     }
    // }
    int curent = repo->lista_repo_undo.dimensiune - 1;

    for (int i = 0; i < repo->lista_repo_undo.lista_undo[curent].dimensiune; i++) {
        repo->lista_repo.lista_participanti[i].id = repo->lista_repo_undo.lista_undo[curent].lista_participanti[i].id;
        strcpy(repo->lista_repo.lista_participanti[i].nume,repo->lista_repo_undo.lista_undo[curent].lista_participanti[i].nume);
        strcpy(repo->lista_repo.lista_participanti[i].prenume,repo->lista_repo_undo.lista_undo[curent].lista_participanti[i].prenume);
        repo->lista_repo.lista_participanti[i].scor = repo->lista_repo_undo.lista_undo[curent].lista_participanti[i].scor;
        repo->lista_repo.lista_participanti[i].probleme_rezolvate = repo->lista_repo_undo.lista_undo[curent].lista_participanti[i].probleme_rezolvate;
    }
    // printf("%d\n",repo->lista_repo_undo.lista_undo[curent].dimensiune);
    repo->lista_repo.dimensiune = repo->lista_repo_undo.lista_undo[curent].dimensiune;
    repo->lista_repo_undo.dimensiune--;
}

int delete(Repository* repo, int id) {
    if (repo->lista_repo.dimensiune > 0) {
        store_undo(repo,repo->lista_repo);
    }
    int pos = find(repo, id);
    if (pos == -1) { return 0; }
    store_sters(repo,pos,repo->lista_repo.lista_participanti[pos].nume,repo->lista_repo.lista_participanti[pos].prenume,repo->lista_repo.lista_participanti[pos].scor,repo->lista_repo.lista_participanti[pos].probleme_rezolvate);
    for (int i = pos; i < repo->lista_repo.dimensiune - 1; i++) {
        transpunere(&repo->lista_repo.lista_participanti[i], &repo->lista_repo.lista_participanti[i+1]);
    }
    repo->lista_repo.dimensiune--;

    if (repo->lista_repo.dimensiune > 0 && repo->lista_repo.dimensiune <= repo->lista_repo.capacitate / 4) {
        int new_capacity = repo->lista_repo.capacitate / 2;
        if (new_capacity < 10) {
            new_capacity = 10;
        }
        Participant* new_list = realloc(repo->lista_repo.lista_participanti, new_capacity * sizeof(Participant));
        if (new_list != NULL) {
            repo->lista_repo.lista_participanti = new_list;
            repo->lista_repo.capacitate = new_capacity;
        }
    }

    return 1;
}

int update(Repository* repo, int id,  char* nume,  char* prenume, int probleme, int scor) {
    if (repo->lista_repo.dimensiune > 0) {
        store_undo(repo,repo->lista_repo);
    }
    int pos = find(repo, id);
    if (pos == -1) {
        return 0;
    }
    Participant new_data;
    new_data.id = id;
    strcpy(new_data.nume, nume);
    strcpy(new_data.prenume, prenume);
    new_data.probleme_rezolvate = probleme;
    new_data.scor = scor;
    if (validare(new_data) == 0)
        return 0;
    transpunere(&repo->lista_repo.lista_participanti[pos], &new_data);

    return 1;
}


