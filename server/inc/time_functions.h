/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** time_functions
*/

#ifndef TIME_FUNCTIONS_H_
#define TIME_FUNCTIONS_H_

#include "client.h"

double get_time_from_freq(int time, int freq);
long get_current_time(void);
bool is_cmd_time_end(client_t *client);

#endif /* !TIME_FUNCTIONS_H_ */
