/*
** EPITECH PROJECT, 2021
** B-NWP-400-RUN-4-1-myteams-dorian.beasse
** File description:
** error_handling
*/

#include "server.h"

void handle_opt(char **av)
{
    char opt[7] = {'p', 'x', 'y', 'n', 'c', 'f', 0};
    int i = 0;

    if (av[0][1] == 0 || av[0][2] != 0)
        exit(EXIT_FAILURE);
    for (; opt[i] != av[0][1]; i++)
        if (opt[i] == 0)
            exit(EXIT_ERROR);
}

void check_required_opt(char **av)
{
    char const *opt[7] = {"-p", "-x", "-y", "-n", "-c", 0};

    for (int i = 0, j = 0; opt[i]; i++) {
        for (; av[j] && (strcmp(av[j], opt[i]) != 0);)
            j++;
        if (!av[j] || strcmp(av[j], opt[i]) != 0)
            exit(EXIT_ERROR);
        j = 0;
    }
}

int skip_opt_n(char **av, int i)
{
    if (av == 0 && av[i] == 0)
        return (i);
    if (strcmp(av[i], "-n") == 0) {
        for (int j = i+1; av[j] && av[j][0] != '-'; j++)
            i++;
        i++;
    }
    return (i);
}

void error_handling(int ac, char **av)
{
    if (ac < 2) {
        printf(HELP_MESSAGE);
        exit(EXIT_ERROR);
    }
    if (strcmp(av[1], "-help") == 0) {
        printf(HELP_MESSAGE);
        exit(0);
    }
    check_required_opt(av);
    for (int i = 1; av[i]; ++i) {
        i = skip_opt_n(av, i);
        if (av[i] && av[i][0] != '-')
            exit(EXIT_ERROR);
        if (av[i][0] == '-') {
            handle_opt(av+i);
            i++;
        }
    }
}