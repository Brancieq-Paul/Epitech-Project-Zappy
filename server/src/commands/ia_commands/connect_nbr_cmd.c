/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** connect_nbr_cmd
*/

#include "server.h"

void connect_nbr_cmd(client_t *client, serv_t *serv, char *arg)
{
    int connect_nbr = 0;

    for (teams_t *tmp = serv->serv_infos.team_list; tmp; tmp = tmp->next) {
        if (strcmp(client->ia->team_name, tmp->team_name) == 0) {
            connect_nbr = tmp->max_nb_client - tmp->nb_client;
            break;
        }
    }
    dprintf(client->fd, "%d\n", connect_nbr);
    (void)arg;
}