/*
** EPITECH PROJECT, 2020
** PSU_navy_2019
** File description:
** Returns true if the given string is a positive numeric value, false otherwise
*/

#include <stdbool.h>

bool my_str_isnum_pos(char const *str)
{
    unsigned int i = 0;

    if (str[0] == 0)
        return (false);
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return (false);
        i = i + 1;
    }
    return (true);
}