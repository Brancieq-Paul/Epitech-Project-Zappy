/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** send_events_new_ia
*/

#include "server.h"

void send_events_new_ia(client_t *ia, serv_t *serv)
{
    for (client_t *graph = serv->client; graph; graph = graph->next)
        if (graph->status == GRAPHICAL)
            pnw_cmd(graph, ia);
    pin_cmd(ia, serv, NULL);
    for (client_t *graph = serv->client; graph; graph = graph->next)
        if (graph->status == GRAPHICAL)
            mct_cmd(graph, serv);
}