#include "../includes/cub3d.h"
#include <math.h>


// each wall is 64*64.
//            cx = (int)(data->player->posx / texwidth) * texwidth + texwidth;

double angle;
int map[w][h]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
/*int map[w1][h1] = 
{
    {1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1}  
};*/

t_image     *get_xpm_img(t_data *data)
{
    int width;
    int height;

    t_image *img;

    img = malloc(sizeof(t_image));
    img->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, "./colorstone.xpm", &width, &height);
    if (img->mlx_img == NULL)
    {
        //printf("null img\n");
        exit(1);
    }
    img->adrs = mlx_get_data_addr(img->mlx_img, &(img->bpp), &(img->size_line), &(img->endian));
    return (img);
}

/*for side == 0 x_side hit*/
void    put_wall_side(t_data *data, int stripex, double distance, int side)
{
    int slice_height;
    char    *xpm_pixel;
    int     y_xpm;
    int     x_offset;
    int     pixel_repeat;
    int     i;
    int     ratio;
    slice_height = ((double)texheight / distance) * (projection_d); // this should be round up distance too small ? 
    t_image *xpm_img = get_xpm_img(data);
    if (side == 0)
    {
         x_offset = (int)data->player->hitx % texwidth; // logical error. : should get actual position of the hit.
         //printf("x offset is %d\n", x_offset);
         y_xpm = 0;
    }

    int y_min =  SCREEN_H / 2 - slice_height / 2;
    if (y_min <= 0)
        y_min = 1;
    int y_max = SCREEN_H / 2 + slice_height / 2;
    if (y_max >= SCREEN_H)
        y_max = SCREEN_H - 1;
    char *pixel;
    i = 0;
    pixel_repeat = abs(y_max - y_min) / texheight; // all verline will be drawn 
    if (pixel_repeat == 0)
    {
        ratio = texheight / abs(y_max - y_min);
        //printf("ratio is %d\n", ratio);
    }
    //printf("distance value is %f sliceheight value %d y_min value %d y_max value %d stripex value %d\n",distance, slice_height, y_min, y_max, stripex);
     // texheight > lineheight :: we scale up. :easier solution repeat the wall
    //printf("pixel repeat is %d\n", pixel_repeat);
    //printf("stripex value %d side value %d x_offset value %d\n",stripex, side, x_offset);
    int color;
    while (y_min != y_max)
    {
        //printf("ymin value is %d\n",- y_min);
        // find a way to get the scaling xpm_pixel
        xpm_pixel = xpm_img->adrs + xpm_img->size_line * y_xpm +
            x_offset * (xpm_img->bpp / 8);
        pixel = data->img->adrs + data->img->size_line * y_min +
            stripex * (data->img->bpp / 8);
        color = *(int *)xpm_pixel;
        *(int *)pixel = color;
        y_min++;
        if (pixel_repeat == 0) /*scale up == reapeat wall*/
            y_xpm += ratio;
        if ((pixel_repeat != 0) && (++i % pixel_repeat == 0))
            y_xpm++;
        if (y_xpm > texheight)
                y_xpm = 0;
        //printf("y_xpm is %d\n", y_xpm);
    }
    mlx_destroy_image(data->mlx_ptr, xpm_img->mlx_img);
    //free(xpm_img->mlx_img);
    free(xpm_img);
}

/*for side == 1 yside hit*/
void    put_wall(t_data *data, int stripex,  double distance, int side)
{
    // PUTS VERLINE .
    // distance ratio ?
    int     slice_height;
    char    *xpm_pixel;
    int     x_xpm;
    int     y_xpm;
    int     x_offset;
    int     pixel_repeat;
    int     ratio;
    int     i;
    char *pixel;
    if (distance > sqrt(MAP_H * MAP_H + MAP_W * MAP_W)) /*BOTH VERTICAL AND HORIZONAL RETURNED HIGH VALUE*/
    {
        distance = fabs(MAP_W - data->player->posx);
    }
    slice_height = ((double)texheight / distance) * (projection_d); // this should be round up distance too small ? 
    //printf("putwall distance is %f slice height is %f\n", distance);
    if (side == 0)
          return (put_wall_side(data, stripex, distance, side));
    t_image *xpm_img = get_xpm_img(data);
    if (side == 1)
    {
         x_offset = (int)data->player->hity % texheight;
         y_xpm = 0;
    }
    //printf("stripex value %d side value %d x_offset value %d\n",stripex, side, x_offset);
    int y_min =  SCREEN_H / 2 - slice_height / 2;
    if (y_min <= 0)
        y_min = 1;
    int y_max = SCREEN_H / 2 + slice_height / 2;
    if (y_max >= SCREEN_H)
        y_max = SCREEN_H - 1;
    i = 0;
    pixel_repeat = slice_height / texheight; // all verline will be drawn 
    if (pixel_repeat == 0)
    {
        ratio = texheight / slice_height;
        //printf("ratio is %d\n", ratio);
    }
    //printf("stripex value %d side value %d x_offset value %d\n",stripex, side, x_offset);
    int color;
    while (y_min != y_max)
    {
        xpm_pixel = xpm_img->adrs + xpm_img->size_line * y_xpm +
            x_offset * (xpm_img->bpp / 8);
        pixel = data->img->adrs + data->img->size_line * y_min +
            stripex * (data->img->bpp / 8);
        color = *(int *)xpm_pixel;
        *(int *)pixel = color;
        y_min++;
        if (pixel_repeat == 0) /*scale up == reapeat wall*/
            y_xpm += ratio;
        if ((pixel_repeat != 0) && (++i % pixel_repeat == 0))
            y_xpm++;
        if (y_xpm > texheight)
            y_xpm = 0;
    }
    mlx_destroy_image(data->mlx_ptr, xpm_img->mlx_img);
    //free(xpm_img->mlx_img);
    free(xpm_img);
}

double   raycast(t_data *data, double castAngle, int *side)
{
    double horizontalray;
    double verticalray;
    double  ver_hitx;
    double  ver_hity;
    if (castAngle < 0)
        castAngle += 360.0;
    if (castAngle == 0 || castAngle == 180.0 || castAngle == 360)
    {
        *side = 0;
        return (x_axis_raycast(data, castAngle));
    }
    else if (castAngle == 90.0 || castAngle == 270.0)
    {
        *side = 1;
        return (y_axis_raycast(data, castAngle));
    }
    verticalray = verticalraycast(data, castAngle);
    ver_hitx = data->player->hitx;
    ver_hity = data->player->hity;
    horizontalray = horizontalraycast(data, castAngle);
    if (verticalray < horizontalray)
    {
        //printf("for angle %f vertical height is %f because horizontal is %f\n", castAngle, verticalray, horizontalray);
        *side = 0;
        data->player->hitx = ver_hitx;
        data->player->hity = ver_hity;
        return (verticalray) * cos(degToRad(data->player->beta_angle));
    }
    *side = 1;
    //}
    //printf("distance to the wall is %f\n", horizontalray);
    //printf("corrected distance to the wall is %f\n", horizontalray * cos(degToRad(data->player->beta_angle)));
    //printf("for angle %f horizontal height is %f because vertical was %f\n", castAngle, horizontalray,verticalray);
    return (horizontalray) * cos(degToRad(data->player->beta_angle));
}

void set_new_img(t_data *data)
{
    if (data->img->mlx_img != NULL)
    {
        mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
        //free(data->img->mlx_img);
        data->img->mlx_img = NULL;
    }
    data->img->mlx_img = mlx_new_image(data->mlx_ptr, SCREEN_W, SCREEN_H);
    data->img->adrs = mlx_get_data_addr(data->img->mlx_img, &(data->img->bpp), &(data->img->size_line), &(data->img->endian));
}

int render_walls(t_data *data)
{
    double wallheight;
    int i;
    double  sep_angle;
    double   castAngle;
    int side;
    i = 0;

    sep_angle = (double)FOW / SCREEN_W;
    castAngle = data->player->view_deg + (double)FOW / 2;
    angle = data->player->view_deg;
    update_ray_dir(&(data->ray), data->player->view_deg);
    //printf("cast angle is %f\n", castAngle);
    data->player->beta_angle = (double)FOW / 2; // works better than FOW / 2 somehow.
    //printf("start boxX[%d] boxY[%d]\n", (int)data->player->posx / 64, (int)data->player->posy / 64);
    //printf("beta angle is %f\n", data->player->beta_angle);
    set_new_img(data);
    while (i < SCREEN_W)
    {
        //printf("cast angle is %f\n", castAngle);
        wallheight = raycast(data, castAngle, &side);
        //printf("for cast angle %f wallheight is %f side is %d\n", castAngle, wallheight, side);
        //printf("stripex is %d side is %d\n", i, side);
        //if (castAngle > -12 && castAngle < -8)
        put_wall(data, i, wallheight, side);
        castAngle -= sep_angle;
        data->player->beta_angle -= sep_angle;
        i++;
    }
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->mlx_img, 0, 0);
    show_player_data(data); // write on top of new img
    put_mini_map(data);
    return (0);
}