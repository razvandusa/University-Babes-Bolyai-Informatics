#include "../headers/ui.h"
#include "../headers/validator.h"
#include <iostream>

void UI::menu() {
    std::cout << "\nAlege optiunea : \n";
    std::cout << "1. Adauga disciplina\n";
    std::cout << "2. Sterge disciplina\n";
    std::cout << "3. Modifica disciplina\n";
    std::cout << "4. Afisare discipline\n";
    std::cout << "5. Cauta disciplina\n";
    std::cout << "6. Filtreaza discipline\n";
    std::cout << "7. Sorteaza discipline\n";
    std::cout << "8. Gestioneaza contract\n";
    std::cout << "9. Afisare raport\n";
    std::cout << "10. Undo\n";
    std::cout << "0. Exit\n";
}

void UI::menu_contract() {
    std::cout << "\nAlege optiunea : \n";
    std::cout << "1. Adauga disciplina in contract\n";
    std::cout << "2. Goleste contractul\n";
    std::cout << "3. Afisare contract\n";
    std::cout << "4. Genereaza contract\n";
    std::cout << "5. Exporta contract\n";
    std::cout << "0. Exit\n";
}

void UI::run() {
    bool run = true;
    std::string input;
    while (run) {
        menu();
        std::getline(std::cin, input);
        try {
            int optiune = std::stoi(input);
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
                    find_disciplina_UI();
                break;
                case 6:
                    filtrare_discipline_UI();
                    std::cin.ignore();
                break;
                case 7:
                    sortare_discipline_UI();
                    std::cin.ignore();
                break;
                case 8:
                    gestionare_contract_UI();
                break;
                case 9:
                    raport_UI();
                break;
                case 10:
                    undo_UI();
                break;
                default:
                    std::cout << "Optiune invalida!\n";
            }
        } catch (const std::invalid_argument&) {
            std::cout << "Optiunea trebuie sa fie un numar intreg!\n";
        }
    }
}

void UI::add_disciplina_UI() {
    std::string id_string;
    std::string denumire;
    std::string ore_string;
    std::string tip;
    std::string cadru_didactic;
    std::cout << "Scrie id-ul disciplinei pe care o adaugi : ";
    std::getline(std::cin, id_string);
    int id;
    try {
        id = Validator::conversie_valida(id_string);
    } catch (const NotValid& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
        return;
    }
    std::cout << "Scrie denumirea disciplinei pe care o adaugi : ";
    std::getline(std::cin, denumire);
    std::cout << "Scrie numarul de ore a disciplinei pe care o adaugi : ";
    std::getline(std::cin, ore_string);
    int ore;
    try {
        ore = Validator::conversie_valida(ore_string);
    } catch (const NotValid& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
        return;
    }
    std::cout << "Scrie tipul disciplinei pe care o adaugi : ";
    std::getline(std::cin, tip);
    std::cout << "Scrie cadrul didactic corespunzator disciplinei pe care o adaugi : ";
    std::getline(std::cin, cadru_didactic);
    try {
        std::string mesaj = service.add_disciplina(id, denumire, ore, tip, cadru_didactic);
        std::cout << mesaj;
    } catch (const NotValid& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
    } catch (const AlreadyExisting& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
    }
}

void UI::add_disciplina_contract_UI() {
    std::string id_string;
    std::cout << "Scrie id-ul disciplinei pe care o adaugi : ";
    std::getline(std::cin, id_string);
    int id;
    try {
        id = Validator::conversie_valida(id_string);
    } catch (const NotValid& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
        return;
    }
    try {
        contract.add_disciplina_contract(id,service);
        std::cout << "Numarul total de discipline din contract este : " << contract.get_lista_discipline_contract().size() << std::endl;
    } catch (const NotValid& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
    } catch (const AlreadyExisting& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
    }
}

void UI::remove_disciplina_UI() {
    std::string id_string;
    std::cout << "Scrie id-ul disciplinei pe care o stergi : ";
    std::getline(std::cin, id_string);
    int id;
    try {
        id = Validator::conversie_valida(id_string);
    } catch (const NotValid& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
        return;
    }
    try {
        std::string mesaj = service.remove_disciplina(id);
        std::cout << mesaj;
    } catch (const NotExisting& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
    }
}

void UI::update_disciplina_UI() {
    std::string id_string;
    std::string new_denumire;
    std::string new_ore_string;
    std::string new_tip;
    std::string new_cadru_didactic;
    std::cout << "Scrie id-ul disciplinei pe care o modifici : ";
    std::getline(std::cin, id_string);
    int id;
    try {
        id = Validator::conversie_valida(id_string);
    } catch (const NotValid& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
        return;
    }
    std::cout << "Scrie noua denumirea a disciplinei pe care o modifici : ";
    std::getline(std::cin, new_denumire);
    std::cout << "Scrie numarul nou de ore a disciplinei pe care o modifici : ";
    std::getline(std::cin, new_ore_string);
    int new_ore;
    try {
        new_ore = Validator::conversie_valida(new_ore_string);
    } catch (const NotValid& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
        return;
    }
    std::cout << "Scrie tipul nou a disciplinei pe care o modifici : ";
    std::getline(std::cin, new_tip);
    std::cout << "Scrie noul cadrul didactic corespunzator disciplinei pe care o modifici : ";
    std::getline(std::cin, new_cadru_didactic);
    try {
        std::string mesaj = service.update_disciplina(id, new_denumire, new_ore, new_tip, new_cadru_didactic);
        std::cout << mesaj;
    } catch (const NotValid& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
    } catch (const NotExisting& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
    }
}

void UI::find_disciplina_UI() {
    std::string id_string;
    std::cout << "Scrie id-ul disciplinei pe care o cauti : ";
    std::getline(std::cin, id_string);
    int id;
    try {
        id = Validator::conversie_valida(id_string);
    } catch (const NotValid& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
        return;
    }
    try {
        Disciplina& disciplina = service.find_disciplina(id);
        std::cout <<"ID-ul disciplinei : " << disciplina.get_id() << std::endl;
        std::cout <<"Denumirea disciplinei : " << disciplina.get_denumire() << std::endl;
        std::cout <<"Numarul de ore a disciplinei : " << disciplina.get_ore() << std::endl;
        std::cout <<"Tipul disciplinei : " << disciplina.get_tip() << std::endl;
        std::cout <<"Cadrul didactic al disciplinei : " << disciplina.get_cadru_didactic() << std::endl;
        std::cout << std::endl;
    } catch (const NotExisting& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
    }
}

void UI::show_list_UI() {
    std::vector<Disciplina>& lista_discipline = service.get_lista_discipline();
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

void UI::show_list_contract_UI() {
    std::vector<Disciplina>& lista_discipline = contract.get_lista_discipline_contract();
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
        std::cout << "Numarul total de discipline din contract este : " << contract.get_lista_discipline_contract().size() << std::endl;
    }
}

void UI::filtrare_discipline_UI() {
    std::vector<Disciplina>& lista_discipline = service.get_lista_discipline();
    std::vector<Disciplina> lista_discipline_filtrata;
    std::cout << "Alege criteriul dupa care filtrezi lista : " << std::endl;
    std::cout << "1. Numar ore" << std::endl;
    std::cout << "2. Cadru didactic" << std::endl;
    int camp_filtrare;
    std::string criteriu;
    std::cin >> camp_filtrare;
    if (camp_filtrare == 1) {
        std::cout << "Scrie numarul minim de ore : " << std::endl;
        std::cin >> criteriu;
        try {
            std::stoi(criteriu);
        } catch (NotValid& e) {
            std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
            return ;
        }
        lista_discipline_filtrata = service.filtrare_discipline(lista_discipline, "numar ore", criteriu);
        if (lista_discipline_filtrata.empty()) {
            std::cout << "Lista filtrata este goala!" << std::endl;
        }
        else {
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
    }
    else if (camp_filtrare == 2) {
        std::cout << "Scrie cadrul didactic : " << std::endl;
        std::cin.ignore();
        std::getline(std::cin, criteriu);
        lista_discipline_filtrata = service.filtrare_discipline(lista_discipline, "cadru didactic", criteriu);
        if (lista_discipline_filtrata.empty()) {
            std::cout << "Lista filtrata este goala!" << std::endl;
        }
        else {
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
    }
    else {
        std::cout << "Nu exista acest criteriu!" << std::endl;
    }
}

void UI::sortare_discipline_UI() {
    std::cout << "Alege criteriul dupa care sortezi lista : " << std::endl;
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

void UI::generate_contract_UI() {
    std::string number_to_generate_string;
    std::cout << "Introduce numarul de discipline pe care vrei sa le contina contractul : ";
    std::getline(std::cin, number_to_generate_string);
    int number_to_generate;
    try {
        number_to_generate = Validator::conversie_valida(number_to_generate_string);
    } catch (const NotValid& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
        return;
    }
    try {
        contract.generate_contract(number_to_generate,service);
        std::cout << "Numarul total de discipline din contract este : " << contract.get_lista_discipline_contract().size() << std::endl;
    } catch (const NotExisting& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
    } catch (const NotValid& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
    }
}

void UI::export_contract_UI() {
    std::string file_name;
    std::cout << "Introduce numele fisierului in care vrei sa exporti : ";
    std::cin >> file_name;
    try {
        contract.export_contract(file_name);
    } catch (const NotValid& e) {
        std::cout << "\033[31m" << e.get_message() << "\033[0m" << '\n';
    }
    std::cin.ignore();
}


void UI::gestionare_contract_UI() {
    bool run = true;
    std::string input;
    while (run) {
        menu_contract();
        std::getline(std::cin, input);
        try {
            int optiune = stoi(input);
            switch (optiune) {
                case 0:
                    run = false;
                break;
                case 1:
                    add_disciplina_contract_UI();
                break;
                case 2:
                    contract.clear_contract();
                std::cout << "Numarul total de discipline din contract este : " << contract.get_lista_discipline_contract().size() << std::endl;
                break;
                case 3:
                    show_list_contract_UI();
                break;
                case 4:
                    generate_contract_UI();
                break;
                case 5:
                    export_contract_UI();
                break;
                default:
                    std::cout << "Optiune invalida!\n";
            }
        } catch (const std::invalid_argument&) {
            std::cout << "Optiunea trebuie sa fie un numar intreg!\n";
        }
    }
}

void UI::raport_UI() {
    std::map<std::string, DTO> raport = service.raport_discipline(service.get_lista_discipline());

    for (const auto& [tip, dto] : raport) {
        std::cout << "Tip: " << tip << " | Numar aparitii: " << dto.get_aparitii() << '\n';
    }
}

void UI::undo_UI() {
    try {
        service.undo();
    } catch (const std::runtime_error& e) {
        std::cout << "\033[31m" << e.what() << "\033[0m" << '\n';
    }
}