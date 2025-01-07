#include "../includes/mini_map.h"
extern int map[w][h];
// fils an image addr pixels with a square

t_map fill_map_data()
{
    t_map map;

    map.mini_map_w = SCREEN_W / 4; // mixed_screen with map.
    map.mini_map_h = SCREEN_H / 4;
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
    it = 1;
    it1 = 1;
    while (it++ < map->w_pixels + 1)
    {
        p_y = map->p_y;
        pixel = img->adrs + img->size_line * p_y + p_x * (img->bpp) / 8; 
        *(int *)pixel = color;
        it1 = 1;
        while (it1++ < map->h_pixels + 1)
        {
            pixel = img->adrs + img->size_line * p_y++ + p_x * img->bpp / 8;
            *(int *)pixel = color;
        }
        p_x++;
    }
}

void    fill_player_position(t_map *mini_map, t_image *img, t_data *data, int color)
{
    mini_map->p_x = (int)data->player->posx / texwidth * mini_map->w_pixels; // 12;
    mini_map->p_y = (int)data->player->posy / texheight * mini_map->h_pixels;
    fill_square_pixels(mini_map, img, color);
}

int put_ray(double view_deg, t_data  *data, t_map *map)
{
    // TO BE FIXED LATER
    int x = 0;
    int y = 0;
    int player_x;
    int player_y;
    int wall_x;
    int wall_y;
    double slope;

    player_x = (int)data->player->posx / texwidth * map->w_pixels;
    player_y = (int)data->player->posy / texwidth * map->h_pixels;
    slope = tan(degToRad(view_deg));
    slope *= -1; // backward coordinates
    //printf("player_x is %d player_y %d slope %f\n", player_x, player_y, slope);
    for (x = player_x ; x < map->mini_map_w; x++)
    {
        y = slope * x - slope * player_x + player_y;
        if (y < 0)
        {
            //printf("negative y !!\n");
            continue;
        }
        //y += player_y;
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x0000ff);
    }
}

int put_rays(t_data *data, t_map *map)
{
    double view_deg;
    double max_deg;
    double low_deg;
    int i;

    i = 0;
    view_deg = data->player->view_deg;
    max_deg = view_deg + 30;
    if (max_deg > 360)
        max_deg = (int)max_deg % 360;
    low_deg = view_deg - 30;
    //if (low_deg < -180)
      //  low_deg = 180 - abs((int)view_deg) % 180;
    put_ray(view_deg, data, map);
    put_ray(max_deg, data, map);
    put_ray(low_deg, data, map);
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
            {//0x3333FF
                // paint 4 pixels wide and 4 pixels height.
                //printf("map p_x is %d p_y is %d\n", mini_map.p_x, mini_map.p_y);
                fill_square_pixels(&mini_map, data->mini_map, 0x3333FF); // struct for map variables.
            }
            else
                fill_square_pixels(&mini_map, data->mini_map, 0x99CCFF); // struct for map variables.
            j++;
        }
        i++;
    }
    fill_player_position(&mini_map, data->mini_map, data, 0xff0000);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->mini_map->mlx_img,0, 0);
    // mlx pixel put looks better.
    put_rays(data, &mini_map);
}