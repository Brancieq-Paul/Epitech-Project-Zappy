/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** eggs_management
*/

#include "server.h"
#include "time_functions.h"

static bool is_egg_hatched(egg_t *egg, int freq);

void eggs_management(serv_t *serv)
{
    egg_t *tmp = serv->eggs;

    while (tmp) {
        if (tmp->status != HATCHED
        && is_egg_hatched(tmp, serv->serv_infos.freq)) {
            tmp->status = HATCHED;
            eht_cmd(serv->client, tmp->nb);
        }
        tmp = tmp->next;
    }
}

egg_t *egg_is_avaible(egg_t *eggs, char *team_name)
{
    egg_t *tmp = eggs;

    while (tmp) {
        if (tmp->status == HATCHED && strcmp(tmp->team_name, team_name) == 0
        && !tmp->used) {
            tmp->used = true;
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

static bool is_egg_hatched(egg_t *egg, int freq)
{
    long time_current = get_current_time();
    long time_tmp = get_time_from_freq(HATCH_TIME, freq) * 1000000;

    if (time_current - egg->launched_time >= time_tmp)
        return true;
    return false;
}