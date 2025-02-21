#include "../includes/cub3d.h"
#include <math.h>
#define M_PI   3.14159265358979323846264338327950288
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

extern int map[w][h];

double  vertical_casting_1(t_data *data, double castangle, int i)
{
    t_rayvars ray_data;
    
    ray_data.xa = texwidth / tan(degToRad(castangle));
    ray_data.ya = texheight * -1;
    ray_data.ry = ((int)data->player->posy >> 6) << 6;
    data->player->box_y = (int)(ray_data.ry - 1) >> 6;
    ray_data.rx = ((data->player->posy - ray_data.ry) / tan(degToRad(castangle)));
    ray_data.rx = data->player->posx + fabs(ray_data.rx);
    data->player->box_x = (int)ray_data.rx >> 6;
    if (ray_data.rx > MAP_W)
         return (1e30);
    while (map[data->player->box_y][data->player->box_x] == 0)
    {
        ray_data.ry += ray_data.ya;
        ray_data.rx += ray_data.xa;
        if (ray_data.rx > MAP_W)
            return (1e30);
        data->player->box_y = (int)(ray_data.ry - 1) >> 6;
        data->player->box_x = (int)ray_data.rx >> 6;
    }
    data->player->ver_hitx[i] = ray_data.rx;
    data->player->ver_hity[i] = ray_data.ry;
    data->player->wall_type = map[data->player->box_y][data->player->box_x];
    return (calculate_distance(data, ray_data.rx, ray_data.ry, castangle));
}

double  vertical_casting_2(t_data *data, double castangle, int i)
{
    t_rayvars ray_data;

    ray_data.xa = texwidth / tan(degToRad(castangle));
    ray_data.ya = texheight * -1;
    ray_data.ry = ((int)data->player->posy >> 6) << 6;
    data->player->box_y = (int)(ray_data.ry - 1) >> 6;
    ray_data.rx = ((data->player->posy - ray_data.ry) / tan(degToRad(castangle)));
    ray_data.rx = data->player->posx - fabs(ray_data.rx);
    data->player->box_x = (int)ray_data.rx >> 6;
    if (ray_data.rx < 0)
         return (1e30);
    while (map[data->player->box_y][data->player->box_x] == 0)/*could be improved*/
    {
        ray_data.ry += ray_data.ya;
        ray_data.rx += ray_data.xa;
        if (ray_data.rx < 0)
            return (1e30);
        data->player->box_y = (int)(ray_data.ry - 1) >> 6;
        data->player->box_x = (int)ray_data.rx >> 6;    
    }
    data->player->ver_hitx[i] = ray_data.rx;
    data->player->ver_hity[i] = ray_data.ry;
    data->player->wall_type = map[data->player->box_y][data->player->box_x];
    return (calculate_distance(data, ray_data.rx, ray_data.ry, castangle));
}

// +x +y
double  vertical_casting_4(t_data *data, double castangle, int i)
{
    t_rayvars raydata;

    raydata.xa = texwidth / tan(degToRad(castangle)) * -1;
    raydata.ya = texheight;
    raydata.ry = (((int)data->player->posy >> 6) << 6) + texheight;
    data->player->box_y = (int)raydata.ry >> 6;
    raydata.rx = (raydata.ry - data->player->posy) / tan(degToRad(castangle));
    raydata.rx = data->player->posx + fabs(raydata.rx);
    data->player->box_x = (int)raydata.rx >> 6;
    if (raydata.rx < 0)
         return (1e30);
    while (map[data->player->box_y][data->player->box_x] == 0)
    {
        raydata.ry += raydata.ya;
        raydata.rx += raydata.xa;
        if (raydata.rx > MAP_H)
            return (1e30);
        data->player->box_y = (int)raydata.ry >> 6;
        data->player->box_x = (int)raydata.rx >> 6;
    }
    data->player->ver_hitx[i] = raydata.rx;
    data->player->ver_hity[i] = raydata.ry;
    data->player->wall_type = map[data->player->box_y][data->player->box_x];
    return (calculate_distance(data, raydata.rx, raydata.ry, castangle));
}

// -x +y
double  vertical_casting_3(t_data *data, double castangle, int i)
{
    t_rayvars ray_data;

    ray_data.xa = texwidth / tan(degToRad(castangle)) * -1;
    ray_data.ya = texheight;
    ray_data.ry = (((int)data->player->posy >> 6) << 6) + texheight;
    data->player->box_y = (int)ray_data.ry >> 6;
    ray_data.rx = (ray_data.ry - data->player->posy) / tan(degToRad(castangle));
    ray_data.rx = data->player->posx - fabs(ray_data.rx);
    data->player->box_x = (int)ray_data.rx >> 6;
    if (ray_data.rx < 0)
         return (1e30);
    while (map[data->player->box_y][data->player->box_x] == 0)
    {
        ray_data.ry += ray_data.ya;
        ray_data.rx += ray_data.xa;
        if (ray_data.rx < 0)
            return (1e30);
        data->player->box_y = (int)ray_data.ry >> 6;
        data->player->box_x = (int)ray_data.rx >> 6;
    }
    data->player->ver_hitx[i] = ray_data.rx;
    data->player->ver_hity[i] = ray_data.ry;
    data->player->wall_type = map[data->player->box_y][data->player->box_x];
    return (calculate_distance(data, ray_data.rx, ray_data.ry, castangle));
}