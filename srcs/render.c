#include "../includes/cub3d.h"
#include <math.h>
#define M_PI   3.14159265358979323846264338327950288
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

// each wall is 64*64.
//            cx = (int)(data->player->posx / texwidth) * texwidth + texwidth;

int map[8][8]={
{1, 1 , 1, 1, 1, 1, 1, 1},
{1, 0 , 0, 0, 0, 0, 0, 1},
{1, 0 , 0, 0, 0, 0, 0, 1},
{1, 0 , 0, 0, 0, 0, 0, 1},
{1, 0 , 0, 0, 0, 0, 0, 1},
{1, 0 , 0, 0, 0, 0, 0, 1},
{1, 0 , 0, 0, 0, 0, 0, 1},
{1, 1 , 1, 1, 1, 1, 1, 1},
};


void    put_wall(t_data *data, int stripex,  double distance)
{
    // PUTS VERLINE .
    // distance ratio ?
    int slice_height;
    int projection_d = (WIDTH / 2) * tan(degToRad(30)); /*ambigous*/
    //printf("putwall distance is %f\n", distance);
    slice_height = (texheight / distance) * (projection_d); // this should be round up distance too small ? 
    //printf("slice height is %d\n", slice_height);
    // drawing from middle of screen;
    int y_min =  HEIGHT / 2 - slice_height / 2;
    if (y_min <= 0)
        y_min = 1;
    int y_max = HEIGHT / 2 + slice_height / 2;
    if (y_max >= HEIGHT)
        y_max = HEIGHT - 1;
    char *pixel;
    while (y_min != y_max)
    {
        //printf("ymin value is %d\n", y_min);
        pixel = data->img->adrs + data->img->size_line * y_min +
            stripex * (data->img->bpp / 8);
        *(int *)pixel = 0x00ff00;
        y_min++;
    }
}

double   raycast(t_data *data, double castAngle)
{
    double horizontalray;
    double verticalray;

    if (castAngle < 0)
        castAngle += 360;
    if (castAngle == 0 || castAngle == 180)
        return (x_axis_raycast(data, castAngle));
    else if (castAngle == 90 || castAngle == 270)
        return (y_axis_raycast(data, castAngle));
    verticalray = verticalraycast(data, castAngle);
    horizontalray = horizontalraycast(data, castAngle);
    if (verticalray < horizontalray)
    {
        printf("for angle %f vertical height is %f because horizontal is %f\n", castAngle, verticalray, horizontalray);
        return (verticalray * cos(degToRad(data->player->beta_angle)));
    }
    //}
    //printf("distance to the wall is %f\n", horizontalray);
    //printf("corrected distance to the wall is %f\n", horizontalray * cos(degToRad(data->player->beta_angle)));
    printf("for angle %f horizontal height is %f because horizontal was %f\n", castAngle, horizontalray,verticalray);
    return (horizontalray * cos(degToRad(data->player->beta_angle)));
}

void set_new_img(t_data *data)
{
    if (data->img->mlx_img)
    {
        mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
        data->img->mlx_img = NULL;
    }
    data->img->mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
    data->img->adrs = mlx_get_data_addr(data->img->mlx_img, &(data->img->bpp), &(data->img->size_line), &(data->img->endian));
}

int render_walls(t_data *data)
{
    double wallheight;
    int i;
    double  sep_angle;
    double   castAngle;

    i = 0;
    sep_angle = 60.0 / WIDTH;
    castAngle = data->player->view_deg + 30;
    data->player->beta_angle = 30;
    //printf("start boxX[%d] boxY[%d]\n", (int)data->player->posx / 64, (int)data->player->posy / 64);
    set_new_img(data);
    while (i < WIDTH)
    {
        //printf("cast angle is %f\n", castAngle);
        wallheight = raycast(data, castAngle);
        //printf("for cast angle %f wallheight is %f\n", castAngle, wallheight);
        put_wall(data, i, wallheight);
        castAngle -= sep_angle;
        data->player->beta_angle -= sep_angle;
        i++;
    }
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->mlx_img, 0, 0);
    return (0);
}