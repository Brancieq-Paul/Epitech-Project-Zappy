/*
** EPITECH PROJECT, 2021
** zappy [WSL: Ubuntu]
** File description:
** create_tile_links
*/

#include "map.h"
#include <stdio.h>

static tile_t *link_front(pos_t tile_coords, map_t map, pos_t map_size);
static tile_t *link_left(pos_t tile_coords, map_t map, pos_t map_size);
static tile_t *link_back(pos_t tile_coords, map_t map, pos_t map_size);
static tile_t *link_right(pos_t tile_coords, map_t map, pos_t map_size);

tile_t *create_tile_links(tile_t *tile, map_t map, pos_t map_size)
{
    tile->front = link_front(tile->coords, map, map_size);
    tile->back = link_back(tile->coords, map, map_size);
    tile->left = link_left(tile->coords, map, map_size);
    tile->right = link_right(tile->coords, map, map_size);
    return tile;
}

static tile_t *link_front(pos_t tile_coords, map_t map, pos_t map_size)
{
    pos_t front = tile_coords;

    if (front.y == 0)
        front.y = map_size.y - 1;
    else
        front.y--;
    return map[front.y][front.x];
}

static tile_t *link_back(pos_t tile_coords, map_t map, pos_t map_size)
{
    pos_t back = tile_coords;

    if (back.y == map_size.y - 1)
        back.y = 0;
    else
        back.y++;
    return map[back.y][back.x];
}

static tile_t *link_left(pos_t tile_coords, map_t map, pos_t map_size)
{
    pos_t left = tile_coords;

    if (left.x == 0)
        left.x = map_size.x - 1;
    else
        left.x--;
    return map[left.y][left.x];
}

static tile_t *link_right(pos_t tile_coords, map_t map, pos_t map_size)
{
    pos_t right = tile_coords;

    if (right.x == map_size.x - 1)
        right.x = 0;
    else
        right.x++;
    return map[right.y][right.x];
}