/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** right_cmd
*/

#include "server.h"
#include "my.h"

void right_cmd(client_t *client, serv_t *serv, char *arg)
{
    direction_t new_direction;

    if (client->ia->direction == NORTH)
        new_direction = EAST;
    if (client->ia->direction == SOUTH)
        new_direction = WEST;
    if (client->ia->direction == WEST)
        new_direction = NORTH;
    if (client->ia->direction == EAST)
        new_direction = SOUTH;
    client->ia->direction = new_direction;
    dprintf(client->fd, "ok\n");
    ppo_cmd(client, serv, NULL);
    (void)serv;
    (void)arg;
}
