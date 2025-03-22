#ifndef UI_H
#define UI_H
#include "../Service/service.h"
void run_tests();
/*      Functia ruleaza toate testele
 *      @return : eroare daca a picat un test
 *                None , altfel
 */

void print_oferta(date_oferta *oferta);
/*      Functia printeaza datele ofertei
 *      Parametrii :
 *      -oferta (type:date_oferta) oferta carei date dorim sa le afisam
 *      @return : None
 */

void print_lista_de_oferte(lista_de_oferte *lista);
/*      Functia printeaza toate ofertele din lista
 *      Parametrii :
 *      -lista (type:lista_de_oferte) lista a carei elemente dorim sa le afisam
 *      @return : None
 */

void run();
/*      Functia ruleaza programul
 *      @return : None
 */

#endif //UI_H
