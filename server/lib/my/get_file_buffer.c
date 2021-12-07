/*
** EPITECH PROJECT, 2021
** myteams [WSL: Ubuntu]
** File description:
** get_file_buffer
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"

char *get_file_buffer(char const *filepath)
{
    int fd = 0;
    unsigned int file_size = get_file_size(filepath);
    char *buffer = malloc(sizeof(char) * (file_size + 1));

    if ((fd = open(filepath, O_RDONLY)) == -1) {
        printf("Couldn't open file buffer.\n");
        return (NULL);
    }
    if (read(fd, buffer, file_size) == -1) {
        printf("Coudl'nt read file buffer.\n");
        return (NULL);
    }
    buffer[file_size] = '\0';
    close(fd);
    return (buffer);
}