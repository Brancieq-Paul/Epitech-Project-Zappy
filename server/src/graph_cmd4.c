/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** graph_cmd4
*/

#include "server.h"
void fill_str_player(char *str_player, client_t *client, serv_t *serv,
                                                    incantation_t needed);

void tna_cmd(client_t *client, serv_t *serv, char *arg)
{
    for (teams_t *tmp = serv->serv_infos.team_list; tmp; tmp = tmp->next)
        if (tmp->team_name != 0) {
            for (client_t *graph = serv->client; graph; graph = graph->next)
                if (graph->status == GRAPHICAL)
                    dprintf(client->fd, "tna %s\n", tmp->team_name);
        }
    (void)arg;
}

void bct_cmd(client_t *client, serv_t *serv, char *arg)
{
    char *xstr = strtok(arg, " ");
    char *ystr = strtok(NULL, "\0");
    int x = atoi(xstr);
    int y = atoi(ystr);

    (void)arg;
    dprintf(client->fd, "bct %d %d %d %d %d %d %d %d %d\n",
    x, y,
    serv->map[y][x]->content.nb_food, serv->map[y][x]->content.nb_linemate,
    serv->map[y][x]->content.nb_deraumere, serv->map[y][x]->content.nb_sibur,
    serv->map[y][x]->content.nb_mendiane, serv->map[y][x]->content.nb_phiras,
    serv->map[y][x]->content.nb_thystame);
}

void msz_cmd(client_t *client, serv_t *serv, char *arg)
{
    char height[20] = {};
    char width[20] = {};

    (void)arg;
    sprintf(height, "%d", serv->serv_infos.height);
    sprintf(width, "%d", serv->serv_infos.width);
    dprintf(client->fd, "msz %s %s\n", height, width);
}

void pic_cmd(client_t *client, serv_t *serv)
{
    (void)serv;
    if (client->status != IA || !client->ia->is_elevating)
        return;
    for (client_t *graph = serv->client; graph; graph = graph->next) {
        if (graph->status == GRAPHICAL) {
            dprintf(graph->fd, "pic %d %d %d %d\n", client->ia->coords.x,
                    client->ia->coords.y, client->ia->level, client->ia->nb);
        }
    }
}