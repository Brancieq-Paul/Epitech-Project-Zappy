/*
** EPITECH PROJECT, 2021
** myteams [WSL: Ubuntu]
** File description:
** remove_before_sep
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"

char *remove_before_sep(char *str, char sep)
{
    int pos = my_count_until_sep(str, sep) + 1;
    int len = strlen(str) - pos;
    char *removed;
    int i = 0;

    if (len == 0)
        return NULL;
    removed = malloc(sizeof(char) * len);
    while (str[pos]) {
        removed[i] = str[pos];
        i++;
        pos++;
    }
    return removed;
}