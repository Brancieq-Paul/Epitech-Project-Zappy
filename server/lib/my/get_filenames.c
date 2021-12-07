/*
** EPITECH PROJECT, 2021
** myteams [WSL: Ubuntu]
** File description:
** get_filenames_in_dir.c
*/

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "my.h"

static char **allocate_filenames(char const *dir_path);
static char **get_filenames_from_dir(char const *dir_path, DIR *dir);

char **get_filenames(char const *dir_path)
{
    char **file_names = NULL;
    DIR *dir = NULL;

    dir = opendir(dir_path);
    if (dir == NULL) {
        printf("%s: %s\n", dir_path, strerror(errno));
        return (NULL);
    }
    file_names = get_filenames_from_dir(dir_path, dir);
    if (closedir(dir) == -1) {
        printf("Couldn't close directoy for some reason.\n");
        return (NULL);
    }
    return (file_names);
}

static char **get_filenames_from_dir(char const *dir_path, DIR *dir)
{
    char **file_names = NULL;
    char *file_name = NULL;
    struct dirent *dir_entry = NULL;
    unsigned int file_name_index = 0;

    file_names = allocate_filenames(dir_path);
    if (file_names == NULL)
        return (NULL);
    while ((dir_entry = readdir(dir)) != NULL) {
        file_name = dir_entry->d_name;
        if (strcmp(file_name, ".") == 0 || strcmp(file_name, "..") == 0)
            continue;
        file_names[file_name_index] = strdup(file_name);
        file_name_index++;
    }
    file_names[file_name_index] = NULL;
    return (file_names);
}

static char **allocate_filenames(char const *dir_path)
{
    char **file_names = NULL;
    int nb_files = 0;

    nb_files = get_nb_files_in_dir(dir_path);
    if (nb_files < 0)
        return (NULL);
    file_names = malloc(sizeof(char *) * (nb_files + 1));
    if (file_names == NULL) {
        printf("Couldn't allocate memory for file names in directory.\n");
        return (NULL);
    }
    return (file_names);
}