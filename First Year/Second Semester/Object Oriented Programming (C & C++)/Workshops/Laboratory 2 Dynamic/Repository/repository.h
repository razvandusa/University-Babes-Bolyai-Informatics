#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "../Domain/domain.h"
void adaugare_oferta(lista_de_oferte *lista, date_oferta *oferta);
/*      Functia adauga o oferta in lista de oferte
 *      Parametrii :
 *      -lista (type:lista_de_oferte *) lista in care dorim sa adaugam oferta
 *      -oferta (type:date_oferta) oferta pe care dorim sa o adaugam
 *      @return : None
 */

void actualizeaza_oferta(lista_de_oferte *lista, date_oferta *oferta, date_oferta *oferta_actualizata);
/*      Functia actualizeaza o oferta in lista de oferte
 *      Parametrii :
 *      -lista (type:lista_de_oferte *) lista in care dorim sa actualizam oferta
 *      -oferta (type:date_oferta) oferta pe care dorim sa o actualizam
 *      -oferta_actualizata (type:date_oferta) oferta cu datele care vrem sa actualizam oferta originala
 *      @return : None
 */

void sterge_oferta(lista_de_oferte *lista, date_oferta *oferta);
/*      Functia sterge o oferta din lista de oferte
 *      Parametrii :
 *      -lista (type:lista_de_oferte *) lista de oferte din care dorim sa stergem
 *      -oferta (type:date_oferta) oferta pe care dorim sa o stergem
 *      @return : None
 */

void swap_oferte(lista_de_oferte *lista, int first_ind, int second_ind);
/*      Functia da swap intre doua oferte din lista
 *      Parametrii :
 *      -lista (type:lista_de_oferte *) lista de oferte din care dorim sa facem
 *      -first_ind (type:int) indicele primei ofertei din lista caruia vrem sa ii dam swap
 *      -second_ind (type:int) indicele la a doua oferta din lista careia vrem sa ii dam swap cu prima
 *      @return : None
 */

int exista_oferta(lista_de_oferte *lista, date_oferta *oferta);
/*      Functia verifica daca exista o oferta in lista de oferte
 *      Parametrii :
 *      -lista (type:lista_de_oferte *) lista de oferte din care dorim sa verificam exista ofertei
 *      -oferta (type:date_oferta) oferta careia vrem sa ii verificam existenta
 *      @return : indicele pozitiei daca exista
 *                -1 altfel
 */
#endif //REPOSITORY_H
