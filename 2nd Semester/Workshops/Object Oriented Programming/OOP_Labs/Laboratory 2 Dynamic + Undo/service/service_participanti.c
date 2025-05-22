#include "service_participanti.h"

#include <stdlib.h>
#include <string.h>

#include "../repo/repo.h"


int adauga_participant(Repository* repo, int id,   char* nume,  char* prenume) {
    return store(repo, id, nume, prenume);
}

int sterge_participant(Repository* repo, int id) {
    return delete(repo, id);
}

int rezolvare_problema(Repository* repo, int id, int punctaj) {
    int pos = find(repo, id);
    if (pos == -1)
        return 0;
    repo->lista_repo.lista_participanti[pos].probleme_rezolvate++;
    repo->lista_repo.lista_participanti[pos].scor += punctaj;
    return 1;

}

int update_nume(Repository* repo, int id,   char* nume_update) {
    int pos = find(repo, id);
    if (pos == -1) {
        return 0;
    }

    Participant* participant = &repo->lista_repo.lista_participanti[pos];

    return update(repo, id, nume_update, participant->prenume, participant->probleme_rezolvate, participant->scor);
}

int update_prenume(Repository* repo,  int id,   char* prenume_update) {
    int pos = find(repo, id);
    if (pos == -1) {
        return 0;
    }

    Participant* participant = &repo->lista_repo.lista_participanti[pos];

    return update(repo, id, participant->nume, prenume_update, participant->probleme_rezolvate, participant->scor);
}

int update_probleme_rezolvate(Repository* repo, int id, int probleme_update) {
    int pos = find(repo, id);
    if (pos == -1 || probleme_update < 0) {
        return 0;
    }

    Participant* participant = &repo->lista_repo.lista_participanti[pos];

    return update(repo, id, participant->nume, participant->prenume, probleme_update, participant->scor);
}

int update_scor(Repository* repo, int id, int scor_upadte) {

        int pos = find(repo, id);
        if (pos == -1 || scor_upadte < 0) {
            return 0;
        }

        Participant* participant = &repo->lista_repo.lista_participanti[pos];

        return update(repo, id, participant->nume, participant->prenume, participant->probleme_rezolvate, scor_upadte);
}

Repository filtrare(Repository repo, int scor) {
    int dimensiune = repo.lista_repo.dimensiune;
    Repository repo_filtrat;
    initializare_lista_participanti(&repo_filtrat);
    repo_filtrat.lista_repo.dimensiune = dimensiune;
    if (dimensiune  == 0) {
        return repo_filtrat;
    }
    int index = 0;
    for (int i = 0; i < dimensiune; i++) {
        if (repo.lista_repo.lista_participanti[i].scor >= scor) {
            transpunere(&repo_filtrat.lista_repo.lista_participanti[index], &repo.lista_repo.lista_participanti[i]);
            index++;
        }
    }
    repo_filtrat.lista_repo.dimensiune = index;
    return repo_filtrat;
}

void swtich_participanti(Participant* p1, Participant* p2) {
    Participant p_aux;
    transpunere(&p_aux, p1);
    transpunere(p1, p2);
    transpunere(p2, &p_aux);
}

Repository sortare_nume(Repository repo, int ordine, int (*comparare)(Participant, Participant)) {
    int dimensiune = repo.lista_repo.dimensiune;

    if (dimensiune == 0) {
        return repo;
    }

    //crescator
    if (ordine == 1) {
        for (int i = 0; i < dimensiune-1; i++) {
            for (int j = i+1; j < dimensiune; j++) {
                if (comparare(repo.lista_repo.lista_participanti[i], repo.lista_repo.lista_participanti[j]) > 0) {
                        swtich_participanti(&repo.lista_repo.lista_participanti[i], &repo.lista_repo.lista_participanti[j]);
                    }
                }

            }
        return repo;
        }


    //descrescator
    for (int i = 0; i < dimensiune-1; i++) {
        for (int j = i+1; j < dimensiune; j++) {
            if (comparare(repo.lista_repo.lista_participanti[i], repo.lista_repo.lista_participanti[j]) < 0) {
                    swtich_participanti(&repo.lista_repo.lista_participanti[i], &repo.lista_repo.lista_participanti[j]);
                }
        }
    }
    return repo;


}

int comparare_nume(Participant p1, Participant p2) {
    if (strcmp(p1.nume, p2.nume) == 0) {
        if (strcmp(p1.prenume, p2.prenume) == 0) {
            return comparare_scor(p1, p2);
        } else {
            return strcmp(p1.prenume, p2.prenume);
        }
    }
    return strcmp(p1.nume, p2.nume);
}

int comparare_scor(Participant p1, Participant p2) {
    if (p1.scor == p2.scor) {
        return 0;
    } else if (p1.scor > p2.scor) {
        return 1;
    }
    return -1;
}

Repository sortare_scor(Repository repo, int ordine, int (*comparare)(Participant, Participant)) {
    int dimensiune = repo.lista_repo.dimensiune;
    if (dimensiune == 0) {
        return repo;
    }

    //crescator
    if (ordine == 1) {
        for (int i = 0; i < dimensiune-1; i++) {
            for (int j = i+1; j < dimensiune; j++) {
                 if (comparare(repo.lista_repo.lista_participanti[i], repo.lista_repo.lista_participanti[j]) > 0) {
                    swtich_participanti(&repo.lista_repo.lista_participanti[i], &repo.lista_repo.lista_participanti[j]);
                }
            }

        }
        return repo;
    }
    //descrescator
    for (int i = 0; i < dimensiune-1; i++) {
        for (int j = i+1; j < dimensiune; j++) {
            if (comparare(repo.lista_repo.lista_participanti[i], repo.lista_repo.lista_participanti[j]) < 0) {
                swtich_participanti(&repo.lista_repo.lista_participanti[i], &repo.lista_repo.lista_participanti[j]);
            }
        }
    }
    return repo;
}

int undo_service(Repository* repo) {
    if (repo->lista_repo_undo.dimensiune == 0) {
        elibereaza_lista_participanti(repo);
        initializare_lista_participanti(repo);
        return 0;
    }
    undo(repo);
    return 1;
}
