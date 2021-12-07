/*
** EPITECH PROJECT, 2021
** myteams [WSL: Ubuntu]
** File description:
** my_intlen
*/


unsigned int my_intlen(int nb)
{
    unsigned int len = 0;

    if (nb == 0)
        return (1);
    while (nb != 0) {
        len++;
        nb /= 10;
    }
    return (len);
}