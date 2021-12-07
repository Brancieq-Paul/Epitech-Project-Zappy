/*
** EPITECH PROJECT, 2021
** B-NWP-400-RUN-4-1-myteams-dorian.beasse
** File description:
** add_str_to_array
*/

#include "utils.h"
#include <stdlib.h>
#include <string.h>

char **add_str_to_array(char **array, char *str)
{
    int size = 0;

    if (array) {
        while (array[size])
            size++;
    }
    array = realloc(array, sizeof(char *) * (size + 2));
    array[size] = strdup(str);
    array[size + 1] = NULL;
    return array;
}