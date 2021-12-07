/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** fork_cmd
*/

#include "server.h"
#include "time_functions.h"

void fork_cmd(client_t *client, serv_t *serv, char *arg)
{
    egg_t *new_egg = malloc(sizeof(egg_t));
    static int egg_nb = 1;

    new_egg->pos = client->ia->coords;
    new_egg->team_name = client->ia->team_name;
    new_egg->status = HATCHING;
    new_egg->direction = client->ia->direction;
    new_egg->launched_time = get_current_time();
    new_egg->nb = egg_nb;
    new_egg->used = false;
    new_egg->next = serv->eggs;
    serv->eggs = new_egg;
    dprintf(client->fd, "ok\n");
    enw_cmd(new_egg, serv, client->ia->nb);
    egg_nb++;
    (void)arg;
}
