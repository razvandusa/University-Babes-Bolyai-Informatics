#include <QApplication>
#include <QPushButton>
#include <iostream>
#include "headers/gui.h"
#include "tests/tests_repository.h"
#include "tests/tests_service.h"

static std::string filename = "/Users/razvandusa/CLionProjects/Melodii/input.txt";

int main(int argc, char *argv[]) {
    tests_repository();
    std::cout << "Testele repository au trecut!" << std::endl;
    tests_service();
    std::cout << "Testele service au trecut!" << std::endl;

    Repository repository(filename);
    Service service(repository);
    service.load_from_file();

    QApplication a(argc, argv);
    Gui window(service);
    window.show();
    return QApplication::exec();
}
