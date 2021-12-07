/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** forward_cmd
*/

#include "server.h"
#include "my.h"

static void events_management(client_t *client, serv_t *serv, char *arg);

void forward_cmd(client_t *client, serv_t *serv, char *arg)
{
    tile_t *player_tile = serv->map[client->ia->coords.y][client->ia->coords.x];

    player_tile->content.nb_player--;
    if (client->ia->direction == NORTH) {
        player_tile->front->content.nb_player++;
        client->ia->coords = player_tile->front->coords;
    }
    if (client->ia->direction == SOUTH) {
        player_tile->back->content.nb_player++;
        client->ia->coords = player_tile->back->coords;
    }
    if (client->ia->direction == WEST) {
        player_tile->left->content.nb_player++;
        client->ia->coords = player_tile->left->coords;
    }
    if (client->ia->direction == EAST) {
        player_tile->right->content.nb_player++;
        client->ia->coords = player_tile->right->coords;
    }
    events_management(client, serv, arg);
}

static void events_management(client_t *client, serv_t *serv, char *arg)
{
    ppo_cmd(client, serv, NULL);
    dprintf(client->fd, "ok\n");
    (void)arg;
}