/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** life_management
*/

#include "server.h"
#include "time_functions.h"

static void kill_ia(client_t *ia, serv_t *serv);
static void food_management(client_t *client, double diff, int freq);
static void ia_management(client_t *ia, double diff, serv_t *serv);

void life_management(serv_t *serv)
{
    static long last_check = 0;
    double diff = 0;
    long current_time = get_current_time();

    if (last_check == 0) {
        last_check = current_time;
        return;
    }
    diff = (double)(current_time - last_check) / (uint64_t)1000000;
    for (client_t *tmp = serv->client; tmp; tmp = tmp->next) {
        if (tmp->status == IA) {
            ia_management(tmp, diff, serv);
        }
    }
    last_check = current_time;
}

static void ia_management(client_t *ia, double diff, serv_t *serv)
{
    ia->ia->life_unit -= diff;
    food_management(ia, diff, serv->serv_infos.freq);
    if (ia->ia->life_unit <= 0)
        kill_ia(ia, serv);
}

static void food_management(client_t *client, double diff, int freq)
{
    if (client->ia->inventory.nb_food == 0)
        return;
    client->ia->food_life -= diff;
    if (client->ia->food_life <= 0) {
        client->ia->food_life = 126.0 / (double)freq;
        client->ia->inventory.nb_food--;
    }
}

static void kill_ia(client_t *ia, serv_t *serv)
{
    dprintf(ia->fd, "dead\n");
    pdi_cmd(serv, ia->ia->nb);
    remove_client(serv, ia);
}