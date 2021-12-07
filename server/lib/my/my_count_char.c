/*
** EPITECH PROJECT, 2021
** myteams [WSL: Ubuntu]
** File description:
** my_count_char
*/

unsigned int my_count_char(char const *str, char const to_count)
{
    unsigned int count = 0;

    for (unsigned int i = 0 ; str[i] ; i++)
        if (str[i] == to_count)
            count++;
    return (count);
}