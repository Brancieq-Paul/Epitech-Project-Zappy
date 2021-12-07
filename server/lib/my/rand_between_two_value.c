/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** rand_between_two_value
*/

#include <stdlib.h>

int rand_between_two_value(int lower, int upper)
{
    return  (rand() % (upper - lower + 1)) + lower;
}
