
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "util.h"

int id_selector() {
    int choice;
    while(1) {
        printf("ID:");
        if(scanf("%d", &choice) != 1) {
            printf("Input invalid\n");
            while (getchar() != '\n'){}
            continue;
        }
          if (choice <= 0) {
              printf("ID-ul trebuie sa fie numar intreg strict pozitiv\n");
              continue;
        }
        return choice;
    }
}

int choice_selector() {
    int choice;
    while(1) {
        printf("Optiune:");
        if(scanf("%d", &choice) != 1) {
            printf("Input invalid\n");
            while (getchar() != '\n'){}
            continue;
        }
        return choice;
    }

}

int punctaj_input() {
    int punctaj;
    while(1) {
        printf("Punctajul problemei rezolvate: ");
        if(scanf("%d", &punctaj) != 1) {
            printf("Input invalid\n");
            while (getchar() != '\n'){}
            continue;
        }
        if (punctaj < 1 || punctaj > 10) {
            printf("Punctajul problemei trebuie sa fie intre 1 si 10\n");
            while (getchar() != '\n'){}
            continue;
        }

        return punctaj;
    }
}

Participant nume_input() {
    Participant participant_input;
    char nume[30];

    while (1) {
        printf("Nume: ");
        if (scanf("%s", nume) != 1) {
            printf("Numele invalid\n");
            while (getchar() != '\n'){}
            continue;
        }
        int valid = 1;
        if (strlen(nume) > 20) {
            printf("Numele poate avea maxim 20 de caractere\n");
            while (getchar() != '\n'){}
            continue;
        }
        for (int i = 0; i <= (int)(strlen(nume))-1; i++) {
            // printf("%d\n", (int)strlen(nume));
            if (isdigit(nume[i])) {
                printf("Numele nu poate contine cifre\n");
                while (getchar() != '\n'){}
                valid = 0;
                break;
            }
        }
        if (valid)
            break;
    }
    strcpy(participant_input.nume, nume);
    return participant_input;
}

Participant prenume_input() {
    Participant participant_input;
    char prenume[30];

    while (1) {
        printf("Prenume: ");
        if (scanf("%s", prenume) != 1) {
            printf("Prenume invalid\n");
            while (getchar() != '\n'){}
            continue;
        }
        int valid = 1;
        if (strlen(prenume) > 20) {
            printf("Prenumele poate avea maxim 20 de caractere\n");
            while (getchar() != '\n'){}
            continue;
        }
        for (int i = 0; i <= (int)(strlen(prenume))-1; i++) {
            if (isdigit(prenume[i])) {
                printf("Prenumele nu poate contine cifre\n");
                while (getchar() != '\n'){}
                valid = 0;
                break;
            }
        }
        if (valid)
            break;
    }
    strcpy(participant_input.prenume, prenume);
    return participant_input;
}

int probleme_rezolvate_input() {
    int numar;
    while (1) {
        printf("Noul numar de probleme rezolvate : ");
        if (scanf("%d", &numar) != 1) {
            printf("Numar invalid\n");
            while (getchar() != '\n');
        } else if (numar < 0 ){
            printf("Numarul de probleme rezolvate trebuie sa fie pozitiv\n");
            while (getchar() != '\n'){}
        } else {
            break;
        }
    }
    return numar;
}

int scor_input() {
    int scor;
    while (1) {
        printf("Scor: ");
        if (scanf("%d", &scor) != 1) {
            printf("Scor invalid\n");
            while (getchar() != '\n');
        } else if (scor < 0){
            printf("Scorul trebuie sa fie pozitiv\n");
            while (getchar() != '\n'){}
        } else {
            break;
        }
    }
    return scor;
}

int ordine_input() {
    while (1) {
        char ordine[15];
        printf("Ordine (crescator/descrescator): ");
        if (scanf("%s", ordine) != 1) {
            printf("Input invalid\n");
            while (getchar() != '\n'){}
            continue;
        }
        if (strcmp(ordine, "crescator") == 0) {
            return 1;
        } else if (strcmp(ordine, "descrescator") == 0) {
            return 0;
        } else {
            printf("Ordine invalida (optiunile sunt crescator/descrescator)\n");
            while (getchar() != '\n'){}
        }
    }
}


Participant input_participant() {
    Participant participant_input;
    int id = id_selector();
    participant_input.id = id;
    strcpy(participant_input.nume, nume_input().nume);
    strcpy(participant_input.prenume, prenume_input().prenume);
    return participant_input;

}
