/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** graph_cmd5
*/

#include "server.h"

void graph_set_cmd(client_t *client, serv_t *serv, int nbr_player)
{
    inventory_t inv;
    client_t *graph;

    for (client_t *tmp = client; tmp; tmp = tmp->next)
        if (tmp->status == GRAPHICAL)
            graph = tmp;
    for (client_t *tmp = serv->client; tmp; tmp = tmp->next) {
        if (nbr_player == serv->client->ia->nb) {
            inv = serv->client->ia->inventory;
            dprintf(graph->fd, "pin %d %d %d %d %d %d %d %d %d\n",
            nbr_player, serv->client->ia->level, inv.nb_food, inv.nb_linemate,
            inv.nb_deraumere, inv.nb_sibur, inv.nb_mendiane, inv.nb_phiras,
                                                            inv.nb_thystame);
        }
    }
}

void graph_map_set_cmd(client_t *client, serv_t *serv, pos_t coords)
{
    char respond[50] = {};
    int i = 0;
    int j = 0;

    i = coords.y;
    j = coords.x;
    if (serv->map[i][j] == NULL)
        return;
    sprintf(respond, "bct %d %d %d %d %d %d %d %d %d\n",
    serv->serv_infos.height, serv->serv_infos.width,
    serv->map[i][j]->content.nb_food, serv->map[i][j]->content.nb_linemate,
    serv->map[i][j]->content.nb_deraumere, serv->map[i][j]->content.nb_sibur,
    serv->map[i][j]->content.nb_mendiane, serv->map[i][j]->content.nb_phiras,
    serv->map[i][j]->content.nb_thystame);
    for (client_t *tmp = client; tmp; tmp = tmp->next)
        if (tmp->status == GRAPHICAL)
            dprintf(tmp->fd, "%s", respond);
}

void pdi_cmd(serv_t *serv, int nb_player)
{
    for (client_t *tmp = serv->client; tmp; tmp = tmp->next)
        if (tmp->status == GRAPHICAL)
            dprintf(tmp->fd, "pdi %d\n", nb_player);
}

void enw_cmd(egg_t *egg, serv_t *serv, int player_nb)
{
    for (client_t *tmp = serv->client; tmp; tmp = tmp->next)
        if (tmp->status == GRAPHICAL)
            dprintf(tmp->fd, "enw %d %d %d %d\n", egg->nb, player_nb,
                egg->pos.x, egg->pos.y);
}

void pie_cmd(client_t *client, serv_t *serv, int incant_state)
{
    for (client_t *tmp = serv->client; tmp; tmp = tmp->next)
        if (tmp->status == GRAPHICAL)
            dprintf(tmp->fd, "pie %d %d %d\n", client->ia->coords.x,
                                        client->ia->coords.y, incant_state);
}