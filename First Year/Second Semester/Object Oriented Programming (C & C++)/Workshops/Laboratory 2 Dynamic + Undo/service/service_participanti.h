#ifndef SERVICE_PARTICIPANTI_H
#define SERVICE_PARTICIPANTI_H

#include "../model/participant.h"
#include "../repo/repo.h"

//Business logic pentru aplicatie, folosind datele dintr-o entitate Repository

/*
 *Adauga in lista de participanti a unui repository un nou participant pe baza de id, nume, prenume
 *repo - repository-ul in care se adauga
 *id - id-ul participantului
 *nume - numele participantului
 *prenume - prenumele participantului
 *return 1 daca participantul a fost adaugat in lista, 0 otherwise (participantul e existent, date invalide)
 */
int adauga_participant(Repository* repo, int id,  char* nume,  char* prenume);


/*
 *Sterge un participant din lista de participanti a unui repository
 *repo - repository-ul in care se face stergerea
 *id - id-ul participantului care trebuie sters
 *return 1 daca stergerea s-a efectuat cu succes, 0 in caz contrar
 */
int sterge_participant(Repository* repo, int id);

/*
 *Creste numarul de probleme rezolvate de un participant cu 1 si aduna la scorul participantului punctajul problemei
 *repo - repository-ul in care se afla salvat participantul care rezolva problema
 *id - id-ul participantului
 *punctaj - punctajul problemei rezolvate
 *return 1 daca modificarea s-a facut cu succes, 0 daca nu s-a gasit participantul cu id-ul respectiv
 */
int rezolvare_problema(Repository* repo, int id, int punctaj);


/*
 *Modifica numele unui participant
 *repo - repository-ul in care se face modificarea
 *id - id-ul participantului
 *nume_update - noul nume
 *return 1 daca modificarea s-a facut cu succes, 0 otherwise (participantul nu a fost gasit)
 */
int update_nume(Repository* repo, int id,   char* nume_update);


/*
 *Modifica prenumele unui participant
 *repo - repository-ul in care se face modificarea
 *id - id-ul participantului
 *prenume_update - noul prenume
 *return 1 daca modificarea s-a facut cu succes, 0 otherwise (participantul nu a fost gasit)
 */
int update_prenume(Repository* repo,  int id,  char* prenume_update);


/*
 *Modifica numarul de probleme rezolvate ale unui participant
 *repo - repository-ul in care se face modificarea
 *id - id-ul participantului
 *probleme_update - noul numar de probleme
 *return 1 daca modificarea s-a facut cu succes, 0 otherwise (participantul nu a fost gasit/numar de probleme invalid)
 */
int update_probleme_rezolvate(Repository* repo, int id, int probleme_update);


/*
 *Modifica scorul unui participant
 *repo - repository-ul in care se face modificarea
 *id - id-ul participantului
 *scor_update - noul scor
 *return 1 daca modificarea s-a facut cu succes, 0 otherwise (participantul nu a fost gasit/scor invalid)
 */
int update_scor(Repository* repo, int id, int scor_upadte);

/*
 *Returneaza o copie cu lista de participanti filtrata (eliminand participantii cu un scor mai mic decat o anumita valoare) a unui repository
 *repo - repository-ul dupa care se construieste copia
 *scor - valoarea minima necesara pentru a pastra un participant in lista
 *return o copie a repository-ului in care lista de participanti contine numai participanti cu scorul mai mare sau egal cu valoarea data
 */
Repository filtrare(Repository repo, int scor);

/*
 *Creaza o copie cu lista de participanti sortata descrescator/crescator dupa nume a unui repository
 *repo - repository-ul dupa care se construieste copia
 *ordine - ordinea crescatoare/descrescatoare de sortare (1/0)
 *return copie cu lista de participanti sortata dupa nume
 */
Repository sortare_nume(Repository repo, int ordine, int (*comparare)(Participant, Participant));

/*
 *Creaza o copie cu lista de participanti sortata descrescator/crescator dupa scor a unui repository
 *repo - repository-ul dupa care se construieste copia
 *ordine - ordinea crescatoare/descrescatoare de sortare (1/0)
 *return copie cu lista de participanti sortata dupa scor
 */
Repository sortare_scor(Repository repo, int ordine, int (*comparare)(Participant, Participant));


/*
 *Interschimba datele a doi participanti
 *p1 - primul participant
 *p2 - al doilea participant
 */
void swtich_participanti(Participant* p1, Participant* p2);

/*
 *Compara doi participanti pe baza numelui
 *p1 - primul participant
 *p2 - al doilea participant
 *return int < 0, daca p1 < p2 dupa nume, 0 daca p1=p2 si int > 0 daca p1 > p2
 */
int comparare_nume(Participant p1, Participant p2);

/*
 *Compara doi participanti pe baza scorului
 *p1 - primul participant
 *p2 - al doilea participant
 *return int < 0, daca scor p1 < scor p2 , 0 daca p1=p2 si int > 0 daca p1 > p2
 */
int comparare_scor(Participant p1, Participant p2);

/*
 *Se face undo la ultima operatie
 *repo - repositoryul unde se face undo
 */
int undo_service(Repository* repo);

#endif
