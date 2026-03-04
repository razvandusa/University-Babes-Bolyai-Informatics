#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
  int c;
  /*
  Un server trebuie sa fie identificabil in retea, adica pe ce IP asculta si pe
  ce port primeste conexiuni. Aceste doua informatii (IP + port) se combina
  intr-o adresa de socket.
  */
  struct sockaddr_in server;
  char sir[100], raspuns[100];
  /*
  Cream un canal de comunicare in kernel (un obiect de tip socket). Sistemul de
  operare returneaza un descriptor catre acesta. AF_INET este familia de adrese
  cu care lucram, in cazul nostru IPv4, SOCK_STREAM este tipul de socket si
  spune ce fel de comunicare vrem sa avem, in cazul nostru TCP.
  */
  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  /*
  Umplem toate campurile din structura server cu valoarea 0 ca sa scapam de
  garbage values.
  */
  memset(&server, 0, sizeof(server));
  /*
  Numarul portului pe care ne vom conecta la server este 1234.
  Convertim un numar de 16 biti din forma folosita pe calculator in froma
  standard de retea folosind host to network short (htons).
  */
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  /*
  Convertim adresa IP "127.0.0.1" (localhost) intr-un numar in formatul retea si
  o salveaza in structura server.
  */
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  if (connect(c, (struct sockaddr *)&server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }

  printf("sir = ");
  // Citim sirul de la tastatura
  fgets(sir, sizeof(sir), stdin);
  sir[strcspn(sir, "\n")] = '\0';
  // Trimitem sirul catre server
  send(c, sir, strlen(sir) + 1, 0);
  // Primim sirul oglindit de la server
  recv(c, raspuns, sizeof(raspuns), 0);
  printf("Am primit de la server: %s\n", raspuns);
  close(c);
}