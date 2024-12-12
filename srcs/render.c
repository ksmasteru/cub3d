#include "../includes/cub3d.h"
#include <math.h>
#define M_PI   3.14159265358979323846264338327950288
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

// each wall is 64*64.
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
double  calculate_distance(t_data *data, double cx, double cy, double castAngle)
{
    //TODO
    double distance;

    distance = sin(degToRad(castAngle)) * fabs(data->player->posy - cy); //  
    return distance;
}
// cast a ray of castAngle stops when it hits a wall
// return distance from player to the wal

// tracing horizontal intersections
double   horizontalraycast(t_data *data, int stripex, double castAngle)
{
    //ya iknowns ca isnt
    double len;
    int hit;
    double cx;
    double cy;
    hit = 0;
    if (castAngle >= 0 && castAngle <= 180)// going up handle if dir y = 0
    {
        printf("upward ray\n");
        cy = ((int)data->player->posy / texheight) * texheight - 1;
        cx = roundf(data->player->posy - cy) / tan(degToRad(castAngle));// this can be so small --> 0 ?
        cx += data->player->posx;
        /*printf("cy is %f cx is %f\n", cy, cx);
        printf("first cube horizontal intersection is at x:%d y:%d \n", (int)(cx/64)
        , (int)(cy / 64));
        exit(1);*/
    }
    
    // ray going down // shouldn't let angle be nagtive : 0-->360;
    else 
    {
        // handle angle = 0 ; 270 180 ; 90
        printf("down ward ray\n");
        cy = ((int)data->player->posy / texheight) * texheight + texheight;
        cx = roundf(cy - data->player->posy) / tan(degToRad(castAngle));
        //printf("cy is %f cx is %f\n", cy, cx);
        if (castAngle > 270)
            cx += data->player->posx;
        else if (castAngle < 270)
            cx = data->player->posx - cx;
        /*cx = roundf(cx) / 64;
        cy = roundf(cy) / 64;
        printf("first cube horizontal intersection is at x:%d y:%d \n", ((int)cx/64)
        , ((int)cy / 64));
        exit(1);*/
    }
    printf("first cube horizontal intersection is at x:%d y:%d \n", (int)cx / 64,
        (int)cy / 64);
    if (map[(int)cx / 64][(int)cy / 64] != 0)
        hit = 1;
    while (hit != 1)
    {
        printf("entered  hit loop\n");
        // traverse upward
        if (castAngle >= 0 && castAngle <= 180)
        {
            cy -= texheight;
            cx += texheight / tan(degToRad(castAngle));
        }
        else
        {
            cy +=texheight;
            if (castAngle > 270)
                cx += texheight / tan(degToRad(castAngle));
            else if (castAngle < 270)
                cx -= texheight / tan(degToRad(castAngle));
        }
        if (map[(int)cx / 64][(int)cy / 64] != 0)
            hit = 1;
    }
    
    printf("found a wall at %d %d\n", (int)cx / 64, (int)cy / 64);
    double distance = calculate_distance(data, cx, cx, castAngle);
    printf("horizontal distance to the wall is %f\n", distance);
    return (distance);
}

double   verticalraycast(t_data *data, double stripex, double castAngle)
{
    double  len;
    double  cx;
    double  cy;
    int     hit;
    double distance;
    int xa;
    hit = 0;
    
    printf("vertival ray casting with castangle %f\n", castAngle);
    if ((castAngle > 0 && castAngle < 90)
        || (castAngle > 270 && castAngle < 360))
    {
        // finding  adjacent  : current + 1 BIG DISTANCE
        cx = ((int)data->player->posx / texwidth) * texwidth + texwidth; // box x
        // small distance
        cy = fabs(tan(degToRad(castAngle)) * roundf(cx - data->player->posx));// opposent : round down second part?
        if (castAngle > 0 && castAngle < 90)
            cy = data->player->posy - cy; // box y;
        else
            cy = data->player->posy + cy;
        /*cx = roundf(cx) / 64;
        cy = roundf(cy) / 64;
        printf("first cube vertical intersection is at x:%d y:%d \n", ((int)cx/64)
        , ((int)cy / 64));
        exit(1);*/
    }
    else
    {
        // adjacent current - box
        cx = ((int)data->player->posx / texwidth) * texwidth - 1; 
        //printf("data->player->posx[%f] - cx[%f] = [%f\n", data->player->posx, cx, data->player->posx - cx);
        cy =  fabs(tan(degToRad(castAngle)) * (data->player->posx - cx));
        //printf("opposent value is %f\n", cy);
        /* fabs (tan) ? because we decided when to add and -
         !!!! when to add and when to substract to cy
        if (castAngle > 0 && castAngle < 90) // handled in the first if*/
        if (castAngle > 90 && castAngle < 180)
            cy = data->player->posy - cy;// !
        else
            cy = data->player->posy + cy;
        /*printf("first cube vertical intersection1 is at x:%d y:%d \n", ((int)cx)
        , ((int)cy));
        exit(1);*/
    }
    while (hit != 1) // xa stable.
    {
        if ((castAngle > 0 && castAngle < 180))
            cy -= fabs(tan(degToRad(castAngle)) * texheight);// BIG CY
        else
            cy += fabs(tan(degToRad(castAngle)) * texheight);
        if ((castAngle > 0 && castAngle < 90)
            || (castAngle > 270 && castAngle < 360))
            cx += texwidth;
        else
            cx -= texwidth;
        printf("current cx[%d] cy[%d]\n", (int)cx, (int)cy);
        if (map[(int)cx / 64][(int)cy / 64] != 0)
            hit = 1;
    }
    printf("found wall at [%d] [%d]\n", (int)cx / 64, (int)cy /64);
    distance = calculate_distance(data, cx, cx, castAngle);
    printf("vertical distance to the wall is %f\n", distance);
    return (distance);
}


void    put_wall(t_data *data, int stripex, double distance)
{
    // PUTS VERLINE .
    // distance ratio ?
    double slice_height;
    double projection_d = (WIDTH / 2) * tan(degToRad(30)); /*ambigous*/
    slice_height = texheight / distance * (projection_d);
    // drawing from middle of screen;
    int y_min =  HEIGHT / 2 - slice_height;
    int y_max = HEIGHT / 2 + slice_height;
    char *pixel;
    while (y_min != y_max)
    {
        pixel = data->img->adrs + data->img->size_line * y_min +
            stripex * (data->img->bpp / 8);
        *(int *)pixel = 0x00ff00;
        y_min++;
    }
}

double   raycast(t_data *data, int stripex, double castAngle)
{
    double horizontalray;
    double verticalray;
    // just use angle instead of vectors;
    // vertical raytracing
    verticalray = verticalraycast(data, stripex, castAngle);
    horizontalray = horizontalraycast(data, stripex, castAngle);
    if (verticalray < horizontalray)
        return (verticalray);
    return (horizontalray);
}

int render_walls(t_data *data)
{
    // TODO
    mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->player->posx
    ,  data->player->posy, 0xffffff);
    double wallheight;
    int i;
    double  sep_angle;
    double   castAngle;
    // DELETE OLD IMAGE AND CREATE A NEW ONE
    if (data->img->mlx_img)
    {
        mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
        data->img->mlx_img = NULL;
    }
    data->img->mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
    data->img->adrs = mlx_get_data_addr(data->img->mlx_img, &(data->img->bpp), &(data->img->size_line), &(data->img->endian));
    sep_angle = 60.0 / WIDTH;
    printf("angle between rays is %f\n", sep_angle);
    i = 0;
    castAngle = data->player->view_deg + 30;
    printf("cast angle is %f\n", castAngle);
    printf("at start player is at cube [%d] [%d]\n", (int)data->player->posx / 64,
    (int)data->player->posy / 64); 
    while (i < WIDTH)
    {
        wallheight = raycast(data, i, castAngle);
        put_wall(data, i, wallheight);
        castAngle -= sep_angle;
        i++;
    }
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->mlx_img, 0, 0);
    return (0);
}