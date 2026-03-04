#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define USERNAME_LEN 32

int sockfd;
char username[USERNAME_LEN];

void *recv_msg(void *arg) {
    char buffer[BUFFER_SIZE];
    while (1) {
        int len = recv(sockfd, buffer, BUFFER_SIZE, 0);
        if (len <= 0) break;
        buffer[len] = '\0';
        printf("%s", buffer);
    }
    return NULL;
}

int main() {
    struct sockaddr_in serv_addr;
    pthread_t recv_thread;
    char message[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Introdu username-ul: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';
    send(sockfd, username, strlen(username), 0);

    printf("Conectat ca %s\n", username);
    printf("Comenzi disponibile:\n");
    printf("  /pm <user> <mesaj>\n");
    printf("  /join <canal>\n");
    printf("  @everyone <mesaj>\n");
    printf("  (mesaj simplu = trimis doar in canalul curent)\n\n");

    pthread_create(&recv_thread, NULL, recv_msg, NULL);

    while (1) {
        fgets(message, BUFFER_SIZE, stdin);
        send(sockfd, message, strlen(message), 0);
    }

    close(sockfd);
    return 0;
}
