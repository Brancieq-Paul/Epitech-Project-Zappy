/*
** EPITECH PROJECT, 2021
** zappy [WSL: Ubuntu]
** File description:
** get_needed_ressources
*/

#include "map.h"

static content_t get_nb_ressources(map_t map);
static content_t get_total_ressoures(pos_t map_size);

content_t get_needed_ressources(map_t map, pos_t map_size)
{
    content_t current = get_nb_ressources(map);
    content_t total = get_total_ressoures(map_size);
    return substract_contents(total, current);
}

static content_t get_nb_ressources(map_t map)
{
    content_t ressources = init_content();

    for (int i = 0; map[i]; i++) {
        for (int j = 0; map[i][j]; j++) {
            ressources = add_contents(ressources, map[i][j]->content);
        }
    }
    return ressources;
}

static content_t get_total_ressoures(pos_t map_size)
{
    content_t content;

    content.nb_deraumere = map_size.x * map_size.y * DERAUMERE_DENSITY;
    content.nb_food = map_size.x * map_size.y * FOOD_DENSITY;
    content.nb_linemate = map_size.x * map_size.y * LINEMATE_DENSITY;
    content.nb_mendiane = map_size.x * map_size.y * MENDIANE_DENSITY;
    content.nb_phiras = map_size.x * map_size.y * PHIRAS_DENSITY;
    content.nb_sibur = map_size.x * map_size.y * SIBUR_DENSITY;
    content.nb_thystame = map_size.x * map_size.y * THYSTAME_DENSITY;
    return content;
}