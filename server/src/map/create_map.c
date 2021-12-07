/*
** EPITECH PROJECT, 2021
** zappy [WSL: Ubuntu]
** File description:
** create_map
*/

#include <stdlib.h>
#include <stdio.h>
#include "map.h"

char *get_tile_ressources(content_t content);

static map_t create_map_links(map_t map, pos_t map_size);

map_t create_map(int x, int y)
{
    map_t map = malloc(sizeof(tile_t **) * (y + 1));

    for (int i = 0; i < y; i++) {
        map[i] = malloc(sizeof(tile_t *) * (x + 1));
        for (int j = 0; j < x; j++) {
            map[i][j] = malloc(sizeof(tile_t));
            map[i][j]->coords = (pos_t){j, i};
            map[i][j]->content = init_content();
        }
        map[i][x] = NULL;
    }
    map[y] = NULL;
    map = create_map_links(map, (pos_t){x, y});
    map = map_generate_ressources(map, (pos_t){x, y});
    return map;
}

static map_t create_map_links(map_t map, pos_t map_size)
{
    for (int i = 0; map[i]; i++) {
        for (int j = 0; map[i][j]; j++)
            map[i][j] = create_tile_links(map[i][j], map, map_size);
    }
    return map;
}