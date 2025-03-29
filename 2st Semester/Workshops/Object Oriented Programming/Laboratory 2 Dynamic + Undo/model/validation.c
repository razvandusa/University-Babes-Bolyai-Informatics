#include <ctype.h>
#include <string.h>
#include "validation.h"
int validare(Participant p) {
    if (p.id <= 0 || p.probleme_rezolvate < 0 || p.scor < 0)
        return 0;
    // for (int i = 0; i <= strlen(p.nume); i++) {
    //     if (isdigit(p.nume[i])) {
    //         return 0;
    //     }
    // }
    // for (int i = 0; i <= strlen(p.prenume); i++) {
    //     if (isdigit(p.prenume[i])) {
    //         return 0;
    //     }
    // }
    return 1;
}
