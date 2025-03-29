#include "ui/ui.h"
#include "teste/test_all.h"

int main(void) {
    /*
1 1 Smith John 1 2 Johnson Emma 1 3 Brown Michael 1 4 Davis Olivia 1 5 Wilson William 1 6 Martinez Sophia 1 7 Taylor James 1 8 Anderson Isabella
    1 10 Smith John 1 21 Johnson Emma 1 31 Brown Michael 1 41 Davis Olivia 1 51 Wilson William 1 61 Martinez Sophia 1 71 Taylor James 1 81 Anderson Isabella
    */ // input participanti

//delete
    // 4 1 4 2 4 3 4 4 4 5 4 6 4 7 4 8 4 10 4 21 4 31

    /*rezolvare probleme
3 1 10 3 1 5 3 1 7 3 2 10 3 2 8 3 3 9 3 3 6  3 4 10 3 4 4 3 5 8 3 5 7 3 5 6 3 6 10 3 6 9 3 6 5 3 7 10 3 7 10 3 7 8 3 8 7 3 8 6 3 8 10 3 2 10 3 2 10 3 6 10 3 6 9 3 6 9
*/
    test_all();
    run_app();

}
