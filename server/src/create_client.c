/*
** EPITECH PROJECT, 2021
** B-NWP-400-RUN-4-1-myteams-dorian.beasse
** File description:
** create_client
*/

#include "server.h"

client_t *client_create(void)
{
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL)
        handle_error("malloc");
    client->fd = -1;
    client->status = WAITING;
    client->ia = NULL;
    client->next = NULL;
    client->cmd_list = NULL;
    client->to_exec = NULL;
    client->arg = NULL;
    client->cmd_time = 0;
    client->launched_cmd = 0;
    return client;
}