#include "../model/participant.h"
#include "teste_domain.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../model/validation.h"

void test_transpunere() {
    Participant p1 = {1, "Nume1", "Prenume1", 20, 3};
    Participant p2 = {2, "Nume2", "Prenume2", 40, 5};
    transpunere(&p1, &p2);

    assert(p1.id == p2.id);
    assert(strcmp(p1.nume, p2.nume) == 0);
    assert(strcmp(p1.prenume, p2.prenume) == 0);
    assert(p1.scor == p2.scor);
    assert(p1.probleme_rezolvate == p2.probleme_rezolvate);
    printf("Testele pentru domain ok\n");
}

void test_validare() {
    Participant p1 = {1, "Nume", "Prenume", 10, 1};
    assert(validare(p1) == 1);

    Participant p2 = {-1, "Nume", "Prenume", 0, 1};
    assert(validare(p2) == 0);

    Participant p3 = {2, "Nume", "Prenume", -3, 1};
    assert(validare(p3) == 0);

    Participant p4 = {3, "Nume", "Prenume", 5, -10};
    assert(validare(p4) == 0);
}

void test_all_domain() {
    test_transpunere();
    test_validare();
}


