/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** graph_cmd3
*/

#include "server.h"

void seg_cmd(client_t *client, char *team_name)
{
    dprintf(client->fd, "seg %s\n", team_name);
}

void sbp_cmd(client_t *client, serv_t *serv, char *arg)
{
    dprintf(client->fd, "sbp\n");
    (void)arg;
    (void)serv;
}

void pex_cmd(serv_t *serv, int nb_player)
{
    send_graph_cmd(serv, nb_player, "pex %d\n");
}

void smg_cmd(client_t *client, char *message)
{
    dprintf(client->fd, "smg %s", message);
}

void sgt_cmd(client_t *client, serv_t *serv, char *arg)
{
    (void)arg;
    dprintf(client->fd, "sgt %d\n", serv->serv_infos.freq);
}