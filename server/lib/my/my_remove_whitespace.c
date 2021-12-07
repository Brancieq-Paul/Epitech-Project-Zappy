/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** my_clean_str
*/

#include <string.h>
#include <stdlib.h>

char *my_remove_whitespace(char *str)
{
    int nb_spaces = 0;
    int j = 0;
    char *trim;

    for (int i = 0; str[i]; i++)
        if (str[i] == ' ')
            nb_spaces++;
    trim = malloc(sizeof(char) * (strlen(str) - nb_spaces + 1));
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ') {
            trim[j] = str[i];
            j++;
        }
    }
    trim[j] = '\0';
    return trim;
}