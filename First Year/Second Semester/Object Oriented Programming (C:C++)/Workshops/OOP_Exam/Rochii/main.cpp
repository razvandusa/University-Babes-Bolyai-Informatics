#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "tests/tests_domain.h"
#include "tests/tests_repository.h"
#include "tests/tests_service.h"
#include "headers/gui.h"

int main(int argc, char *argv[]) {
    tests_domain();
    std::cout<<"Testele domain au trecut!\n";
    tests_repository();
    std::cout<<"Testele repository au trecut!\n";
    tests_service();
    std::cout<<"Testele service au trecut!\n";
    Repository repository("/Users/razvandusa/CLionProjects/Rochii/input.txt");
    Service service(repository);
    service.load_from_file();

    QApplication a(argc, argv);
    GUI gui(service);

    return QApplication::exec();
}
