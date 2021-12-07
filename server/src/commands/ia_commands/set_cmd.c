/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** set_object_cmd
*/

#include "server.h"
#include "my.h"

static bool set(int *nb, int *inv_nb, int fd);
static object_prop_t *create_object_tab(inventory_t *i, content_t *c);

void set_cmd(client_t *client, serv_t *serv, char *arg)
{
    pos_t coords = client->ia->coords;
    bool object_set = false;
    object_prop_t *objects = create_object_tab(&client->ia->inventory,
                                    &serv->map[coords.y][coords.x]->content);

    for (int i = 0; i < 7; i++) {
        if (arg && strcmp(arg, objects[i].type) == 0)
            object_set = set(objects[i].c_nb, objects[i].inv_nb, client->fd);
    }
    (!object_set) ? dprintf(client->fd, "ko\n") : 0;
    pin_cmd(client, serv, NULL);
    for (client_t *graph = serv->client; graph; graph = graph->next)
        if (graph->status == GRAPHICAL)
            bct_cmd(graph, serv, my_sdup(4, my_int_to_strnum(coords.x), " ",
                                            my_int_to_strnum(coords.y), "\0"));
}

static bool set(int *nb, int *inv_nb, int fd)
{
    if (*inv_nb <= 0)
        return false;
    *nb = *nb + 1;
    *inv_nb = *inv_nb - 1;
    dprintf(fd, "ok\n");
    return true;
}

static object_prop_t *create_object_tab(inventory_t *i, content_t *c)
{
    object_prop_t *tab = malloc(sizeof(object_prop_t) * 7);

    tab[0] = (object_prop_t){"deraumere",  &i->nb_deraumere, &c->nb_deraumere};
    tab[1] = (object_prop_t){"food",  &i->nb_food, &c->nb_food};
    tab[2] = (object_prop_t){"linemate",  &i->nb_linemate, &c->nb_linemate};
    tab[3] = (object_prop_t){"mendiane",  &i->nb_mendiane, &c->nb_mendiane};
    tab[4] = (object_prop_t){"phiras",  &i->nb_phiras, &c->nb_phiras};
    tab[5] = (object_prop_t){"sibur",  &i->nb_sibur, &c->nb_sibur};
    tab[6] = (object_prop_t){"thystame",  &i->nb_thystame, &c->nb_thystame};
    return tab;
}