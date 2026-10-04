#include<stdio.h>
#include "ui.h"
#include "../service/service_participanti.h"
#include "../util/util.h"
#include <ctype.h>
#include <string.h>


void run_app() {
    int isRunning = 1;
    Repository repo;
    initializare_lista_participanti(&repo);
    initializare_lista_undo(&repo);
    initializare_lista_participanti_stersi(&repo);

    while (isRunning) {
        meniu_principal();
        int choice = choice_selector();
        switch (choice) {
            default:
                printf("Optiune invalida\n");
            break;

            case 0:
                isRunning = 0;
                elibereaza_lista_participanti(&repo);
                elibereaza_lista_undo(&repo);
                elibereaza_lista_participanti_stersi(&repo);
            break;

            case 1:
                adauga_participant_ui(&repo);
                break;

            case 2:
                update_participant_ui(&repo);
                break;

            case 3:
                rezolvare_problema_ui(&repo);
                break;

            case 4:
                sterge_participant_ui(&repo);
                break;

            case 5:
                filtrare_ui(repo);
                break;

            case 6:
                meniu_sortari();
                int choice_sortare = choice_selector();
                if (choice_sortare == 1) {
                    sortare_nume_ui(repo);
                } else if (choice_sortare == 2) {
                    sortare_scor_ui(repo);
                } else {
                    printf("Optiune invalida");
                }
                break;

            case 7:
                print_lista_participanti(repo);
                break;

            case 8:
                undo_ui(&repo);
                break;

            case 9:
                print_lista_participanti_stersi(repo);
                break;
        }

    }
    printf("Se opreste executia aplicatiei");

}

void print_participant(Participant participant) {
    printf("%d. %s %s:\n\tScor: %d\n\tProbleme rezolvate: %d\n", participant.id,
           participant.nume, participant.prenume, participant.scor, participant.probleme_rezolvate);
}

void print_lista_participanti(Repository repo) {
    int dimensiune = repo.lista_repo.dimensiune;
    if (dimensiune == 0) {
        printf("Nu exista participanti inregistrati\n");
        return;
    }
    for (int i=0; i < dimensiune; i++) {
        print_participant(repo.lista_repo.lista_participanti[i]);
    }
}

void print_lista_participanti_stersi(Repository repo) {
    int dimensiune = repo.lista_repo_stersi.dimensiune;
    if (dimensiune == 0) {
        printf("Nu exista participanti stersi\n");
        return;
    }
    for (int i=0; i < dimensiune; i++) {
        print_participant(repo.lista_repo_stersi.lista_participanti_stersi[i]);
    }
}

void meniu_principal() {
    printf("Optiuni:\n \t1. Adaugare participant\n\t2. Actualizare participant\n\t3. Rezolvare problema\n\t"
           "4. Stergere participant\n\t5. Filtrare dupa scor (<scor)\n\t6. Sortari\n\t7. Afisare participanti\n\t8. Undo\n\t9. Afisare participanti stersi\n\t0. Exit\n");
}

void adauga_participant_ui(Repository* repo) {
    Participant participant = input_participant();
    int result = adauga_participant(repo, participant.id, participant.nume, participant.prenume);
    if (result)
        printf("Concurent adaugat cu succes\n");
    else
        printf("Concurent cu ID-ul %d deja existent\n", participant.id);
}

void sterge_participant_ui(Repository* repo) {
    int dimensiune = repo->lista_repo.dimensiune;
    if (dimensiune == 0) {
        printf("Nu exista participanti inregistrati\n");
        return;
    }
    print_lista_participanti(*repo);
    int id = id_selector();
    int result = sterge_participant(repo, id);
    if (result) {
        printf("Stergere facuta cu succes\n");
    } else {
        printf("Participantul cu ID %d nu a fost gasit\n", id);
    }
}

void rezolvare_problema_ui(Repository* repo) {
    int id = id_selector();
    int pos = find(repo, id);
    if (pos == -1) {
        printf("Participant cu ID-ul %d inexistent\n", id);
        return;
    }
    int punctaj = punctaj_input();
    int result = rezolvare_problema(repo, id, punctaj);
    if (result) {
        printf("Scorul participantului %s %s a fost actualizat la %d\n", repo->lista_repo.lista_participanti[pos].prenume, repo->lista_repo.lista_participanti[pos].nume, repo->lista_repo.lista_participanti[pos].scor);
    } else {
        printf("Participantul a rezolvat numarul maxim de probleme\n");
    }
}

void update_participant_ui(Repository* repo) {
    int dimensiune = repo->lista_repo.dimensiune;
    if (dimensiune == 0) {
        printf("Nu exista participanti inregistrati\n");
        return;
    }
    print_lista_participanti(*repo);
    int id = id_selector();
    int pos = find(repo, id);
    if (pos == -1) {
        printf("Participant cu ID-ul %d inexistent\n", id);
        return;
    }
    print_participant(repo->lista_repo.lista_participanti[pos]);

    meniu_update();
    int choice = choice_selector();
    int result;
    switch (choice) {
        default:
            printf("Optiune invalida\n");
            break;
        case 1:
            result = update_nume(repo, id, nume_input().nume);
            if (result) {
                printf("Modificare facuta cu succes\n");
            } else {
                printf("Eroare la modificare\n");
            }
            break;

        case 2:
            result = update_prenume(repo, id, prenume_input().prenume);
            if (result) {
            printf("Modificare facuta cu succes\n");
            } else {
            printf("Eroare la modificare\n");
            }
            break;

        case 3:
            result = update_probleme_rezolvate(repo, id, probleme_rezolvate_input());
            if (result) {
            printf("Modificare facuta cu succes\n");
            } else {
            printf("Eroare la modificare\n");
            }
            break;

        case 4:
            result = update_scor(repo, id, scor_input());
            if (result) {
            printf("Modificare facuta cu succes\n");
            } else {
            printf("Eroare la modificare\n");
            }
            break;
    }
}

void meniu_update() {
    printf("Optiuni de modificare: \n\t1. Nume\n\t2. Prenume\n\t3. Probleme rezolvate\n\t4. Scor\n");
}

void filtrare_ui(Repository repo) {
    if (repo.lista_repo.dimensiune == 0) {
        printf("Nu exista participanti inregistrati\n");
        return;
    }
    int scor = scor_input();
    Repository repo_filtrat = filtrare(repo, scor);
    printf("LISTA PARTICIPANTILOR CU SCORUL PESTE %d\n", scor);
    if (repo_filtrat.lista_repo.dimensiune == 0) {
        printf("Nu exista participanti cu scor > %d\n", scor);
        elibereaza_lista_participanti(&repo_filtrat);
        return;
    }
    print_lista_participanti(repo_filtrat);
    elibereaza_lista_participanti(&repo_filtrat);
}

void meniu_sortari() {
    printf("Sortari: \n\t1. Dupa nume\n\t2. Dupa scor\n");
}


void sortare_nume_ui(Repository repo) {
    int ordine = ordine_input();
    printf("LISTA PARTICIPANTILOR SORTATA DUPA NUME\n");
    print_lista_participanti(sortare_nume(repo, ordine, comparare_nume));
}


void sortare_scor_ui(Repository repo) {
    int ordine = ordine_input();
    printf("LISTA PARTICIPANTILOR SORTATA DUPA SCOR\n");
    print_lista_participanti(sortare_scor(repo, ordine, comparare_scor));
}


void undo_ui(Repository* repo) {
    int valid = undo_service(repo);
    if (!valid) {
        printf("Lista a ajuns vida!\n");
    }
}
