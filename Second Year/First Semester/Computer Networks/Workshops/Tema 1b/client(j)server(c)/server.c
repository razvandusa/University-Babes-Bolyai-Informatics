#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void deservire_client(int c) {
  char buf[100];
  recv(c, buf, sizeof(buf), 0);

  buf[strcspn(buf, "\n")] = '\0';

  int n = strlen(buf);
  for (int i = 0; i < n / 2; i++) {
    char temp = buf[i];
    buf[i] = buf[n - i - 1];
    buf[n - i - 1] = temp;
  }
  strcat(buf, "\n");
  send(c, buf, strlen(buf), 0);
  close(c);
}

int main() {
  int s;
  struct sockaddr_in server, client;
  socklen_t l;
  int c;

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
    c = accept(s, (struct sockaddr *)&client, &l);
    if (c < 0) {
      continue;
    }
    printf("S-a conectat un client.\n");

    pid_t pid = fork();
    if (pid < 0) {
      close(c);
      continue;
    }
    if (pid == 0) {
      deservire_client(c);
      return 0;
    } else {
      close(c);
    }
  }
}