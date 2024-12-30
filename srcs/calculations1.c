#include "../includes/cub3d.h"
#include <math.h>
#define M_PI   3.14159265358979323846264338327950288
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

extern int map[w][h];
// !!USE SHIFT TO DEVIDE BY 64 WHILE LOOPING FOR WALL

// castANGLE == 0 nbp
// 0, 90 +x -y
double  vertical_casting_1(t_data *data, double castangle, int i)
{
    double len;
    double rx;
    double ry;
    double xa;
    double ya;

    xa = texwidth / tan(degToRad(castangle));
    ya = texheight * -1;
    //printf("ver cast 1 xa %f ya %f\n", xa, ya);
    ry = ((int)data->player->posy >> 6) << 6;
    data->player->box_y = (int)(ry - 1) >> 6;
    //printf("-vertical casting: next square y is %f box_y is %d\n", ry, data->player->box_y );
    rx = ((data->player->posy - ry) / tan(degToRad(castangle)));
    rx = data->player->posx + fabs(rx); // rx should be postive remove fabs
    data->player->box_x = (int)rx >> 6;
    if (rx > MAP_W)
    {
         //printf("!!!!!width is too high!!!!! rx is %f\n", rx);
         return (1e30);
    }
    while (map[data->player->box_y][data->player->box_x] == 0)/*could be improved*/
    {
        ry += ya;
        rx += xa;
        if (rx > MAP_W) // always pos.
            return (1e30);
        data->player->box_y = (int)(ry - 1) >> 6;
        data->player->box_x = (int)rx >> 6;
    }
    data->player->ver_hitx[i] = rx;
    data->player->ver_hity[i] = ry;
    data->player->wall_type = map[data->player->box_y][data->player->box_x];
    return (calculate_distance(data, rx, ry, castangle));
}
// -x -y
double  vertical_casting_2(t_data *data, double castangle, int i)
{
    double len;
    int hit;
    double rx;
    double ry;
    hit = 0;
    double xa;
    double ya;

    xa = texwidth / tan(degToRad(castangle)); // negative tan negative xa
    ya = texheight * -1;
    //printf("ver cast 2 xa %f ya %f\n", xa, ya);
    ry = ((int)data->player->posy >> 6) << 6;
    data->player->box_y = (int)(ry - 1) >> 6;
    rx = ((data->player->posy - ry) / tan(degToRad(castangle)));
    rx = data->player->posx - fabs(rx); // negative tan you could + rx
    data->player->box_x = (int)rx >> 6;
    if (rx < 0)
    {
         //printf("!!!!!width is too high!!!!! rx is %f\n", rx);
         return (1e30);
    }
    while (map[data->player->box_y][data->player->box_x] == 0)/*could be improved*/
    {
        ry += ya;
        rx += xa;
        if (rx < 0)// !! ? can set rx to 0 for 1 calculation ?
            return (1e30);
        data->player->box_y = (int)(ry - 1) >> 6;
        data->player->box_x = (int)rx >> 6;    
    }
    data->player->ver_hitx[i] = rx;
    data->player->ver_hity[i] = ry;
    data->player->wall_type = map[data->player->box_y][data->player->box_x];
    return (calculate_distance(data, rx, ry, castangle));
}

// +x +y
double  vertical_casting_4(t_data *data, double castangle, int i)
{
    double len;
    int hit;
    double rx;
    double ry;
    hit = 0;
    double xa;
    double ya;

    xa = texwidth / tan(degToRad(castangle)) * -1;
    ya = texheight;
    ry = (((int)data->player->posy >> 6) << 6) + texheight;
    data->player->box_y = (int)ry >> 6;
        //printf("vertical casting: next square y is %f box_y is %d\n", ry, data->player->box_y );
    rx = (ry - data->player->posy) / tan(degToRad(castangle));
    rx = data->player->posx + fabs(rx);
    data->player->box_x = (int)rx >> 6;
    if (rx < 0)
    {
         //printf("!!!!!width is too high!!!!! rx is %f\n", rx);
         return (1e30);
    }
    while (map[data->player->box_y][data->player->box_x] == 0)/*could be improved*/
    {
        ry += ya;
        rx += xa;
        if (rx > MAP_H)
            return (1e30);
        data->player->box_y = (int)ry >> 6;
        data->player->box_x = (int)rx >> 6;
    }
    data->player->ver_hitx[i] = rx;
    data->player->ver_hity[i] = ry;
    data->player->wall_type = map[data->player->box_y][data->player->box_x];
    return (calculate_distance(data, rx, ry, castangle));
}

// -x +y
double  vertical_casting_3(t_data *data, double castangle, int i)
{
    double len;
    int hit;
    double rx;
    double ry;
    hit = 0;
    double xa;
    double ya;

    xa = texwidth / tan(degToRad(castangle)) * -1;
    ya = texheight;
    ry = (((int)data->player->posy >> 6) << 6) + texheight;
    data->player->box_y = (int)ry >> 6;
        //printf("vertical casting: next square y is %f box_y is %d\n", ry, data->player->box_y );
    //printf("ver cast 4 xa %f ya %f\n", xa, ya);
    rx = (ry - data->player->posy) / tan(degToRad(castangle));
    rx = data->player->posx - fabs(rx);
    data->player->box_x = (int)rx >> 6;
    if (rx < 0)
    {
         //printf("!!!!!width is too high!!!!! rx is %f\n", rx);
         return (1e30);
    }
    while (map[data->player->box_y][data->player->box_x] == 0)/*could be improved*/
    {
        ry += ya;
        rx += xa;
        if (rx < 0)
            return (1e30);
        data->player->box_y = (int)ry >> 6;
        data->player->box_x = (int)rx >> 6;
    }
    data->player->ver_hitx[i] = rx;
    data->player->ver_hity[i] = ry;
    data->player->wall_type = map[data->player->box_y][data->player->box_x];
    return (calculate_distance(data, rx, ry, castangle));
}