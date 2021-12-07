/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** ressources_management
*/

#include "server.h"
#include "time_functions.h"

static bool should_reload_ressources(serv_t *serv, int freq);

void ressources_management(serv_t *serv)
{
    pos_t size = (pos_t){serv->serv_infos.width, serv->serv_infos.height};

    if (should_reload_ressources(serv, serv->serv_infos.freq))
        serv->map = map_generate_ressources(serv->map, size);
}

static bool should_reload_ressources(serv_t *serv, int freq)
{
    long time_current = get_current_time();
    long time_tmp = get_time_from_freq(RESOURCES_REGEN_TIME, freq) * 1000000;

    if (time_current - serv->ressources_regen_time >= time_tmp)
        return true;
    return false;
}