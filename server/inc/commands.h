/*
** EPITECH PROJECT, 2021
** server [WSL: Ubuntu]
** File description:
** commands
*/

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "egg.h"

typedef struct serv_s serv_t;
typedef struct client_s client_t;

#define FORWARD_TIME        7
#define RIGHT_TIME          7
#define LEFT_TIME           7
#define LOOK_TIME           7
#define INVENTORY_TIME      1
#define BROADCAST_TIME      7
#define CONNECT_NBR_TIME    0
#define FORK_TIME           42
#define EJECT_TIME          7
#define TAKE_TIME           7
#define SET_TIME            7
#define INCANTATION_TIME    300

#define INVENTORY_SIZE      70
#define ELEVATION_MSG       strdup("Elevation underway")

typedef struct cmds_s {
    char *name;
    void (*func)(client_t *client, serv_t *serv, char *arg);
    int time;
} cmds_t;

typedef struct object_prop_s {
    char *type;
    int *inv_nb;
    int *c_nb;
}object_prop_t;

typedef struct orientation_s {
    direction_t	direction;
    int	top_left;
    int	top_center;
    int	top_right;
    int	bot_left;
    int	bot_center;
    int bot_right;
    int	mid_left;
    int	mid_right;
}orientation_t;

typedef struct incantation_s {
    int	level;
    int	nb_players;
    int	linemate;
    int	deraumere;
    int	sibur;
    int	mendiane;
    int	phiras;
    int	thystame;
}incantation_t;

cmds_t **create_ia_cmds_tab(void);
cmds_t **create_graph_cmds_tab(void);
char *get_tile_ressources(content_t content);
void look_cmd(client_t *client, serv_t *serv, char *arg);
void forward_cmd(client_t *client, serv_t *serv, char *arg);
void left_cmd(client_t *client, serv_t *serv, char *arg);
void right_cmd(client_t *client, serv_t *serv, char *arg);
void inventory_cmd(client_t *client, serv_t *serv, char *arg);
void connect_nbr_cmd(client_t *client, serv_t *serv, char *arg);
void take_cmd(client_t *client, serv_t *serv, char *arg);
void set_cmd(client_t *client, serv_t *serv, char *arg);
void eject_cmd(client_t *client, serv_t *serv, char *arg);
bool incantation_checks(client_t *client, serv_t *serv, bool send_message);
void incantation_cmd(client_t *client, serv_t *serv, char *arg);
void broadcast_cmd(client_t *client, serv_t *serv, char *arg);
void fork_cmd(client_t *client, serv_t *serv, char *arg);
void eht_cmd(client_t *client, int egg_nbr);
void ebo_cmd(serv_t *serv, int egg_nbr);
void pbc_cmd(client_t *client, int nb_player, char *msg);
void pex_cmd(serv_t *serv, int nb_player);
void pin_cmd(client_t *client, serv_t *serv, char *arg);
void seg_cmd(client_t *client, char *team_name);
void sbp_cmd(client_t *client, serv_t *serv, char *arg);
void smg_cmd(client_t *client, char *message);
void sgt_cmd(client_t *client, serv_t *serv, char *arg);
void plv_cmd(client_t *client, serv_t *serv, char *arg);
void ppo_cmd(client_t *client, serv_t *serv, char *arg);
void pnw_cmd(client_t *client, client_t *player);
void mct_cmd(client_t *client, serv_t *serv);
void edi_cmd(client_t *client, int egg_nbr);
void tna_cmd(client_t *client, serv_t *serv, char *arg);
void bct_cmd(client_t *client, serv_t *serv, char *arg);
void msz_cmd(client_t *client, serv_t *serv, char *arg);
void pdi_cmd(serv_t *serv, int nb_player);
void pic_cmd(client_t *client, serv_t *serv);
void enw_cmd(egg_t *egg, serv_t *serv, int player_nb);
void graph_set_cmd(client_t *client, serv_t *serv, int nbr_player);
void graph_map_set_cmd(client_t *client, serv_t *serv, pos_t coords);
void send_graph_cmd(serv_t *serv, int nb, char *msg);
void pie_cmd(client_t *client, serv_t *serv, int incant_state);

#endif /* !COMMANDS_H_ */
