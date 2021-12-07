/*
** EPITECH PROJECT, 2021
** myteams [WSL: Ubuntu]
** File description:
** my_str_to_word_array
*/

#include <stddef.h>
#include <stdlib.h>
#include "my.h"

char **my_str_to_word_array(char const *str, char const sep)
{
    unsigned int nb_rows = my_count_char(str, sep) + 1;
    unsigned int nb_cols = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    char **arr = malloc(sizeof(char *) * (nb_rows + 1));

    for (i = 0 ; i < nb_rows ; i = i + 1, k = k + 1) {
        nb_cols = my_count_until_sep(str + k, sep);
        arr[i] = malloc(sizeof(char) * (nb_cols + 1));
        for (j = 0 ; j < nb_cols ; j = j + 1, k = k + 1)
            arr[i][j] = str[k];
        arr[i][j] = '\0';
    }
    arr[i] = NULL;
    return (arr);
}