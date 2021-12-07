/*
** EPITECH PROJECT, 2021
** B-NWP-400-RUN-4-1-myteams-dorian.beasse
** File description:
** destroy_client
*/

#include "server.h"

void client_destroy(client_t *client)
{
    if (client->fd != -1)
        close(client->fd);
    free(client);
}