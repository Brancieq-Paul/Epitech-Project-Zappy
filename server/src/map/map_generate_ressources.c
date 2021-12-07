/*
** EPITECH PROJECT, 2021
** zappy [WSL: Ubuntu]
** File description:
** map_generate_ressources
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "map.h"
#include "my.h"

static map_t spread_ressource(char *key, int nb, map_t map, pos_t map_size);
static void add_ressource(char *key, content_t *content);

map_t map_generate_ressources(map_t map, pos_t map_size)
{
    content_t needed = get_needed_ressources(map, map_size);

    map = spread_ressource("deraumere", needed.nb_deraumere, map, map_size);
    map = spread_ressource("food", needed.nb_food, map, map_size);
    map = spread_ressource("linemate", needed.nb_linemate, map, map_size);
    map = spread_ressource("mendiane", needed.nb_mendiane, map, map_size);
    map = spread_ressource("phiras", needed.nb_phiras, map, map_size);
    map = spread_ressource("sibur", needed.nb_sibur, map, map_size);
    map = spread_ressource("thystame", needed.nb_thystame, map, map_size);
    return map;
}

static map_t spread_ressource(char *key, int nb, map_t map, pos_t map_size)
{
    pos_t coords;

    while (nb > 0) {
        coords.x = rand_between_two_value(0, map_size.x - 1);
        coords.y = rand_between_two_value(0, map_size.y - 1);
        add_ressource(key, &map[coords.y][coords.x]->content);
        nb--;
    }
    return map;
}

static void add_ressource(char *key, content_t *content)
{
    content->nb_deraumere = (strcmp(key, "deraumere") == 0) ?
            content->nb_deraumere + 1 : content->nb_deraumere;
    content->nb_food = (strcmp(key, "food") == 0) ?
            content->nb_food + 1 : content->nb_food;
    content->nb_linemate = (strcmp(key, "linemate") == 0) ?
            content->nb_linemate + 1 : content->nb_linemate;
    content->nb_mendiane = (strcmp(key, "mendiane") == 0) ?
            content->nb_mendiane + 1 : content->nb_mendiane;
    content->nb_phiras = (strcmp(key, "phiras") == 0) ?
            content->nb_phiras + 1 : content->nb_phiras;
    content->nb_sibur = (strcmp(key, "sibur") == 0) ?
            content->nb_sibur + 1 : content->nb_sibur;
    content->nb_thystame = (strcmp(key, "thystame") == 0) ?
            content->nb_thystame + 1 : content->nb_thystame;
}