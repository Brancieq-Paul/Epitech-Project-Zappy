/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** broadcast_text_cmd
*/

#include "server.h"

static const orientation_t ORIENTATIONS[] = {
    { NORTH, 2, 1, 8, 4, 5, 6, 3, 7 },
    { EAST, 4, 3, 2, 6, 7, 8, 5, 1 },
    { SOUTH, 6, 5, 4, 8, 1, 2, 7, 3 },
    { WEST, 8, 7, 6, 2, 3, 4, 1, 5 },
};

static int get_broadcast_origin(client_t *to, client_t *client, serv_t *serv);
static pos_t get_vect_origin(pos_t to, pos_t client, serv_t *serv);
static int absolute(int nb);
static int get_tile_from_vect(orientation_t orientation, pos_t vect);

void broadcast_cmd(client_t *client, serv_t *serv, char *arg)
{
    client_t *tmp = serv->client;
    int broadcast_origin = 0;

    while (tmp) {
        broadcast_origin = get_broadcast_origin(tmp, client, serv);
        dprintf(tmp->fd, "message %d, %s\n", broadcast_origin, arg);
        tmp = tmp->next;
    }
    for (client_t *tmp = serv->client; tmp; tmp = tmp->next)
        if (tmp->status == GRAPHICAL)
            pbc_cmd(tmp, broadcast_origin, arg);
    dprintf(client->fd, "ok\n");
}

static int get_broadcast_origin(client_t *to, client_t *client, serv_t *serv)
{
    pos_t vect = get_vect_origin(to->ia->coords, client->ia->coords, serv);
    int i = 0;

    while (ORIENTATIONS[i].direction != client->ia->direction)
        i++;
    return get_tile_from_vect(ORIENTATIONS[i], vect);
}

static int get_tile_from_vect(orientation_t orientation, pos_t vect)
{
    int tile = 0;

    tile = (vect.x == 1 && vect.y == 1) ? orientation.top_left : tile;
    tile = (vect.x == 1 && vect.y == -1) ? orientation.bot_left : tile;
    tile = (vect.x == 1 && vect.y == 0) ? orientation.mid_left : tile;
    tile = (vect.x == -1 && vect.y == 1) ? orientation.top_right : tile;
    tile = (vect.x == -1 && vect.y == -1) ? orientation.bot_right : tile;
    tile = (vect.x == -1 && vect.y == 0) ? orientation.mid_right : tile;
    tile = (vect.x == 0 && vect.y == 1) ? orientation.top_center : tile;
    tile = (vect.x == 0 && vect.y == -1) ? orientation.bot_center : tile;
    tile = (vect.x == 0 && vect.y == 0) ? 0 : tile;
    return tile;
}

static pos_t get_vect_origin(pos_t to, pos_t client, serv_t *serv)
{
    int distx = serv->serv_infos.width - absolute(to.x - client.x);
    int disty = serv->serv_infos.height - absolute(to.y - client.y);
    pos_t vect;

    vect.x = client.x < to.x ? 1 : client.x > to.x ? -1 : 0;
    vect.y = client.y < to.y ? 1 : client.y > to.y ? -1 : 0;
    if (absolute(distx) < absolute(to.x - client.x))
        vect.x *= -1;
    if (absolute(disty) < absolute(to.y - client.y))
        vect.y *= -1;
    return vect;
}

static int absolute(int nb)
{
    return nb < 0 ? (nb * -1) : nb;
}