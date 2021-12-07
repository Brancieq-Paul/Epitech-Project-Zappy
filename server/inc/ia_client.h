/*
** EPITECH PROJECT, 2021
** zappy [WSL: Ubuntu]
** File description:
** ia_client
*/

#ifndef IA_CLIENT_H_
#define IA_CLIENT_H_

#include "map.h"

typedef enum ia_direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
}direction_t;

typedef struct inventory_s {
    int nb_food;
    int nb_linemate;
    int nb_deraumere;
    int nb_sibur;
    int nb_mendiane;
    int nb_phiras;
    int nb_thystame;
}inventory_t;

typedef struct ia_client_s {
    char *team_name;
    pos_t coords;
    direction_t direction;
    int level;
    double life_unit;
    double food_life;
    int nb;
    inventory_t inventory;
    bool is_elevating;
}ia_client_t;

#endif /* !IA_CLIENT_H_ */
