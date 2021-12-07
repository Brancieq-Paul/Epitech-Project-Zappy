/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** look_cmd
*/

#include "server.h"
#include "my.h"
#include "time_functions.h"
#include "commands.h"

char *get_north_vision_line(client_t *client, map_t map, int vision_unit);
char *get_south_vision_line(client_t *client, map_t map, int vision_unit);
char *get_west_vision_line(client_t *client, map_t map, int vision_unit);
char *get_east_vision_line(client_t *client, map_t map, int vision_unit);
void look_cmd(client_t *client, serv_t *serv, char *arg)
{
    char *vision = "[";
    char *vision_line = "";

    for (int unit = 0; unit <= client->ia->level; unit++) {
        if (client->ia->direction == NORTH)
            vision_line = get_north_vision_line(client, serv->map, unit);
        if (client->ia->direction == SOUTH)
            vision_line = get_south_vision_line(client, serv->map, unit);
        if (client->ia->direction == WEST)
            vision_line = get_west_vision_line(client, serv->map, unit);
        if (client->ia->direction == EAST)
            vision_line = get_east_vision_line(client, serv->map, unit);
        vision = my_strdupcat(vision, vision_line);
    }
    vision = my_strdupcat(vision, "]");
    dprintf(client->fd, "%s\n", vision);
    (void)arg;
}