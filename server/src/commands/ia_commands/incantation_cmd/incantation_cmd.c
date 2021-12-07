/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** incantation_cmd
*/

#include "server.h"

static const incantation_t INC[] = {
    { 1, 1, 1, 0, 0, 0, 0, 0 },
    { 2, 2, 1, 1, 1, 0, 0, 0 },
    { 3, 2, 2, 0, 1, 0, 2, 0 },
    { 4, 4, 1, 1, 2, 0, 1, 0 },
    { 5, 4, 1, 2, 1, 3, 0, 0 },
    { 6, 6, 1, 2, 3, 0, 1, 0 },
    { 7, 6, 2, 2, 2, 2, 2, 1 }
};
static void send_msg(incantation_t needed, client_t *clients, tile_t *tile,
                                                                    char *msg);
static tile_t *delete_ressources(tile_t *tile, incantation_t needed);
static client_t *add_level(client_t *clients, incantation_t needed, tile_t *t);
static void send_lvl_msg(incantation_t needed, client_t *clients, tile_t *tile,
                                                                serv_t *serv);

void incantation_cmd(client_t *client, serv_t *serv, char *arg)
{
    tile_t *tile = serv->map[client->ia->coords.y][client->ia->coords.x];
    int  client_lvl = client->ia->level;

    if (!incantation_checks(client, serv, false)) {
        send_msg(INC[client_lvl - 1], serv->client, tile, strdup("ko"));
        pie_cmd(client, serv, 0);
        return;
    }
    tile = delete_ressources(tile, INC[client_lvl - 1]);
    serv->client = add_level(serv->client, INC[client_lvl - 1], tile);
    serv->map[client->ia->coords.x][client->ia->coords.x] = tile;
    pie_cmd(client, serv, 1);
    send_lvl_msg(INC[client_lvl], serv->client, tile, serv);
    (void)arg;
}

static tile_t *delete_ressources(tile_t *tile, incantation_t needed)
{
    tile->content.nb_deraumere -= needed.deraumere;
    tile->content.nb_linemate -= needed.linemate;
    tile->content.nb_mendiane -= needed.mendiane;
    tile->content.nb_phiras -= needed.phiras;
    tile->content.nb_sibur -= needed.sibur;
    tile->content.nb_thystame -= needed.thystame;
    return tile;
}

static client_t *add_level(client_t *clients, incantation_t needed, tile_t *t)
{
    client_t *tmp = clients;

    while (tmp) {
        if (tmp->status == IA && tmp->ia->coords.y == t->coords.y &&
            tmp->ia->coords.x == t->coords.x &&
            tmp->ia->level == needed.level)
            tmp->ia->level++;
        tmp = tmp->next;
    }
    return clients;
}

static void send_msg(incantation_t needed, client_t *clients, tile_t *tile,
                                                                    char *msg)
{
    client_t *tmp = clients;

    while (tmp) {
        if (tmp->status == IA && tmp->ia->coords.y == tile->coords.y &&
            tmp->ia->coords.x == tile->coords.x &&
            tmp->ia->level == needed.level)
            dprintf(tmp->fd, "%s\n", msg);
        tmp = tmp->next;
    }
}

static void send_lvl_msg(incantation_t needed, client_t *clients, tile_t *tile,
                                                                serv_t *serv)
{
    client_t *tmp = clients;

    while (tmp) {
        if (tmp->status == IA && tmp->ia->coords.y == tile->coords.y &&
            tmp->ia->coords.x == tile->coords.x &&
            tmp->ia->level == needed.level) {
            dprintf(tmp->fd, "Current level %d\n", tmp->ia->level);
            plv_cmd(tmp, serv, NULL);
        }
        tmp = tmp->next;
    }
}
