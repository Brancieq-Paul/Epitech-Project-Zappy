/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** eject_cmd
*/

#include "server.h"

static bool is_player_on_tile(client_t *player, pos_t coords, client_t *client);
static client_t *eject_player(client_t *player, serv_t *serv, direction_t dir);
static int get_tile_comming_from(direction_t p_dir, direction_t e_dir);

void eject_cmd(client_t *client, serv_t *serv, char *arg)
{
    tile_t *tile = serv->map[client->ia->coords.y][client->ia->coords.x];
    client_t *tmp = serv->client;
    bool ejected = false;

    while (tmp) {
        if (tmp->status == IA && is_player_on_tile(tmp, tile->coords, client)) {
            tmp = eject_player(tmp, serv, client->ia->direction);
            dprintf(tmp->fd, "eject %d\n",
            get_tile_comming_from(tmp->ia->direction, client->ia->direction));
            ejected = true;
            pex_cmd(serv, client->ia->nb);
            ppo_cmd(client, serv, NULL);
        }
        tmp = tmp->next;
    }
    if (ejected)
        dprintf(client->fd, "ok\n");
    else
        dprintf(client->fd, "ko\n");
    (void)arg;
}

static bool is_player_on_tile(client_t *player, pos_t coords, client_t *client)
{
    return player->ia->coords.y == coords.y &&
            player->ia->coords.x == coords.x &&
            player->ia->nb != client->ia->nb;
}

static client_t *eject_player(client_t *player, serv_t *serv, direction_t dir)
{
    tile_t *tile = serv->map[player->ia->coords.y][player->ia->coords.x];

    tile->content.nb_player--;
    if (dir == NORTH) {
        tile->front->content.nb_player++;
        player->ia->coords = tile->front->coords;
    }
    if (player->ia->direction == SOUTH) {
        tile->back->content.nb_player++;
        player->ia->coords = tile->back->coords;
    }
    if (player->ia->direction == WEST) {
        tile->left->content.nb_player++;
        player->ia->coords = tile->left->coords;
    }
    if (player->ia->direction == EAST) {
        tile->right->content.nb_player++;
        player->ia->coords = tile->right->coords;
    }
    return player;
}

static int get_tile_comming_from(direction_t p_dir, direction_t e_dir)
{
    if (p_dir == e_dir)
        return 5;
    if (p_dir + e_dir == 5 || p_dir + e_dir == 1)
        return 1;
    if ((int)p_dir - (int)e_dir == -2 || p_dir - e_dir == 3 ||
        p_dir + e_dir == 3)
        return 3;
    return 7;
}