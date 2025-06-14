#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "headers/gui.h"
#include "tests/tests_repository.h"
#include "tests/tests_service.h"

int main(int argc, char *argv[]) {
    tests_repository();
    std::cout << "Testele repository au trecut!" << std::endl;
    tests_service();
    std::cout << "Testele service au trecut!" << std::endl;

    std::string filename = "/Users/razvandusa/CLionProjects/Produse/input.txt";
    Repository repository(filename);
    Service service(repository);

    service.load_from_file();

    QApplication a(argc, argv);
    Gui gui(service);
    return QApplication::exec();
}