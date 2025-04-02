#include "../headers/ui.h"
#include <iostream>

void UI::menu() {
    std::cout << "\nAlege optiunea : \n";
    std::cout << "1. Adauga disciplina\n";
    std::cout << "2. Sterge disciplina\n";
    std::cout << "3. Modifica disciplina\n";
    std::cout << "4. Afisare discipline\n";
    std::cout << "5. Filtreaza discipline\n";
    std::cout << "6. Sorteaza discipline\n";
    std::cout << "0. Exit\n";
}

void UI::run() {
    bool run = true;
    int optiune;
    while (run) {
        menu();
        std::cin >> optiune;
        switch (optiune) {
            case 0:
                run = false;
                break;
            case 1:
                add_disciplina_UI();
                break;
            case 2:
                remove_disciplina_UI();
                break;
            case 3:
                update_disciplina_UI();
                break;
            case 4:
                show_list_UI();
                break;
            case 5:
                filtrare_discipline_UI();
                break;
            case 6:
                sortare_discipline_UI();
                break;
            default:
                std::cout << "Optiune invalida!\n";
        }
    }
}

void UI::add_disciplina_UI() {
    int id;
    std::string denumire;
    int ore;
    std::string tip;
    std::string cadru_didactic;
    std::cout << "Scrie id-ul disciplinei pe care o adaugi : ";
    std::cin >> id;
    std::cout << "Scrie denumirea disciplinei pe care o adaugi : ";
    std::cin.ignore();
    std::getline(std::cin, denumire);
    std::cout << "Scrie numarul de ore a disciplinei pe care o adaugi : ";
    std::cin >> ore;
    std::cout << "Scrie tipul disciplinei pe care o adaugi : ";
    std::cin.ignore();
    std::getline(std::cin, tip);
    std::cout << "Scrie cadrul didactic corespunzator disciplinei pe care o adaugi : ";
    std::getline(std::cin, cadru_didactic);
    std::string mesaj = service.add_disciplina(id, denumire, ore, tip, cadru_didactic);
    std::cout << mesaj;
}

void UI::remove_disciplina_UI() {
    int id;
    std::cout << "Scrie id-ul disciplinei pe care o stergi : ";
    std::cin >> id;
    std::string mesaj = service.remove_disciplina(id);
    std::cout << mesaj;
}

void UI::update_disciplina_UI() {
    int id;
    std::string new_denumire;
    int new_ore;
    std::string new_tip;
    std::string new_cadru_didactic;
    std::cout << "Scrie id-ul disciplinei pe care o modifici : ";
    std::cin >> id;
    std::cout << "Scrie noua denumirea a disciplinei pe care o modifici : ";
    std::cin.ignore();
    std::getline(std::cin, new_denumire);
    std::cout << "Scrie numarul nou de ore a disciplinei pe care o modifici : ";
    std::cin >> new_ore;
    std::cout << "Scrie tipul nou a disciplinei pe care o modifici : ";
    std::cin.ignore();
    std::getline(std::cin, new_tip);
    std::cout << "Scrie noul cadrul didactic corespunzator disciplinei pe care o modifici : ";
    std::getline(std::cin, new_cadru_didactic);
    std::string mesaj = service.update_disciplina(id, new_denumire, new_ore, new_tip, new_cadru_didactic);
    std::cout << mesaj;
}

void UI::show_list_UI() {
    std::vector<Disciplina> lista_discipline = service.get_lista_discipline();
    if (lista_discipline.empty()) {
        std::cout << "Lista de discipline este goala!";
    }
    else {
        for (const auto& disciplina : lista_discipline) {
            std::cout <<"ID-ul disciplinei : " << disciplina.get_id() << std::endl;
            std::cout <<"Denumirea disciplinei : " << disciplina.get_denumire() << std::endl;
            std::cout <<"Numarul de ore a disciplinei : " << disciplina.get_ore() << std::endl;
            std::cout <<"Tipul disciplinei : " << disciplina.get_tip() << std::endl;
            std::cout <<"Cadrul didactic al disciplinei : " << disciplina.get_cadru_didactic() << std::endl;
            std::cout << std::endl;
        }
    }
}

void UI::filtrare_discipline_UI() {
    std::vector<Disciplina> lista_discipline_filtrata;
    std::cout << "Alege criteriul dupa care filtrezi lista : " << std::endl;
    std::cout << "1. Numar ore" << std::endl;
    std::cout << "2. Cadru didactic" << std::endl;
    int criteriu;
    std::cin >> criteriu;
    if (criteriu == 1) {
        lista_discipline_filtrata = service.filtrare_discipline(service.get_lista_discipline(), "numar ore");
    }
    else if (criteriu == 2) {
        lista_discipline_filtrata = service.filtrare_discipline(service.get_lista_discipline(), "cadru didactic");
    }
    else {
        std::cout << "Nu exista acest criteriu!" << std::endl;
        return ;
    }
    std::cout <<"Lista filtrata este : " << std::endl;
    for (const auto& disciplina : lista_discipline_filtrata) {
        std::cout <<"ID-ul disciplinei : " << disciplina.get_id() << std::endl;
        std::cout <<"Denumirea disciplinei : " << disciplina.get_denumire() << std::endl;
        std::cout <<"Numarul de ore a disciplinei : " << disciplina.get_ore() << std::endl;
        std::cout <<"Tipul disciplinei : " << disciplina.get_tip() << std::endl;
        std::cout <<"Cadrul didactic al disciplinei : " << disciplina.get_cadru_didactic() << std::endl;
        std::cout << std::endl;
    }
}

void UI::sortare_discipline_UI() {
    std::cout << "Alege criteriul dupa care filtrezi lista : " << std::endl;
    std::cout << "1. Denumire" << std::endl;
    std::cout << "2. Numar ore" << std::endl;
    std::cout << "3. Cadru didactic" << std::endl;
    std::cout << "4. Tip" << std::endl;
    int criteriu;
    std::cin >> criteriu;
    std::vector<Disciplina>& lista_discipline = service.get_lista_discipline();
    if (criteriu == 1) {
        service.sortare_discipline(lista_discipline, "denumire");
    }
    else if (criteriu == 2) {
        service.sortare_discipline(lista_discipline, "numar ore");
    }
    else if (criteriu == 3) {
        service.sortare_discipline(lista_discipline, "cadru didactic");
    }
    else if (criteriu == 4) {
        service.sortare_discipline(lista_discipline, "tip");
    }
    else {
        std::cout << "Nu exista acest criteriu!" << std::endl;
        return ;
    }
    std::cout <<"Lista sortata este : " << std::endl;
    for (const auto& disciplina : lista_discipline) {
        std::cout <<"ID-ul disciplinei : " << disciplina.get_id() << std::endl;
        std::cout <<"Denumirea disciplinei : " << disciplina.get_denumire() << std::endl;
        std::cout <<"Numarul de ore a disciplinei : " << disciplina.get_ore() << std::endl;
        std::cout <<"Tipul disciplinei : " << disciplina.get_tip() << std::endl;
        std::cout <<"Cadrul didactic al disciplinei : " << disciplina.get_cadru_didactic() << std::endl;
        std::cout << std::endl;
    }
}