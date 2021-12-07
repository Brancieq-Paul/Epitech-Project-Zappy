/*
** EPITECH PROJECT, 2021
** B-NWP-400-RUN-4-1-myteams-dorian.beasse
** File description:
** my_sdup
*/

#include <stdlib.h>
#include <stdarg.h>
#include "my.h"
#include <string.h>

char *my_sdup(int nb_str, ...)
{
    va_list args;
    char *sdup = NULL;
    va_start(args, nb_str);

    sdup = strdup(va_arg(args, char *));
    for (int i = 1 ; i < nb_str ; i++)
        sdup = my_strdupcat(sdup, va_arg(args, char *));
    va_end(args);
    return (sdup);
}