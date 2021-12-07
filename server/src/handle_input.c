/*
** EPITECH PROJECT, 2021
** B-NWP-400-RUN-4-1-myteams-dorian.beasse
** File description:
** handle_input
*/

#include "server.h"

static int handle_input(serv_t *server, client_t *client)
{
    ssize_t bytes = 0;
    char buf[BUF_SIZE] = "\0";

    memset(buf, 0, BUF_SIZE);
    bytes = read(client->fd, buf, BUF_SIZE);
    FD_CLR(client->fd, &(server->readfds));
    if (bytes == -1) {
        handle_error("read");
    } else if (bytes == 0) {
        remove_client(server, client);
    } else {
        buf[bytes] = 0;
        handle_buffer(server, client, strdup(buf));
    }
    return 0;
}

int handle_inputs(serv_t *serv)
{
    for (client_t *client = serv->client ; client ; client = client->next)
        if (FD_ISSET(client->fd, &(serv->readfds)))
            handle_input(serv, client);
    return 0;
}