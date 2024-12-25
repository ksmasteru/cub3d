#ifndef MINI_MAP_H
#define MINI_MAP_H

#include "../includes/cub3d.h"
t_map fill_map_data();
int fill_square_pixels(t_map *map, t_image *img, int color);
int put_mini_map(t_data *data);
#endif