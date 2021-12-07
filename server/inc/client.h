/*
** EPITECH PROJECT, 2021
** zappy [WSL: Ubuntu]
** File description:
** client
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include <netinet/in.h>
#include "ia_client.h"

typedef struct serv_s serv_t;
typedef struct client_s client_t;

typedef enum auth_status_e {
    WAITING,
    GRAPHICAL,
    IA
}auth_status;

typedef struct command_list_s {
    char *command;
    struct command_list_s *next;
} cmd_list_t;

typedef struct client_s {
    int fd;
    struct sockaddr_in sockaddr;
    socklen_t socklen;
    fd_set readfds;
    auth_status status;
    double cmd_time;
    long launched_cmd;
    ia_client_t *ia;
    void (*to_exec)(client_t *client, serv_t *serv, char *arg);
    char *arg;
    cmd_list_t *cmd_list;
    struct client_s *next;
} client_t;

client_t *client_create(void);
void client_destroy(client_t *client);

#endif /* !CLIENT_H_ */
