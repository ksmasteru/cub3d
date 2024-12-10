#include "../includes/cub3d.h"
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

// cast a ray of castAngle stops when it hits a wall
// return distance from player to the wal

// tracing horizontal intersections
double   horizontalraycast(t_data *data, double stripex, double castAngle)
{
    double len;
    int hit;

    hit = 0;
    // raydiry
    if (castAngle >= 0 && castAngle <= 180)
        // going up
    else
        // going down
    while (hit != 1)
    {
        
    }
}

double   verticalraycast(t_data *data, double stripex, double castAngle)
{
    double len;
}

double   raycast(t_data *data, int stripex, double castAngle)
{
    double horizotalray;
    double verticalray;
    // just use angle instead of vectors;
    // vertical raytracing
    verticalray = verticalraycast(data, stripex, castAngle);
    horizotalray = horizotalraycast(data, stripex, castAngle);
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

    sep_angle = 60.0 / WIDTH;
    i = 0;
    castAngle = data->player->view_deg + 30;
    while (i < WIDTH)
    {
        wallheight = raycast(data, i, castAngle);
        castAngle -= sep_angle;
    }
}