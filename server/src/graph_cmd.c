/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** graph_cmd
*/

#include "server.h"

void eht_cmd(client_t *client, int egg_nbr)
{
    for (client_t *tmp = client; tmp; tmp = tmp->next)
        if (tmp->status == GRAPHICAL)
            dprintf(tmp->fd, "eht %d\n", egg_nbr);
}

void ebo_cmd(serv_t *serv, int egg_nbr)
{
    for (client_t *tmp = serv->client; tmp; tmp = tmp->next)
        if (tmp->status == GRAPHICAL)
            dprintf(tmp->fd, "ebo %d\n", egg_nbr);
}

void pbc_cmd(client_t *client, int nb_player, char *msg)
{
    dprintf(client->fd, "pbc %d %s\n", nb_player, msg);
}

void pin_cmd(client_t *client, serv_t *serv, char *arg)
{
    inventory_t inv = client->ia->inventory;

    (void)arg;
    for (client_t *tmp = serv->client; tmp; tmp = tmp->next) {
        if (tmp->status == GRAPHICAL) {
            dprintf(tmp->fd, "pin %d %d %d %d %d %d %d %d %d %d\n",
            client->ia->nb, client->ia->coords.x, client->ia->coords.y,
            inv.nb_food, inv.nb_linemate, inv.nb_deraumere, inv.nb_sibur,
            inv.nb_mendiane, inv.nb_phiras, inv.nb_thystame);
        }
    }
}

void send_graph_cmd(serv_t *serv, int nb, char *msg)
{
    for (client_t *tmp = serv->client; tmp; tmp = tmp->next) {
        if (tmp->status == GRAPHICAL)
            dprintf(tmp->fd, msg, nb);
    }
}