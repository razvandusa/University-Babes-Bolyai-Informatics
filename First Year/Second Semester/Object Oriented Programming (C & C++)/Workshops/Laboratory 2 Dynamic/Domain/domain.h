#ifndef DOMAIN_H
#define DOMAIN_H
typedef struct
{
    char *tip;
    char *destinatie;
    char *data_plecare;
    int pret;
}date_oferta;

typedef struct
{
    int cp;
    int len;
    date_oferta *oferte;
}lista_de_oferte;

date_oferta* constructor_oferta(char *tip, char *destinatie, char *data_plecare, int pret);
/*      Functia creeaza o oferta cu datele de intrare date ca parametrii
 *      Parametrii :
 *      -tip (type:char) tipul calatoriei
 *      -destinatie (type:char) destinatia calatoriei
 *      -data_plecare (type:char) data de plecare
 *      -pret (type:char) pretul calatoriei
 *      @return : oferta creata
 */

void destructor_oferta(date_oferta *oferta);
/*      Functia elibereaza memoria stocata de variabila oferta
 *      Parametrii :
 *      -oferta (type:date_oferta) oferta careia memorii o eliberam
 *      @return : None
 */

lista_de_oferte* constructor_lista(int cp);
/*      Functia creeaza o lista pentru stocarea ofertelor cu capacitatea egala cu cp si lungimea egala cu 0
 *      @return : lista creata pentru stocarea ofertelor
 */

void destructor_lista(lista_de_oferte *lista);
/*      Functia elibereaza memoria stocata de variabila lista
 *      Parametrii :
 *      -lista (type:lista_de_oferte) lista a carei memorii o eliberam
 *      @return : None
 */

int oferta_valida(char *tip, char *destinatie, char *data_plecare, int pret);
/*      Functia verifica daca o oferta are datele de intrare valide
*       Parametrii :
 *      -tip (type:char) tipul calatoriei
 *      -destinatie (type:char) destinatia calatoriei
 *      -data_plecare (type:char) data de plecare
 *      -pret (type:char) pretul calatoriei
 *      @return : 0 daca datele sunt invalide
 *                1 daca datele sunt valide
 */

int oferte_egale(date_oferta *oferta_1, date_oferta *oferta_2);
/*      Functia compara doua oferte
 *      Parametrii :
 *      -oferta_1 (type:date_oferta) oferta pe care dorim sa o comparam
 *      -oferta_2 (type:date_oferta) oferta cu care dorim sa o comparam
 *      @return : 0 daca ofertele nu sunt egale
 *                1 daca ofertele sunt egale
 */
#endif //DOMAIN_H
