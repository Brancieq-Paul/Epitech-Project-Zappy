/*
** EPITECH PROJECT, 2021
** B-NWP-400-RUN-4-1-myteams-dorian.beasse
** File description:
** destroy_serv
*/

#include "server.h"

void server_destroy(serv_t *serv)
{
    for (client_t *client = serv->client ; client ; client = client->next)
        client_destroy(client);
    close(serv->fd);
    free(serv);
}
