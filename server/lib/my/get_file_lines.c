/*
** EPITECH PROJECT, 2021
** myteams [WSL: Ubuntu]
** File description:
** get_file_lines
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "my.h"

char **get_file_lines(char const *pathname)
{
    char *file_buffer = NULL;

    file_buffer = get_file_buffer(pathname);
    if (file_buffer == NULL)
        return (NULL);
    return (my_str_to_word_array(file_buffer, '\n'));
}