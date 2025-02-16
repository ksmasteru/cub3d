#include "../includes/cub3d.h"
#include <math.h>
#define M_PI   3.14159265358979323846264338327950288
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

extern int map[w][h];

double   horizontalraycast_1(t_data *data, double castAngle, int i)
{
    double len;
    int hit;
    double rx;
    double ry;
    hit = 0;
    double xa;
    double ya;
    double distance;

    xa = texwidth;
    ya = tan(degToRad(castAngle)) * texheight * -1; // negative ya.
    rx = (((int)data->player->posx >> 6) << 6) + texwidth; // box x
    data->player->box_x = (int)rx >> 6;
    ry = tan(degToRad(castAngle)) * (rx - data->player->posx);
    ry = data->player->posy - fabs(ry); // pos tan no need for fabs.
    data->player->box_y = (int)ry >> 6;
    if (ry < 0)
    {
        //printf("!!!!!!!!!!at angle %f ry is too high %f!!!!!!!!!!!!!\n", castAngle, ry);
        return (1e30);
    }

    while (map[data->player->box_y][data->player->box_x] == 0)
    {
        ry += ya;
        rx += xa;
        if (ry < 0)
            return (1e30);
        data->player->box_x = (int)rx >> 6;
        data->player->box_y = (int)ry >> 6;
    }
    data->player->hor_hitx[i] = rx;
    data->player->hor_hity[i] = ry;
    distance = calculate_distance(data, rx, ry, castAngle);
    return (distance);
}

// 90, 180 : -x -y
double   horizontalraycast_2(t_data *data, double castAngle, int i)
{
    double len;
    int hit;
    double rx;
    double ry;
    hit = 0;
    double xa;
    double ya;
    double distance;

    xa = texwidth * -1;    
    ya = tan(degToRad(castAngle)) * texheight; //neg tan
    rx = ((int)data->player->posx >> 6) << 6;
    data->player->box_x = (int)(rx - 1) >> 6;
    ry =  tan(degToRad(castAngle)) * (data->player->posx - rx);
    ry = data->player->posy - fabs(ry); // negative tan : could + ry
    data->player->box_y = (int)ry >> 6;
    if (ry < 0) /*enough ?*/
    {
        return (1e30);
    }
    while (map[data->player->box_y][data->player->box_x] == 0)
    {
        ry += ya;
        rx += xa;
        if (ry < 0)
            return (1e30);
        data->player->box_x = (int)(rx - 1) >> 6;
        data->player->box_y = (int)ry >> 6;
    }
    data->player->hor_hitx[i] = rx;
    data->player->hor_hity[i] = ry;
    distance = calculate_distance(data, rx, ry, castAngle);
    return (distance);
}
// 180 , 270 : -x + y 
double   horizontalraycast_3(t_data *data, double castAngle, int i)
{
    double len;
    int hit;
    double rx;
    double ry;
    hit = 0;
    double xa;
    double ya;
    double distance;

    xa = texwidth * -1;
    ya = tan(degToRad(castAngle)) * texheight; //pos tan pos ya
    rx = ((int)data->player->posx >> 6) << 6;
    data->player->box_x = (int)(rx - 1) >> 6;
    ry =  tan(degToRad(castAngle)) * (data->player->posx - rx);
    ry = data->player->posy + fabs(ry);
    data->player->box_y = (int)ry >> 6;
    if (ry > MAP_H) /*enough ?*/
    {
        return (1e30);
    }
    while (map[data->player->box_y][data->player->box_x] == 0)
    {
        ry += ya;
        rx += xa;
        if (ry > MAP_W)
            return (1e30);
        data->player->box_x = (int)(rx - 1) >> 6; // round-down-up then >> ?
        data->player->box_y = (int)ry >> 6;
    }
    data->player->hor_hitx[i] = rx;
    data->player->hor_hity[i] = ry;
    distance = calculate_distance(data, rx, ry, castAngle);
    return (distance);
    
}
// 270, 360 : +x +y
double   horizontalraycast_4(t_data *data, double castAngle, int i)
{
    double len;
    int hit;
    double rx;
    double ry;
    double xa;
    double ya;
    double distance;

    hit = 0;
    xa = texwidth;
    ya = tan(degToRad(castAngle)) * texheight * -1; // neg tan pos ya
    rx = (((int)data->player->posx >> 6) << 6) + texwidth; // box x
    data->player->box_x = (int)rx >> 6;
    ry = tan(degToRad(castAngle)) * (rx - data->player->posx); // something is wrong in here
    ry = data->player->posy + fabs(ry); // pos tan 
    //printf("horizontal casting ry value is %f\n", ry); // make smaller map
    data->player->box_y = (int)ry >> 6;
    if (ry > MAP_H) /*enough ?*/
    {
        //printf("!!!!!!!!!!at angle %f ry is too high %f!!!!!!!!!!!!!\n", castAngle, ry);
        return (1e30);
    }
    while (map[data->player->box_y][data->player->box_x] == 0)
    {
        ry += ya;
        if (ry > MAP_W)
            return (1e30);
        rx += xa;
        data->player->box_x = (int)(rx) >> 6;
        data->player->box_y = (int)ry >> 6;
    }
    distance = calculate_distance(data, rx, ry, castAngle);
    data->player->hor_hitx[i] = rx;
    data->player->hor_hity[i] = ry;
    return (distance);
}