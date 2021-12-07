/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** graphical_management
*/

#include "server.h"

void graphical_management(char *cmd_line, serv_t *serv, client_t *client)
{
    char *cmd_token;
    char *cmd_args = 0;

    cmd_token = strtok(cmd_line, " ");
    cmd_args = strtok(NULL, "\0");
    for (int i = 0; serv->graph_cmds[i] != NULL; i++) {
        if (strcmp(cmd_token, serv->graph_cmds[i]->name) == 0) {
            serv->graph_cmds[i]->func(client, serv, cmd_args);
            break;
        }
    }
}