/*
** EPITECH PROJECT, 2021
** myteams [WSL: Ubuntu-20.04]
** File description:
** my_strarr_to_str
*/

#include "my.h"

char *my_strarr_to_str(char **args, const char *sep)
{
    char *args_str = "";

    if (!args)
        return "\0";
    for (int i = 0; args[i]; i++) {
        args_str = my_strdupcat(my_strdupcat(args_str, args[i]), sep);
    }
    return args_str;
}