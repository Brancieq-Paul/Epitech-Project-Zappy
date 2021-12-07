/*
** EPITECH PROJECT, 2021
** B-NWP-400-RUN-4-1-myteams-dorian.beasse
** File description:
** remove_client
*/

#include "server.h"

void remove_client(serv_t *server, client_t *client)
{
    client_t *previous = NULL;
    teams_t *tmp = server->serv_infos.team_list;

    while (tmp) {
        if (!client->ia || strcmp(tmp->team_name, client->ia->team_name) == 0)
            tmp->nb_client--;
        tmp = tmp->next;
    }
    if (server->client == client) {
        server->client = server->client->next;
    } else {
        previous = server->client;
        while (previous->next != client)
            previous = previous->next;
        previous->next = previous->next->next;
    }
    FD_CLR(client->fd, &(server->active_fds));
    client_destroy(client);
}