/*
** EPITECH PROJECT, 2021
** myteams [WSL: Ubuntu]
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <sys/queue.h>
#include "client.h"
#include "server_infos.h"
#include "map.h"
#include "commands.h"
#include "egg.h"

#define RESOURCES_REGEN_TIME 20
#define EXIT_ERROR 84
#define LISTEN_QUEUE 10
#define HELP_MESSAGE "USAGE: ./zappy_server -p port -x width -y height -n name1\
name2 ... -c clientsNb -f freq\n\
port is the port number\n\
width is the width of the world\n\
height is the height of the world\n\
nameX is the name of the team X\n\
clientsNb is the number of authorized clients per team\n\
freq is the reciprocal of time unit for execution of actions\n"

#define BUF_SIZE 1024
#define handle_error(msg) \
    do {write(1, msg, strlen(msg)); exit(EXIT_ERROR);} while (0)

typedef struct serv_s {
    int port;
    int fd;
    struct sockaddr_in sockaddr;
    socklen_t socklen;
    fd_set readfds;
    fd_set active_fds;
    bool is_run;
    map_t map;
    cmds_t **ia_cmds;
    cmds_t **graph_cmds;
    egg_t *eggs;
    server_info_t serv_infos;
    long ressources_regen_time;
    client_t *client;
} serv_t;

serv_t *create_server(int port);
void remove_client(serv_t *server, client_t *client);
void add_client(serv_t *server, client_t *client);
client_t *client_create(void);
void client_destroy(client_t *client);
void accept_client(serv_t *serv);
void server_destroy(serv_t *serv);
void server_loop(serv_t *serv);
void accept_client(serv_t *serv);
int handle_inputs(serv_t *serv);
void handle_buffer(serv_t *serv, client_t *client, char *buf);
void error_handling(int ac, char **av);
server_info_t get_server_info(char **av);
void send_responses(serv_t *serv);
struct timeval *get_timeout(client_t *client);
void graphical_management(char *cmd_line, serv_t *serv, client_t *client);
ia_client_t *create_ia_client(int nb, teams_t *team, serv_t *serv);
void life_management(serv_t *serv);
egg_t *egg_is_avaible(egg_t *eggs, char *team_name);
void eggs_management(serv_t *serv);
void ressources_management(serv_t *serv);
void send_events_new_ia(client_t *ia, serv_t *serv);

#endif /* !SERVER_H_ */
