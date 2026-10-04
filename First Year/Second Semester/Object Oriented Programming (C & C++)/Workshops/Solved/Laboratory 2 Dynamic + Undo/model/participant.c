#include "participant.h"

#include <string.h>

void transpunere(Participant* participant1, Participant* participant2) {
    participant1->id = participant2->id;
    strcpy(participant1->nume, participant2->nume);
    strcpy(participant1->prenume, participant2->prenume);
    participant1->scor = participant2->scor;
    participant1->probleme_rezolvate = participant2->probleme_rezolvate;
}
