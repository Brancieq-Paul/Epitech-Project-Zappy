/*
** EPITECH PROJECT, 2021
** myteams [WSL: Ubuntu]
** File description:
** my_revstr
*/

#include <string.h>

char *my_revstr(char *str)
{
    int i = 0;
    int str_len = 0;
    char tmp = ' ';

    str_len = strlen(str);
    while (i < (str_len / 2)) {
        tmp = str[i];
        str[i] = str[(str_len - i - 1)];
        str[(str_len - i - 1)] = tmp;
        i = i + 1;
    }
    return (str);
}