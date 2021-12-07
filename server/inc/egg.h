/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** eggs
*/

#ifndef EGGS_H_
#define EGGS_H_

#include "map.h"

#define HATCH_TIME      600

typedef enum egg_status_e {
    HATCHING,
    HATCHED,
}egg_status;

typedef struct egg_s {
    pos_t pos;
    direction_t direction;
    char *team_name;
    long launched_time;
    egg_status status;
    int nb;
    struct egg_s *next;
    bool used;
}egg_t;

#endif /* !EGGS_H_ */
