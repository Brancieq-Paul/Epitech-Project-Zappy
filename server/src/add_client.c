/*
** EPITECH PROJECT, 2021
** B-NWP-400-RUN-4-1-myteams-dorian.beasse
** File description:
** add_client
*/

#include "server.h"

void add_client(serv_t *serv, client_t *client)
{
    if (serv->client == NULL) {
        serv->client = client;
    } else {
        client->next = serv->client;
        serv->client = client;
    }
    FD_SET(client->fd, &(serv->active_fds));
}