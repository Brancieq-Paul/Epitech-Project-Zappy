/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** add_team
*/

#include "server_infos.h"
#include "server.h"

static server_info_t set_info(server_info_t info, char opt, char **av)
{
    if (av[1] == NULL && isdigit(av[1]))
        exit(EXIT_ERROR);
    if (opt == 'p')
        info.port = (int)strtol(av[1], NULL, 0);
    if (opt == 'x')
        info.width = (int)strtol(av[1], NULL, 0);
    if (opt == 'y')
        info.height = (int)strtol(av[1], NULL, 0);
    if (opt == 'f')
        info.freq = (int)strtol(av[1], NULL, 0);
    return (info);
}

static server_info_t get_info(server_info_t info, char **av)
{
    char opt[6] = {'p', 'x', 'y', 'f', 0};

    for (int i = 0; opt[i]; i++)
        if (av[0][0] == '-' && av[0][1] == opt[i] && av[0][2] == 0)
            info = set_info(info, opt[i], av);
    return (info);
}

static teams_t *create_list(teams_t *team_list, char *team_name)
{
    teams_t *new_team = malloc(sizeof(teams_t));
    teams_t *tmp = team_list;

    new_team->team_name = strdup(team_name);
    new_team->nb_client = 0;
    new_team->max_nb_client = 0;
    new_team->next = NULL;
    if (!team_list)
        return new_team;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_team;
    return (team_list);
}

static server_info_t create_team_list(server_info_t info, char **av)
{
    int i = 0;
    int j = 0;

    for (; av[i] && strcmp(av[i], "-n") > 0;)
        i++;
    for (i++; av[i] && av[i][0] != '-' ; i++)
        info.team_list = create_list(info.team_list, av[i]);
    for (; av[j] && strcmp(av[j], "-c") > 0;)
        j++;
    for (teams_t *tmp = info.team_list; tmp != NULL; tmp = tmp->next)
        tmp->max_nb_client = (int)strtol(av[j+1], NULL, 0);
    if (info.team_list == NULL || info.team_list->max_nb_client == 0)
        exit(EXIT_ERROR);
    return (info);
}

server_info_t get_server_info(char **av)
{
    server_info_t info;

    info.freq = 100;
    for (int i = 1, j = 0; av[i]; i++, j++)
        info = get_info(info, av + i);
    info.team_list = NULL;
    info = create_team_list(info, av);
    return (info);
}