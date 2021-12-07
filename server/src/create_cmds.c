/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** create_cmds
*/

#include "server.h"

static cmds_t **fill_cmds(const cmds_t *cmds_tab)
{
    size_t nb_commands = 0;
    cmds_t **cmds = NULL;

    while (cmds_tab[nb_commands++].name != NULL) {}
    cmds = malloc(sizeof(cmds_t *) * (nb_commands + 1));
    if (cmds == NULL)
        handle_error("malloc");
    for (size_t i = 0 ; cmds_tab[i].name != NULL ; i++) {
        cmds[i] = malloc(sizeof(cmds_t));
        if (cmds[i] == NULL)
            handle_error("malloc");
        cmds[i]->name = strdup(cmds_tab[i].name);
        cmds[i]->func = cmds_tab[i].func;
        cmds[i]->time = cmds_tab[i].time;
    }
    cmds[nb_commands] = NULL;
    return cmds;
}

cmds_t **create_ia_cmds_tab(void)
{
    cmds_t tab_cmds[] = {
        {"Look", &look_cmd, LOOK_TIME}, {"Forward", &forward_cmd, FORWARD_TIME},
        {"Left", &left_cmd, LEFT_TIME}, {"Right", &right_cmd, RIGHT_TIME},
        {"Inventory", &inventory_cmd, INVENTORY_TIME},
        {"Connect_nbr", &connect_nbr_cmd, CONNECT_NBR_TIME},
        {"Take", &take_cmd, TAKE_TIME}, {"Set", &set_cmd, SET_TIME},
        {"Eject", &eject_cmd, EJECT_TIME},
        {"Incantation", &incantation_cmd, INCANTATION_TIME},
        {"Broadcast", &broadcast_cmd, BROADCAST_TIME},
        {"Fork", &fork_cmd, FORK_TIME},
        {NULL, NULL, 0},
    };
    return fill_cmds(tab_cmds);
}

cmds_t **create_graph_cmds_tab(void)
{
    cmds_t tab_cmds[] = {
        {"msz", &msz_cmd, 0},
        {"bct", &bct_cmd, 0},
        {"tna", &tna_cmd, 0},
        {"sgt", &sgt_cmd, 0},
        {"ppo", &ppo_cmd, 0},
        {"plv", &plv_cmd, 0},
        {"pin", &pin_cmd, 0},
        {NULL, NULL, 0},
    };
    return fill_cmds(tab_cmds);
}