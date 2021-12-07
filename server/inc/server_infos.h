/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** server_info
*/

#ifndef SERVER_INFO_H_
#define SERVER_INFO_H_
#define _GNU_SOURCE

typedef struct teams_s
{
    int max_nb_client;
    int nb_client;
    char *team_name;
    struct teams_s *next;
} teams_t;

typedef struct server_info_s
{
    int port;
    int width;
    int height;
    teams_t *team_list;
    int freq;
} server_info_t;

server_info_t get_server_info(char **av);

#endif /* !SERVER_INFO_H_ */
