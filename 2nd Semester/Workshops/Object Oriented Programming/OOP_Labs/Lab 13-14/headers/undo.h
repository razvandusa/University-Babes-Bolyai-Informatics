#pragma once
#include "repository.h"

class ActiuneUndo {
    public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
    RepositoryMemory& repo;
    Disciplina disciplina;
public:
    UndoAdauga(RepositoryMemory& r, const Disciplina& d) : repo(r), disciplina(d) {}

    /**
     * Realizeaza undo cand ultima operatie a fost adaugarea.
     */
    void doUndo() override;
};

class UndoSterge : public ActiuneUndo {
private:
    RepositoryMemory& repo;
    Disciplina disciplina;
public:
    UndoSterge(RepositoryMemory& r, const Disciplina& d) : repo(r), disciplina(d) {}

    /**
     * Realizeaza undo cand ultima operatie a fost stergerea.
     */
    void doUndo() override;
};

class UndoModifica : public ActiuneUndo {
private:
    RepositoryMemory& repo;
    Disciplina disciplina_veche;
public:
    UndoModifica(RepositoryMemory& r, const Disciplina& d) : repo(r), disciplina_veche(d) {}

    /**
     * Realizeaza undo cand ultima operatie a fost modificarea.
     */
    void doUndo() override;
};