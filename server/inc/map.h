/*
** EPITECH PROJECT, 2021
** zappy [WSL: Ubuntu]
** File description:
** map
*/

#ifndef MAP_H_
#define MAP_H_

#define FOOD_DENSITY        0.5
#define LINEMATE_DENSITY    0.3
#define DERAUMERE_DENSITY   0.15
#define SIBUR_DENSITY       0.1
#define MENDIANE_DENSITY    0.1
#define PHIRAS_DENSITY      0.08
#define THYSTAME_DENSITY    0.05

typedef struct position {
    int x;
    int y;
}pos_t;

typedef struct tile_content {
    int nb_food;
    int nb_linemate;
    int nb_deraumere;
    int nb_sibur;
    int nb_mendiane;
    int nb_phiras;
    int nb_thystame;
    int nb_player;
}content_t;

typedef struct map_tile_s {
    pos_t coords;
    content_t content;
    struct map_tile_s *front;
    struct map_tile_s *back;
    struct map_tile_s *left;
    struct map_tile_s *right;
}tile_t;

#define map_t tile_t ***

map_t map_generate_ressources(map_t map, pos_t map_size);
tile_t *create_tile_links(tile_t *tile, map_t map, pos_t map_size);
map_t create_map(int x, int y);
content_t get_needed_ressources(map_t map, pos_t map_size);
content_t add_contents(content_t content1, content_t content2);
content_t init_content(void);
content_t substract_contents(content_t content1, content_t content2);

#endif /* !MAP_H_ */
