/*
** EPITECH PROJECT, 2021
** B-YEP-410-RUN-4-1-zappy-julien.pause
** File description:
** check_cmd_time
*/

#include <sys/time.h>
#include "server.h"
#include "client.h"

double get_time_from_freq(int time, int freq)
{
    return (double)time / (double)freq;
}

long get_current_time(void)
{
    struct timeval tv;
    long current_time;

    gettimeofday(&tv, NULL);
    current_time = tv.tv_sec * (uint64_t)1000000 + tv.tv_usec;
    return current_time;
}

bool is_cmd_time_end(client_t *client)
{
    long time_current;
    long time_tmp;

    time_current = get_current_time();
    time_tmp = client->cmd_time * 1000000;
    if (time_current - client->launched_cmd >= time_tmp) {
        return (true);
    }
    return (false);
}