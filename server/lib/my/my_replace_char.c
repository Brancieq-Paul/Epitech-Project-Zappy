/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** my_replace_char
*/

#include <string.h>

char *my_replace_char(char *str, char find, char replace)
{
    char *current_pos;

    if (!str || !str[0])
        return NULL;
    current_pos  = strchr(str, find);
    while (current_pos) {
        *current_pos = replace;
        current_pos = strchr(current_pos, find);
    }
    return str;
}