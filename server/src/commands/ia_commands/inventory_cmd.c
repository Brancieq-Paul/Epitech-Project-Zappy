/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** inventory_cmd
*/

#include "server.h"
#include "my.h"

static char *create_inventory_str(inventory_t inv, size_t size);

void inventory_cmd(client_t *client, serv_t *serv, char *arg)
{
    inventory_t inv = client->ia->inventory;
    size_t size = INVENTORY_SIZE + my_intlen(inv.nb_deraumere)
                                    + my_intlen(inv.nb_food)
                                    + my_intlen(inv.nb_linemate)
                                    + my_intlen(inv.nb_mendiane)
                                    + my_intlen(inv.nb_phiras)
                                    + my_intlen(inv.nb_sibur)
                                    + my_intlen(inv.nb_thystame);
    char *str = create_inventory_str(inv, size);

    dprintf(client->fd, "%s\n", str);
    (void)serv;
    (void)arg;
}

static char *create_inventory_str(inventory_t inv, size_t size)
{
    char *str = malloc(sizeof(char) *  (size + 1));

    sprintf(str, "[deraumere %d, food %d, linemate %d, mendiane %d, phiras %d, \
sibur %d, thystame %d]", inv.nb_deraumere,
                                inv.nb_food, inv.nb_linemate, inv.nb_mendiane,
                                inv.nb_phiras, inv.nb_sibur, inv.nb_thystame);
    return str;
}