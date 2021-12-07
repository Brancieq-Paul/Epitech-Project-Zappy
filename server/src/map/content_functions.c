/*
** EPITECH PROJECT, 2021
** zappy [WSL: Ubuntu]
** File description:
** content_functions
*/

#include "map.h"

content_t init_content(void)
{
    content_t content;

    content.nb_deraumere = 0;
    content.nb_food = 0;
    content.nb_linemate = 0;
    content.nb_mendiane = 0;
    content.nb_phiras = 0;
    content.nb_sibur = 0;
    content.nb_thystame = 0;
    content.nb_player = 0;
    return content;
}

content_t add_contents(content_t content1, content_t content2)
{
    content1.nb_deraumere += content2.nb_deraumere;
    content1.nb_food += content2.nb_food;
    content1.nb_linemate += content2.nb_linemate;
    content1.nb_mendiane += content2.nb_mendiane;
    content1.nb_phiras += content2.nb_phiras;
    content1.nb_sibur += content2.nb_sibur;
    content1.nb_thystame += content2.nb_thystame;
    content1.nb_player += content2.nb_player;
    return content1;
}

content_t substract_contents(content_t content1, content_t content2)
{
    content1.nb_deraumere -= content2.nb_deraumere;
    content1.nb_food -= content2.nb_food;
    content1.nb_linemate -= content2.nb_linemate;
    content1.nb_mendiane -= content2.nb_mendiane;
    content1.nb_phiras -= content2.nb_phiras;
    content1.nb_sibur -= content2.nb_sibur;
    content1.nb_thystame -= content2.nb_thystame;
    content1.nb_player -= content2.nb_player;
    return content1;
}