#include "../headers/undo.h"

void UndoAdauga::doUndo() {
    repo.remove_disciplina(disciplina.get_id());
}

void UndoSterge::doUndo() {
    repo.add_disciplina(disciplina);
}

void UndoModifica::doUndo() {
    repo.update_disciplina(disciplina_veche.get_id(), disciplina_veche);
}