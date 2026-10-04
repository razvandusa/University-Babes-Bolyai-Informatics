#ifndef SERVICE_H
#define SERVICE_H
#include "../Repository/repository.h"
int adaugare_oferta_service(lista_de_oferte *lista, char *tip, char *destinatie, char *data_plecare, int pret);
/*      Functia adauga o oferta in lista de oferte si valideaza datele de intrare
 *      Parametrii :
 *      -Lista_de_oferte (type:lista_de_oferte *) lista in care dorim sa adaugam oferta
 *       Parametrii :
 *      -tip (type:char) tipul calatoriei
 *      -destinatie (type:char) destinatia calatoriei
 *      -data_plecare (type:char) data de plecare
 *      -pret (type:char) pretul calatoriei
 *      @return : 0 daca a esuat adaugarea ofertei in lista
 *                1 daca s-a reusit adaugarea ofertei in lista
 */

int actualizare_oferta_service(lista_de_oferte *lista, date_oferta *oferta, date_oferta *oferta_actualizata);
/*      Functia actualizeaza o oferta in lista de oferte si verifica ca aceasta sa existe
 *      Parametrii:
 *      -lista (type:lista_de_oferte *) lista in care dorim sa actualzam oferta
 *      -oferta (type:date_oferta) oferta a carei date dorim sa le actualizam
 *      -oferta_actualizata (type:date_oferta) oferta cu datele actualizate
 *      @return : 0 daca a esuat actualizarea ofertei din lista
 *                1 daca s-a reusit actualizarea ofertei din lista
 */

int sterge_oferta_service(lista_de_oferte *lista, date_oferta *oferta);
/*      Functia sterge o oferta din lista de oferte si verifica ca aceasta sa existe
 *      Parametrii:
 *      -lista (type:lista_de_oferte *) lista din care dorim sa stergem oferta
 *      -oferta (type:date_oferta) oferta pe care dorim sa o stergem
 *      @return : 0 daca a esuat stergerea ofertei din lista
 *                1 daca s-a reusit stergerea ofertei din lista
 */

lista_de_oferte* ordonare_oferte_criteriu_ordine(lista_de_oferte *lista, char *criteriu ,char *ordine);
/*      Functia ordoneaza ofertele din lista de oferte dupa criteriul precizat si dupa ordine
 *      Parametrii:
 *      -lista(type:lista_de_oferte) lista pe care dorim sa o ordonam
 *      @return : lista de oferte ordonata
 */

lista_de_oferte *filtrare_oferte(lista_de_oferte *lista, char *criteriu, int (*functie_comparare)(lista_de_oferte *,int,int));
/*      Functia filtreaza ofertele din lista de oferte dupa criteriu
 *      Parametrii:
 *      -lista(type:lista_de_oferte) lista pe care dorim sa o filtram
 *      @return : lista de oferte filtrata
 */

int functie_comparare_destinatii(lista_de_oferte *lista, int i, int j);
/*      Functia compara doua destinatii din lista
 *      Parametrii:
 *      -lista(type:lista_de_oferte) lista a caror destinatii dorim sa le comparam
 *      -i: indicele primei destinatii pe care dorim sa o comparam
 *      -j: indicele la a doua destinatie pe care dorim sa o comparam
 *      @return : 0 daca sunt egale
 *                > 0 daca prima destinatie are stringul mai mare
 *                < 0 daca prima destinatie are stringul mai mic
 */
#endif //SERVICE_H
