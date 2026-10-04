#include "tests_utils.h"

std::string filename = "/Users/razvandusa/CLionProjects/Rochii/tests/tests_input.txt";

void loading_file(const std::string& filename) {
    std::ofstream fout(filename);
    fout <<"1,GUCCI WOOL DRESS,S,9000,True\n"
            "2,PRADA SILK GOWN,M,12000,True\n"
            "3,CHANEL BLACK DRESS,S,10500,False\n"
            "4,DIOR SUMMER DRESS,L,9800,True\n"
            "5,ARMANI RED DRESS,M,8500,True\n"
            "6,VALENTINO COCKTAIL DRESS,XS,11000,False\n"
            "7,SAINT LAURENT EVENING DRESS,L,12500,True\n"
            "8,BALENCIAGA MINI DRESS,S,7900,True\n"
            "9,LOUIS VUITTON MAXI DRESS,M,13000,False\n"
            "10,CELINE CASUAL DRESS,L,7200,True";
}