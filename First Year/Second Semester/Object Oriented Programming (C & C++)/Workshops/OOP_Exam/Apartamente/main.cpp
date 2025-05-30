#include <iostream>
#include <QApplication>

#include "headers/GUI.h"
#include "headers/repository.h"
#include "headers/service.h"
#include "tests/tests_domain.h"
#include "tests/tests_repository.h"
#include "tests/tests_service.h"
#include "tests/tests_validator.h"

std::string filename = "/Users/razvandusa/CLionProjects/Apartamente/file.txt";

int main (int argc, char** argv) {
    tests_domain();
    std::cout<<"Testele domain au trecut!\n";
    tests_repository();
    std::cout<<"Testele repository au trecut!\n";
    tests_validator();
    std::cout<<"Testele validator au trecut!\n";
    tests_service();
    std::cout<<"Testele service au trecut!\n";

    Repository repository(filename);
    Service service(repository);
    service.load_from_file_service();

    QApplication a(argc, argv);
    GUI window(service);
    window.show();
    return a.exec();
}
