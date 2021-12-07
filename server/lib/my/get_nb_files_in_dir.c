/*
** EPITECH PROJECT, 2021
** myteams [WSL: Ubuntu]
** File description:
** get_nb_files_in_dir
*/

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

int get_nb_files_in_dir(char const *pathname)
{
    DIR *directory = NULL;
    struct dirent *directory_entry = NULL;
    int nb_files = 0;

    if ((directory = opendir(pathname)) == NULL) {
        printf("%s: %s\n", pathname, strerror(errno));
        return (-1);
    }
    errno = 0;
    while ((directory_entry = readdir(directory)) != NULL)
        nb_files++;
    if (directory_entry == NULL && errno != 0) {
        printf("readdir: %s\n", strerror(errno));
        return (-1);
    }
    if (closedir(directory) != 0) {
        printf("closedir: %s\n", strerror(errno));
        return (-1);
    }
    return (nb_files);
}