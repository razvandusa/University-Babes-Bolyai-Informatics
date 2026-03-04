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
  struct sockaddr_in server;
  socklen_t l = sizeof(server);
  char buf[101];
  uint16_t nr_spatii;

  c = socket(AF_INET, SOCK_DGRAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  printf("Introdu sirul: ");
  fgets(buf, sizeof(buf), stdin);
  buf[strcspn(buf, "\n")] = '\0'; // elimina \n

  sendto(c, buf, strlen(buf) + 1, 0, (struct sockaddr *)&server, l);

  recvfrom(c, &nr_spatii, sizeof(nr_spatii), 0, (struct sockaddr *)&server, &l);
  nr_spatii = ntohs(nr_spatii);

  printf("Serverul a spus ca sunt %hu spatii in sir.\n", nr_spatii);

  close(c);
}
