/*
** EPITECH PROJECT, 2021
** B-NWP-400-RUN-4-1-myteams-dorian.beasse
** File description:
** accept_client
*/

#include "server.h"

void accept_client(serv_t *serv)
{
    client_t *client = client_create();

    client->fd = accept(serv->fd, (struct sockaddr *) &serv->sockaddr,
                                                                &serv->socklen);
    if (client->fd == -1)
        handle_error("accept");
    add_client(serv, client);
    dprintf(client->fd, "WELCOME\n");
}