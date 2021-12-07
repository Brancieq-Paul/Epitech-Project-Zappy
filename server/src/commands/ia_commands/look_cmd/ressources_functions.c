/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** ressources_functions
*/

#include "server.h"
#include "my.h"

char *add_ressources(char *type, int nb, char *ressources);

char *get_tile_ressources(content_t content)
{
    char *ress = "";

    ress = add_ressources("deraumere", content.nb_deraumere, ress);
    ress = add_ressources("food", content.nb_food, ress);
    ress = add_ressources("linemate", content.nb_linemate, ress);
    ress = add_ressources("mendiane", content.nb_mendiane, ress);
    ress = add_ressources("phiras", content.nb_phiras, ress);
    ress = add_ressources("sibur", content.nb_sibur, ress);
    ress = add_ressources("thystame", content.nb_thystame, ress);
    ress = add_ressources("player", content.nb_player, ress);
    return ress;
}

char *add_ressources(char *type, int nb, char *ressources)
{
    char *new_ressource = "";

    if (nb == 0)
        return ressources;
    if (strlen(ressources) != 0 && ressources[strlen(ressources) - 1] !=  ' ')
        new_ressource = " ";
    for (int i = 0; i < nb; i++) {
        if (i == nb - 1)
            new_ressource = my_sdup(2, new_ressource, type);
        else
            new_ressource = my_sdup(3, new_ressource, type, " ");
    }
    return my_strdupcat(ressources, new_ressource);
}