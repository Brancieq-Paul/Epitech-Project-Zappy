/*
** EPITECH PROJECT, 2021
** myteams [WSL: Ubuntu]
** File description:
** my_count_until_sep
*/

unsigned int my_count_until_sep(char const *str, char const sep)
{
    unsigned int count = 0;

    for (unsigned int i = 0 ; str[i] && str[i] != sep ; i++)
        count++;
    return (count);
}