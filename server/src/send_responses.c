/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** launch_command
*/

#include "server.h"
#include "my.h"
#include "time_functions.h"

static void exec_last_cmd(serv_t *serv, client_t *client);
static client_t *manage_client(client_t *client, int i, serv_t *serv,
                                                                char *cmd_arg);

void send_responses(serv_t *serv)
{
    client_t *tmp = serv->client;
    while (tmp) {
        if (tmp->status == IA && is_cmd_time_end(tmp)) {
            if (!tmp->to_exec) {
                exec_last_cmd(serv, tmp);
            }
            else {
                tmp->to_exec(tmp, serv, tmp->arg);
                tmp->to_exec = NULL;
                tmp->cmd_time = 0;
            }
        }
        tmp = tmp->next;
    }
}

static void exec_last_cmd(serv_t *serv, client_t *client)
{
    cmd_list_t *cmd_line;
    char *cmd_token;
    char *cmd_arg;

    if (!client->cmd_list)
        return;
    cmd_line = client->cmd_list;
    cmd_token = strtok(cmd_line->command, " ");
    cmd_arg = (strtok(NULL, "\0"));
    cmd_arg = cmd_arg ? my_remove_whitespace(cmd_arg) : NULL;
    if (strcmp(cmd_token, "Incantation") == 0
    && !incantation_checks(client, serv, true)) {
        client->cmd_list = client->cmd_list->next;
        return;
    }
    for (int i = 0; serv->ia_cmds[i] != NULL; i++)
        if (strcmp(cmd_token, serv->ia_cmds[i]->name) == 0)
            client = manage_client(client, i, serv, cmd_arg);
    !client->to_exec ? dprintf(client->fd, "ko\n") : 0;
    client->cmd_list = client->cmd_list->next;
}

static client_t *manage_client(client_t *client, int i, serv_t *serv,
                                                                char *cmd_arg)
{
    client->to_exec = serv->ia_cmds[i]->func;
    client->launched_cmd = get_current_time();
    client->arg = cmd_arg;
    client->cmd_time = get_time_from_freq(serv->ia_cmds[i]->time
                                                    , serv->serv_infos.freq);
    return client;
}