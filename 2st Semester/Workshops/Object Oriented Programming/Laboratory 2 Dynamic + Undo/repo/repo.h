#ifndef REPO_H
#define REPO_H

#include "../model/participant.h"
#include "../model/validation.h"
//Declararea structurilor ListaParticipanti si Repository, functii de initializare manipulare a datelor pentru repository

typedef struct {
    Participant* lista_participanti;
    int dimensiune;
    int capacitate;
} ListaParticipanti;

typedef struct {
    Participant* lista_participanti_stersi;
    int dimensiune;
    int capacitate;
} ListaParticipantiStersi;

typedef struct {
    ListaParticipanti* lista_undo;
    int dimensiune;
    int capacitate;
} ListaUndo;

typedef struct {
    ListaParticipanti lista_repo;
    ListaUndo lista_repo_undo;
    ListaParticipantiStersi lista_repo_stersi;
} Repository;


/*
 *Initializeaza lista de participanti a unui repository
 *repo - repository-ul care se initializeaza
 */
void initializare_lista_participanti(Repository *repo);

/*Initializeaza memorie suficienta listei
 *repo - repositoryul in care se initializeaza
 */
void initializare_lista_undo(Repository *repo);

/*Initializeaza memorie suficienta listei
 *repo - repositoryul in care se initializeaza
 */
void initializare_lista_participanti_stersi(Repository* repo);

/*
 *Elibereaza memoria ocupata ce se afla in lista stearsa
 *repo - repository-ul in care se adauga
 */
void elibereaza_lista_participanti(Repository *repo);

/*
 *Elibereaza memoria ocupata ce se afla in lista stearsa
 *repo - repository-ul in care se adauga
 */
void elibereaza_lista_undo(Repository* repo);

/*
 *Elibereaza memoria ocupata ce se afla in lista de undo
 *repo - repository-ul in care se adauga
 */
void elibereaza_lista_participanti_stersi(Repository* repo);

/*
 *Adauga in lista de participanti a unui repository un nou participant pe baza de id, nume, prenume
 *repo - repository-ul in care se adauga
 *id - id-ul participantului
 *nume - numele participantului
 *prenume - prenumele participantului
 *return 1 daca participantul a fost adaugat in lista, 0 otherwise (participantul e existent, date invalide)
 */
int store(Repository* repo, int id, char* nume, char* prenume);

/*
 *Stocheaza in lista de undo lista curenta
 *repo - repository-ul in care se stocheaza lista undo
 */
void store_undo(Repository* repo, ListaParticipanti lista_participanti);

/*
 *Stocheaza in lista de liste sterse lista stearsa
 *repo - repository-ul in care se stocheaza lista stearsa
 */
void store_sters(Repository* repo, int id,  char* nume,  char* prenume, int scor, int probleme_rezolvate);

/*
 *Se face undo la ultima operatie
 *repo - repository-ul in care se face undo
 */
void undo(Repository* repo);

/*
 *Sterge un participant din lista de participanti a unui repository
 *repo - repository-ul in care se face stergerea
 *id - id-ul participantului care trebuie sters
 *return 1 daca stergerea s-a efectuat cu succes, 0 in caz contrar
 */
int delete(Repository* repo, int id);

/*
 *Cauta pozitia unui participant intr-un repository
 *repo - repository-ul in care se face cautarea
 *id - id-ul participantului cautat
 *return <pozitia participantului in lista de participanti> daca acesta exista, -1 daca participantul nu se afla in lista
 */
int find(Repository* repo, int id);

/*
 *Modifica datele unui participant inregistrat in repository
 *repo - repository-ul in care se face modificarea participantului
 *id - id-ul participantului pentru care se face modificarea
 *nume - noul nume
 *prenume - noul prenume
 *probleme - noul numar de probleme
 *scor - noul scor
 *return 1 daca modificarea s-a facut cu succes, 0 otherwise
 */
int update(Repository* repo, int id,  char* nume,  char* prenume, int probleme, int scor);

#endif
