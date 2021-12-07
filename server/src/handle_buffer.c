/*
** EPITECH PROJECT, 2021
** B-NWP-400-RUN-4-1-myteams-dorian.beasse
** File description:
** handle_buffer
*/

#include "server.h"
#include "commands.h"
#include "my.h"

static void manage_new_graphic(client_t *client, serv_t *serv);
static void manage_new_ia(client_t *client, teams_t *team, serv_t *serv);
static void handle_connexion(char *cmd_line, client_t *client,
                                                            serv_t *infos);

cmd_list_t *add_cmd_list(char *cmd, cmd_list_t *cmd_list)
{
    cmd_list_t *tmp = cmd_list;
    cmd_list_t *new_cmd = malloc(sizeof(cmd_list_t));
    int command_nb = 0;

    for (tmp = cmd_list; tmp != NULL; tmp = tmp->next)
        command_nb++;
    if (command_nb == 10)
        return (cmd_list);
    new_cmd->command = strdup(cmd);
    new_cmd->next = cmd_list;
    return new_cmd;
}

void handle_buffer(serv_t *serv, client_t *client, char *buf)
{
    char *cmd_line = strtok(buf, "\n");

    cmd_line = my_replace_char(cmd_line, '\n', '\0');
    if (!cmd_line)
        return;
    if (client->status == WAITING)
        handle_connexion(cmd_line, client, serv);
    else if (client->status == IA)
        client->cmd_list = add_cmd_list(cmd_line, client->cmd_list);
    else
        graphical_management(cmd_line, serv, client);
}

static void handle_connexion(char *cmd_line, client_t *client,
                                                            serv_t *serv)
{
    teams_t *tmp = serv->serv_infos.team_list;
    int fd = client->fd;

    if (strcmp(cmd_line, "GRAPHIC") == 0) {
        manage_new_graphic(client, serv);
        return;
    }
    while (tmp) {
        if (strcmp(cmd_line, tmp->team_name) == 0) {
            manage_new_ia(client, tmp, serv);
            return;
        }
        tmp = tmp->next;
    }
    dprintf(fd, "ko\n");
}

static void manage_new_graphic(client_t *client, serv_t *serv)
{
    client->status = GRAPHICAL;
    msz_cmd(client, serv, NULL);
    sgt_cmd(client, serv, NULL);
    mct_cmd(client, serv);
    tna_cmd(client, serv, NULL);
    for (client_t *tmp = serv->client; tmp; tmp = tmp->next) {
        for (client_t *graph = serv->client; graph; graph = graph->next)
            if (graph->status == GRAPHICAL)
                pnw_cmd(graph, tmp);
        pic_cmd(tmp, serv);
    }
}

static void manage_new_ia(client_t *client, teams_t *team, serv_t *serv)
{
    static int client_nb = 1;

    if (team->nb_client == team->max_nb_client) {
        dprintf(client->fd, "ko\n");
        return;
    }
    client->status = IA;
    client->ia = create_ia_client(client_nb, team, serv);
    serv->map[client->ia->coords.y][client->ia->coords.x]->content.nb_player++;
    dprintf(client->fd, "%d\n%d %d\n", team->max_nb_client - team->nb_client,
                            serv->serv_infos.width, serv->serv_infos.height);
    send_events_new_ia(client, serv);
    client_nb++;
}