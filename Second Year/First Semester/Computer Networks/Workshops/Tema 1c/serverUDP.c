#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int s;
  struct sockaddr_in server, client;
  socklen_t l = sizeof(client);
  char buf[101];
  uint16_t nr_spatii;

  s = socket(AF_INET, SOCK_DGRAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;

  if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }

  printf("Serverul asteapta mesaje...\n");

  recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *)&client, &l);

  // numaram spatiile
  nr_spatii = 0;
  for (int i = 0; i < strlen(buf); i++)
    if (buf[i] == ' ')
      nr_spatii++;

  nr_spatii = htons(nr_spatii);
  sendto(s, &nr_spatii, sizeof(nr_spatii), 0, (struct sockaddr *)&client, l);

  printf("Am trimis inapoi %hu spatii.\n", ntohs(nr_spatii));
  close(s);
}