/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** incantation_cmd
*/

#include "server.h"
#include "my.h"

static const incantation_t INC[] = {
    { 1, 1, 1, 0, 0, 0, 0, 0 },
    { 2, 2, 1, 1, 1, 0, 0, 0 },
    { 3, 2, 2, 0, 1, 0, 2, 0 },
    { 4, 4, 1, 1, 2, 0, 1, 0 },
    { 5, 4, 1, 2, 1, 3, 0, 0 },
    { 6, 6, 1, 2, 3, 0, 1, 0 },
    { 7, 6, 2, 2, 2, 2, 2, 1 }
};

static bool ressources_conditions(incantation_t needed, content_t content);
static bool players_conditions(incantation_t needed, client_t *players,
                                                                tile_t *tile);
static void send_msg(incantation_t needed, client_t *clients, tile_t *tile);
static void send_events(client_t *client, serv_t *serv);

bool incantation_checks(client_t *client, serv_t *serv, bool send_message)
{
    tile_t *tile = serv->map[client->ia->coords.y][client->ia->coords.x];
    int  client_lvl = client->ia->level;

    if (client_lvl >= 8 ||
        !players_conditions(INC[client_lvl - 1], serv->client, tile) ||
        !ressources_conditions(INC[client_lvl - 1], tile->content)) {
        dprintf(client->fd, "ko\n");
        return false;
    }
    if (send_message) {
        client->ia->is_elevating = true;
        send_msg(INC[client_lvl - 1], serv->client, tile);
        send_events(client, serv);
        client->ia->is_elevating = false;
    }
    return true;
}

static void send_events(client_t *client, serv_t *serv)
{
    pos_t coords = client->ia->coords;

    pic_cmd(client, serv);
    for (client_t *graph = serv->client; graph; graph = graph->next)
        if (graph->status == GRAPHICAL)
            bct_cmd(graph, serv, my_sdup(4, my_int_to_strnum(coords.x), " "
                                    , my_int_to_strnum(coords.y), "\0"));
}

static void send_msg(incantation_t needed, client_t *clients, tile_t *tile)
{
    client_t *tmp = clients;

    while (tmp) {
        if (tmp->status == IA && tmp->ia->coords.y == tile->coords.y &&
            tmp->ia->coords.x == tile->coords.x &&
            tmp->ia->level == needed.level)
            dprintf(tmp->fd, "%s\n", ELEVATION_MSG);
        tmp = tmp->next;
    }
}

static bool ressources_conditions(incantation_t needed, content_t content)
{
    if (content.nb_deraumere >= needed.deraumere &&
        content.nb_linemate >= needed.linemate &&
        content.nb_mendiane >= needed.mendiane &&
        content.nb_phiras >= needed.phiras &&
        content.nb_sibur >= needed.sibur &&
        content.nb_thystame >= needed.thystame)
        return true;
    return false;
}


static bool players_conditions(incantation_t needed, client_t *players,
                                                                tile_t *tile)
{
    client_t *tmp = players;
    int total = 0;

    while (tmp) {
        if (tmp->status == IA && tmp->ia->coords.y == tile->coords.y &&
            tmp->ia->coords.x == tile->coords.x &&
            tmp->ia->level == needed.level)
            total++;
        tmp = tmp->next;
    }
    if (total >= needed.nb_players)
        return true;
    return false;
}