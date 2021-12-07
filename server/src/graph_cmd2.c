/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** graph_cmd2
*/

#include "server.h"

void plv_cmd(client_t *client, serv_t *serv, char *arg)
{
    (void)arg;
    for (client_t *tmp = serv->client; tmp; tmp = tmp->next) {
        if (tmp->status != IA) {
            dprintf(tmp->fd, "plv %d %d\n", client->ia->nb,
                                        client->ia->level);
        }
    }
}

void ppo_cmd(client_t *client, serv_t *serv, char *arg)
{
    (void)arg;
    for (client_t *tmp = serv->client; tmp; tmp = tmp->next) {
        if (tmp->status == GRAPHICAL)
            dprintf(tmp->fd, "ppo %d %d %d %d\n", client->ia->nb,
                    client->ia->coords.x, client->ia->coords.y,
                    client->ia->direction);
    }
}

void pnw_cmd(client_t *client, client_t *player)
{
    if (!client || !player || player->status != IA)
        return;
    dprintf(client->fd, "pnw %d %d %d %d %d %s\n", player->ia->nb,
    player->ia->coords.x, player->ia->coords.y, player->ia->direction,
    player->ia->level, player->ia->team_name);
}

void mct_cmd(client_t *client, serv_t *serv)
{
    for (int i = 0; i < serv->serv_infos.height; i++) {
        for (int j = 0; j < serv->serv_infos.width; j++) {
            dprintf(client->fd, "bct %d %d %d %d %d %d %d %d %d\n",
            j, i,
            serv->map[i][j]->content.nb_food,
            serv->map[i][j]->content.nb_linemate,
            serv->map[i][j]->content.nb_deraumere,
            serv->map[i][j]->content.nb_sibur,
            serv->map[i][j]->content.nb_mendiane,
            serv->map[i][j]->content.nb_phiras,
            serv->map[i][j]->content.nb_thystame);
        }
    }
}

void edi_cmd(client_t *client, int egg_nbr)
{
    dprintf(client->fd, "edi %d", egg_nbr);
}