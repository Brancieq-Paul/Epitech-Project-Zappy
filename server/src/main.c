/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu-20.04]
** File description:
** main
*/

#include <time.h>
#include "map.h"
#include "server.h"
#include "time_functions.h"

int main(int ac, char **av)
{
    serv_t *serv = NULL;
    server_info_t infos;

    error_handling(ac, av);
    infos = get_server_info(av);
    srand(time(NULL));
    serv = create_server(infos.port);
    serv->ressources_regen_time = get_current_time();
    serv->serv_infos = infos;
    serv->map = create_map(serv->serv_infos.width, serv->serv_infos.height);
    serv->ia_cmds = create_ia_cmds_tab();
    serv->graph_cmds = create_graph_cmds_tab();
    if (serv == NULL)
        return 84;
    server_loop(serv);
    return 0;
}