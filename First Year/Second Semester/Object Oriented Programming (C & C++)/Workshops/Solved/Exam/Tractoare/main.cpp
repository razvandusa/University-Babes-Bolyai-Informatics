#include <iostream>
#include <QApplication>

#include "headers/gui.h"
#include "tests/tests_repository.h"
#include "tests/tests_service.h"

int main(int argc, char** argv) {
    tests_repository();
    std::cout << "Tests repository passed!" << std::endl;
    tests_service();
    std::cout << "Tests service passed!" << std::endl;

    Repository repo("/Users/razvandusa/CLionProjects/Tractoare/input.txt");
    Service service(repo);
    service.load_from_file();

    QApplication app(argc, argv);
    Gui window(service);
    return app.exec();
}
