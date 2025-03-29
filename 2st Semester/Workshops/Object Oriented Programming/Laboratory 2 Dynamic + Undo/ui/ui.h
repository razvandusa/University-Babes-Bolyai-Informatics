#ifndef UI_H
#define UI_H
//Gestioneaza meniurile consolei, introducerea de input de catre utilizator si afisarea erorilor si ruleaza aplicatia
//folosind logica implementata in Service
#include "../model/participant.h"
#include "../repo/repo.h"

//Ruleaza aplicatia si apeleaza functiile din UI pentru a citi input, stoca, modifica si afisa datele
void run_app();

//Printeaza meniul principal
void meniu_principal();

//Printeaza meniul cu optiunile de sortare
void meniu_sortari();

//Printeaza meniul cu optiunile de update
void meniu_update();

/*
 *Citeste datele unui participant si il adauga in repository
 *repo - repository-ul in care se adauga participantul
 */
void adauga_participant_ui(Repository* repo);

/*
 *Citeste id-ul unui participant si il sterge din repository
 *repo - repository-ul din care se sterge participantul
 */
void sterge_participant_ui(Repository* repo);

//Afiseaza datele tuturor participantilor din repository
//repo - repository-ul pentru care se printeaza datele tuturor participantilor
void print_lista_participanti(Repository repo);

void print_lista_participanti_stersi(Repository repo);

//Printeaza datele unui participant
//participant - participantul pentru care se printeaza datele
void print_participant(Participant participant);

//Citeste date pentru incrementarea numarului de probleme rezolvate si actualizarea scorului unui participant
//repo - repository-ul in care se afla participantul pentru care se face modificarea
void rezolvare_problema_ui(Repository* repo);

//Citeste date si modifica un anumit atribut al unui participant
void update_participant_ui(Repository *repo);

//Filtreaza si printeaza lista de participanti a unui repository pe baza unui scor citit ca input
void filtrare_ui(Repository repo);

//Citeste ordinea sortarii si afiseaza lista de participanti sortata dupa nume
void sortare_nume_ui(Repository repo);

//Citeste ordinea sortarii si afiseaza lista de participanti sortata dupa scor
void sortare_scor_ui(Repository repo);

//Se face undo la ultima operatie
void undo_ui(Repository* repo);

#endif //UI_H
