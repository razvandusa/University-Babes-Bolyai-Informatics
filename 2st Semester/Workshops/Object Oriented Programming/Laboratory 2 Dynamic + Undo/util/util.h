#ifndef UTIL_H
#define UTIL_H
//Functii de citire si validare a input-ului de la utilizator
#include "../model/participant.h"

/*
 *Citeste si valideaza optiunea introdusa de utilizator
 *return optiunea introdusa
 */
int choice_selector();

/*
 *Citeste id-ul unei entitati de tip participant
 *return id-ul introdus
 */
int id_selector();

/*
 *Citeste punctajul unei probleme rezolvate
 *return punctajul introdus
 */
int punctaj_input();

/*
 *Citeste id-ul, numele si prenumele unui participant
 *return participant cu id, nume si prenume initializate cu datele introduse
 */
Participant input_participant();

/*
 *Citeste numele unui participant
 *return participant cu atributul nume initializat cu numele introdus
 */
Participant nume_input();

/*
 *Citeste prenumele unui participant
 *return participant cu atributul prenume initializat cu prenumele introdus
 */
Participant prenume_input();

/*
 *Citeste numarul de probleme rezolvate al unei entitati de tip participant
 *return numarul de probleme introdus
 */
int probleme_rezolvate_input();

/*
 *Citeste scorul unei entitati de tip participant
 *return scorul introdus
 */
int scor_input();

/*
 *Citeste ordinea pentru sortarea participantilor (crescator/descrescator)
 *return 1 - crescator, 0 - descrescator
 */
int ordine_input();


#endif
