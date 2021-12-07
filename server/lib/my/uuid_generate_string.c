/*
** EPITECH PROJECT, 2021
** myteams [WSL: Ubuntu]
** File description:
** uuid_generate_string
*/

#include <uuid/uuid.h>
#include <stdlib.h>

char *uuid_generate_string(void)
{
    uuid_t uuid;
    char *str = malloc(sizeof(char) * UUID_STR_LEN);

    uuid_generate_time_safe(uuid);
    uuid_unparse_lower(uuid, str);
    return str;
}