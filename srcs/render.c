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
double   horizontalraycast(t_data *data, int stripex, double castAngle)
{
    //ya iknowns ca isnt
    double len;
    int hit;
    double cx;
    double cy;
    hit = 0;
    // raydiry
    castAngle = 230; // for testing
    if (castAngle >= 0 && castAngle <= 180)// going up handle if dir y = 0
    {
        printf("upward ray %d\n");
        // defining the first horizontal intersection
        cy = ((int)data->player->posy / texheight) * texheight - 1;
        cx = (data->player->posy - cy) / tan(castAngle);
        cx += data->player->posx;
        /*printf("cy is %f cx is %f\n", cy, cx);
        printf("first cube horizontal intersection is at x:%d y:%d \n", ((int)cx/64)
        , ((int)cy / 64));
        exit(1);*/
    }
    
    // ray going down // shouldn't let angle be nagtive : 0-->360;
    else 
    {
        // handle angle = 0 ; 270 180 ; 90
        printf("down ward ray\n");
        cy = ((int)data->player->posy / texheight) * texheight + texheight;
        cx = (cy - data->player->posy) / tan(castAngle);
        printf("cy is %f cx is %f\n", cy, cx);
        if (castAngle > 270)
            cx += data->player->posx;
        else if (castAngle < 270)
            cx = data->player->posx - cx;
        printf("first cube horizontal intersection is at x:%d y:%d \n", ((int)cx/64)
        , ((int)cy / 64));
        exit(1);
    }
    while (hit != 1)
    {
        printf("entered  hit loop\n");
        exit(1);
    }
    return (0.0);
}

double   verticalraycast(t_data *data, double stripex, double castAngle)
{
    double len;
    return (0.0);
}

double   raycast(t_data *data, int stripex, double castAngle)
{
    double horizotalray;
    double verticalray;
    // just use angle instead of vectors;
    // vertical raytracing
    verticalray = verticalraycast(data, stripex, castAngle);
    horizotalray = horizontalraycast(data, stripex, castAngle);
    return (0.0);
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
    printf("angle between rays is %f\n", sep_angle);
    i = 0;
    castAngle = data->player->view_deg + 30;
    printf("cast angle is %f\n", castAngle);
    printf("at start player is at cube [%d] [%d]\n", (int)data->player->posx / 64,
    (int)data->player->posy / 64);
    while (i < WIDTH)
    {
        wallheight = raycast(data, i, castAngle);
        castAngle -= sep_angle;
        i++;
    }
    return (0);
}