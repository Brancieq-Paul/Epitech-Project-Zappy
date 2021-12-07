/*
** EPITECH PROJECT, 2021
** B-NWP-400-RUN-4-1-myteams-dorian.beasse
** File description:
** server_run
*/

#include "server.h"

static bool new_connection_requested(serv_t *serv)
{
    return FD_ISSET(serv->fd, &(serv->readfds));
}

void server_loop(serv_t *serv)
{
    struct timeval timeout = (struct timeval){0, 1.0 /
                                                (double)serv->serv_infos.freq};

    while (1 && serv->is_run) {
        serv->readfds = serv->active_fds;
        if (select(FD_SETSIZE, &(serv->readfds), NULL, NULL, &timeout) == -1)
            handle_error("select");
        if (new_connection_requested(serv)) {
            accept_client(serv);
        }
        else
            handle_inputs(serv);
        life_management(serv);
        eggs_management(serv);
        send_responses(serv);
        ressources_management(serv);
    }
    server_destroy(serv);
}
