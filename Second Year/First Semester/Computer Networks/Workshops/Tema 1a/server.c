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
  int c;
  socklen_t l;

  s = socket(AF_INET, SOCK_STREAM, 0);
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

  listen(s, 5);

  l = sizeof(client);
  memset(&client, 0, sizeof(client));

  while (1) {
    char buf[100];
    c = accept(s, (struct sockaddr *)&client, &l);
    printf("S-a conectat un client.\n");
    // deservirea clientului
    recv(c, buf, sizeof(buf), 0);
    printf("Am primit de la client: %s\n", buf);

    int n = strlen(buf);
    for (int i = 0; i < n / 2; i++) {
      char temp = buf[i];
      buf[i] = buf[n - i - 1];
      buf[n - i - 1] = temp;
    }
    send(c, buf, strlen(buf) + 1, 0);
    close(c);
    // sfarsitul deservirii clientului;
  }
}