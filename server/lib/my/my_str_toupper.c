/*
** EPITECH PROJECT, 2021
** myftp [WSL: Ubuntu-20.04]
** File description:
** my_str_toupper
*/

#include <ctype.h>

char *my_str_toupper(char *str)
{
    for (int i = 0 ; str[i] ; i++)
        str[i] = toupper(str[i]);
    return str;
}