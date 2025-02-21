#include "../includes/mini_map.h"
extern int map[w][h];

void    fill_player_position(t_map *mini_map, t_image *img, t_data *data, int color)
{
    mini_map->p_x = (int)data->player->posx / texwidth * mini_map->w_pixels; // 12;
    mini_map->p_y = (int)data->player->posy / texheight * mini_map->h_pixels;
    printf("p_x %d p_y %d\n", mini_map->p_x, mini_map->p_y);
    fill_square_pixels(mini_map, img, color);
}
