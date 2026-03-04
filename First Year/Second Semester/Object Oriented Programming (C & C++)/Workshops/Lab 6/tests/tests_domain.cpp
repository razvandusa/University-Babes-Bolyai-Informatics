#include "../headers/domain.h"
#include <cassert>

void test_constructor_disciplina_implicit() {
    Disciplina disciplina;
    assert (disciplina.get_id() == 0);
    assert (disciplina.get_denumire() == "");
    assert (disciplina.get_ore() == 0);
    assert (disciplina.get_tip() == "");
    assert (disciplina.get_cadru_didactic() == "");
}

void test_constructor_disciplina() {
    Disciplina disciplina = Disciplina(2,"Matematica",4,"Reala","Ioan Paul");
    assert (disciplina.get_id() == 2);
    assert (disciplina.get_denumire() == "Matematica");
    assert (disciplina.get_ore() == 4);
    assert (disciplina.get_tip() == "Reala");
    assert (disciplina.get_cadru_didactic() == "Ioan Paul");
}

void test_get_set() {
    Disciplina disciplina = Disciplina(2,"Matematica",4,"Reala","Ioan Paul");
    disciplina.set_id(1);
    disciplina.set_denumire("Limba Romana");
    disciplina.set_ore(20);
    disciplina.set_tip("Umana");

    disciplina.set_cadru_didactic("Andrei Maruta");
    assert (disciplina.get_id() == 1);
    assert (disciplina.get_denumire() == "Limba Romana");
    assert (disciplina.get_ore() == 20);
    assert (disciplina.get_tip() == "Umana");
    assert (disciplina.get_cadru_didactic() == "Andrei Maruta");
}

void test_disciplini_egale() {
    Disciplina disciplina = Disciplina(2,"Matematica",4,"Reala","Ioan Paul");
    assert (disciplina == disciplina);

    Disciplina disciplina_diferita = Disciplina(1,"Matematica",4,"Reala","Ioan Paul");
    assert (disciplina != disciplina_diferita);

    disciplina_diferita = Disciplina(2,"Limba Romana",4,"Reala","Ioan Paul");
    assert (disciplina != disciplina_diferita);

    disciplina_diferita = Disciplina(2,"Matematica",20,"Reala","Ioan Paul");
    assert (disciplina != disciplina_diferita);

    disciplina_diferita = Disciplina(2,"Matematica",4,"Umana","Ioan Paul");
    assert (disciplina != disciplina_diferita);

    disciplina_diferita = Disciplina(2,"Matematica",4,"Reala","Andrei Maruta");
    assert (disciplina != disciplina_diferita);
}

void teste_domain() {
    test_constructor_disciplina_implicit();
    test_constructor_disciplina();
    test_get_set();
    test_disciplini_egale();
}
