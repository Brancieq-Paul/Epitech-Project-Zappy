/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** create_ia_client
*/

#include "server.h"
#include "my.h"

static inventory_t create_inventory(void);
static ia_client_t *create_ia_from_egg(egg_t *egg, int nb,  serv_t *serv);

ia_client_t *create_ia_client(int nb, teams_t *team, serv_t *serv)
{
    ia_client_t *ia = malloc(sizeof(ia_client_t));
    egg_t *egg;

    if ((egg = egg_is_avaible(serv->eggs, team->team_name)))
        return create_ia_from_egg(egg, nb, serv);
    ia->team_name = team->team_name;
    ia->direction = NORTH;
    ia->level = 1;
    ia->nb = nb;
    ia->is_elevating = false;
    ia->food_life = 126.0 / (double)serv->serv_infos.freq;
    ia->life_unit = 1260.0 / (double)serv->serv_infos.freq;
    ia->coords.x = rand_between_two_value(0, serv->serv_infos.width - 1);
    ia->coords.y = rand_between_two_value(0, serv->serv_infos.height - 1);
    ia->inventory = create_inventory();
    team->nb_client++;
    return ia;
}

static ia_client_t *create_ia_from_egg(egg_t *egg, int nb,  serv_t *serv)
{
    ia_client_t *ia = malloc(sizeof(ia_client_t));

    ia->team_name = egg->team_name;
    ia->direction = egg->direction;
    ia->level = 1;
    ia->nb = nb;
    ia->is_elevating = false;
    ia->food_life = 126.0 / (double)serv->serv_infos.freq;
    ia->life_unit = 1260.0 / (double)serv->serv_infos.freq;
    ia->coords.x = egg->pos.x;
    ia->coords.y = egg->pos.y;
    ia->inventory = create_inventory();
    ebo_cmd(serv, egg->nb);
    return ia;
}

static inventory_t create_inventory(void)
{
    inventory_t inventory;

    inventory.nb_food = 0;
    inventory.nb_linemate = 0;
    inventory.nb_deraumere = 0;
    inventory.nb_sibur = 0;
    inventory.nb_mendiane = 0;
    inventory.nb_phiras = 0;
    inventory.nb_thystame = 0;
    return inventory;
}