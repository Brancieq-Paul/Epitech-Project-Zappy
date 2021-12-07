/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** get_west_vision_line
*/

#include "server.h"
#include "my.h"

char *get_west_vision_line(client_t *client, map_t map, int vision_unit)
{
    pos_t coords = client->ia->coords;
    tile_t *player_tile = map[coords.y][coords.x];
    char *vision_line = "";

    if (vision_unit == 0)
        return my_strdupcat(get_tile_ressources(player_tile->content), ", ");
    for (int i = 0; i < vision_unit; i++) {
        player_tile = player_tile->left;
        player_tile = player_tile->back;
    }
    for (int i = 0; i < (2 * vision_unit) + 1; i++) {
        vision_line = my_strdupcat(vision_line,
                                    get_tile_ressources(player_tile->content));
        if (i != (2 * vision_unit))
            vision_line = my_strdupcat(vision_line, ", ");
        player_tile = player_tile->front;
    }
    return vision_line;
}