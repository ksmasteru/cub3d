#include "../includes/mini_map.h"
extern int map[w][h];
// fils an image addr pixels with a square

t_map fill_map_data()
{
    t_map map;

    map.mini_map_w = SCREEN_W / 5; // mixed_screen with map.
    map.mini_map_h = SCREEN_H / 5;
    while (map.mini_map_w % w != 0)
        map.mini_map_w++;
    while (map.mini_map_h % h != 0)
        map.mini_map_h++;
    map.w_pixels = map.mini_map_w / w;
    map.h_pixels = map.mini_map_h / h;
    map.p_x = 0;
    map.p_y = 0;
    return (map);
}

int fill_square_pixels(t_map *map, t_image *img, int color)
{
    int it;
    int it1;
    char    *pixel;
    int p_y;
    int p_x;

    p_y = map->p_y;
    p_x = map->p_x;
    it = 0;
    it1 = 0;
    while (it++ < map->w_pixels)
    {
        p_y = map->p_y;
        pixel = img->adrs + img->size_line * p_y + p_x * (img->bpp) / 8; 
        *(int *)pixel = color;
        it1 = 0;
        while (it1++ < map->h_pixels)
        {
            pixel = img->adrs + img->size_line * p_y++ + p_x * img->bpp / 8;
            *(int *)pixel = color;
        }
        p_x++;
    }
}

int put_mini_map(t_data *data)
{
     // an image that will be put on the screen should be by scale of scrren 
    int i;
    int j;
    i  = 0;
    j  = 0;
    t_map mini_map = fill_map_data();
    char    *pixel;
    if (data->mini_map->mlx_img != NULL)
        mlx_destroy_image(data->mlx_ptr, data->mini_map->mlx_img);
    data->mini_map->mlx_img = mlx_new_image(data->mlx_ptr, mini_map.mini_map_w, mini_map.mini_map_h);
    data->mini_map->adrs = mlx_get_data_addr(data->mini_map->mlx_img, &(data->mini_map->bpp), &(data->mini_map->size_line),
        &data->mini_map->endian);
    // each grid is 2 pixel height / width
    while (i < w)
    {
        j = 0; //THIS IS FOR Y
        mini_map.p_y = i * mini_map.h_pixels;// this will p_y start for loop
        while(j < h)
        {
            mini_map.p_x = j * mini_map.w_pixels;
            if (map[i][j] != 0)
            {
                // paint 4 pixels wide and 4 pixels height.
                printf("map p_x is %d p_y is %d\n", mini_map.p_x, mini_map.p_y);
                fill_square_pixels(&mini_map, data->mini_map, 0x00ff00); // struct for map variables.
            }
            else
                fill_square_pixels(&mini_map, data->mini_map, 0xffffff); // struct for map variables.
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->mini_map->mlx_img,0, 0);
}