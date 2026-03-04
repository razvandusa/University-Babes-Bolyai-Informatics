#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024
#define USERNAME_LEN 32
#define CHANNEL_NAME_LEN 32

typedef struct {
    struct sockaddr_in addr;
    int sockfd;
    char username[USERNAME_LEN];
    char channel[CHANNEL_NAME_LEN]; // canalul curent
} client_t;

client_t *clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex;

void send_channel(const char *message, int sender_fd, const char *channel_name) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i] &&
            clients[i]->sockfd != sender_fd &&
            strcmp(clients[i]->channel, channel_name) == 0) {
            send(clients[i]->sockfd, message, strlen(message), 0);
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void send_all(const char *message, int sender_fd) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i] && clients[i]->sockfd != sender_fd) {
            send(clients[i]->sockfd, message, strlen(message), 0);
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void send_private(const char *target, const char *message, const char *sender_name) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i] && strcmp(clients[i]->username, target) == 0) {
            char fullmsg[BUFFER_SIZE];
            snprintf(fullmsg, sizeof(fullmsg), "[PM de la %s]: %s\n", sender_name, message);
            send(clients[i]->sockfd, fullmsg, strlen(fullmsg), 0);
            pthread_mutex_unlock(&clients_mutex);
            return;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void add_client(client_t *cl) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (!clients[i]) {
            clients[i] = cl;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void remove_client(int sockfd) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i] && clients[i]->sockfd == sockfd) {
            clients[i] = NULL;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg) {
    client_t *cli = (client_t *)arg;
    char buffer[BUFFER_SIZE];
    char command[BUFFER_SIZE], target[USERNAME_LEN], msg[BUFFER_SIZE];

    while (1) {
        int len = recv(cli->sockfd, buffer, BUFFER_SIZE, 0);
        if (len <= 0) break;

        buffer[len] = '\0';
        buffer[strcspn(buffer, "\n")] = '\0';
        sscanf(buffer, "%s", command);

        if (strcmp(command, "/pm") == 0) {
            sscanf(buffer, "%*s %s %[^\n]", target, msg);
            send_private(target, msg, cli->username);
        } 
        else if (strcmp(command, "/join") == 0) {
            sscanf(buffer, "%*s %s", cli->channel);
            char joined[BUFFER_SIZE];
            snprintf(joined, sizeof(joined), "%s a intrat in canalul #%s\n", cli->username, cli->channel);
            send_all(joined, -1);
            send(cli->sockfd, "Ai intrat în canal.\n", 25, 0);
        }
        else if (strncmp(buffer, "@everyone ", 10) == 0) {
            snprintf(msg, sizeof(msg), "[%s catre toti]: %s\n", cli->username, buffer + 10);
            send_all(msg, cli->sockfd);
        }
        else if (strlen(cli->channel) > 0) {
            snprintf(msg, sizeof(msg), "[%s #%s]: %s\n", cli->username, cli->channel, buffer);
            send_channel(msg, cli->sockfd, cli->channel);
        }
        else {
            char err[] = "Comenzi: /pm <user> <msg> | /join <canal> | @everyone <msg>\n";
            send(cli->sockfd, err, strlen(err), 0);
        }
    }

    close(cli->sockfd);
    printf("%s s-a deconectat.\n", cli->username);
    remove_client(cli->sockfd);
    free(cli);
    pthread_detach(pthread_self());
    return NULL;
}

int main() {
    int server_fd;
    struct sockaddr_in server_addr, cli_addr;
    pthread_t tid;

    pthread_mutex_init(&clients_mutex, NULL);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 10);

    printf("Server pornit pe portul %d...\n", PORT);

    while (1) {
        socklen_t clilen = sizeof(cli_addr);
        int client_fd = accept(server_fd, (struct sockaddr *)&cli_addr, &clilen);

        client_t *cli = (client_t *)malloc(sizeof(client_t));
        cli->addr = cli_addr;
        cli->sockfd = client_fd;
        strcpy(cli->channel, ""); 

        recv(client_fd, cli->username, USERNAME_LEN, 0);
        cli->username[strcspn(cli->username, "\n")] = '\0';
        add_client(cli);

        printf("%s s-a conectat.\n", cli->username);
        pthread_create(&tid, NULL, handle_client, (void *)cli);
    }

    pthread_mutex_destroy(&clients_mutex);
    return 0;
}
