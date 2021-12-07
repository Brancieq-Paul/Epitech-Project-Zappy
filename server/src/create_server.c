/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** create_server
*/

#include "server.h"
#include "commands.h"
#include "time_functions.h"

static void bind_listen(serv_t *serv)
{
    if ((bind(serv->fd, (struct sockaddr *) &serv->sockaddr,
        serv->socklen) == -1) || (listen(serv->fd, LISTEN_QUEUE)) == -1)
    handle_error("Bind");
}

serv_t *create_server(int port)
{
    serv_t *serv = malloc(sizeof(serv_t));
    int i = 1;

    serv->port = port;
    if ((serv->fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        handle_error("Server socket");
    if (setsockopt(serv->fd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int)) < 0)
        handle_error("Server setsocketopt");
    serv->sockaddr.sin_family = AF_INET;
    serv->sockaddr.sin_port = htons(serv->port);
    serv->sockaddr.sin_addr.s_addr = INADDR_ANY;
    serv->socklen = sizeof(serv->sockaddr);
    serv->is_run = true;
    serv->client = NULL;
    serv->eggs = NULL;
    FD_ZERO(&serv->active_fds);
    FD_ZERO(&serv->readfds);
    FD_SET(serv->fd, &serv->active_fds);
    bind_listen(serv);
    return serv;
}