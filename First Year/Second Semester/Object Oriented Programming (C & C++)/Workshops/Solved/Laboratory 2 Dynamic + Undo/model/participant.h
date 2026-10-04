#ifndef PARTICIPANT_H
#define PARTICIPANT_H

//Modul pentru declararea structurii de tip Participant + functie pentru copierea datelor dintr-o entitate participant in alta.

typedef struct {
    int id;
    char nume[22];
    char prenume[22];
    int scor;
    int probleme_rezolvate;
} Participant;

/*
 *Copiaza datele unui participant in alta entitate participant
 *participant1 - entitatea in care se copiaza atributele
 *participant2 - entitatea in care se copiaza atributele
 */

void transpunere(Participant* participant1, Participant* participant2);

#endif //PARTICIPANT_H

