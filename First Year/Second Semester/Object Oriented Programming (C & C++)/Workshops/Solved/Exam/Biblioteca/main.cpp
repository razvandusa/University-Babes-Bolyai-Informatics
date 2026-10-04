#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "headers/gui.h"
#include "tests/tests_domain.h"
#include "tests/tests_repository.h"
#include "tests/tests_service.h"

int main(int argc, char *argv[]) {
    tests_domain();
    std::cout << "Testele domain au trecut!" << std::endl;
    tests_repository();
    std::cout << "Testele repository au trecut!" << std::endl;
    tests_service();
    std::cout << "Testele service au trecut!" << std::endl;
    Repository repository("/Users/razvandusa/CLionProjects/Biblioteca/file.txt");
    Service service(repository);
    service.load_from_file();
    QApplication a(argc, argv);
    GUI window(service);
    window.show();
    return QApplication::exec();
}
