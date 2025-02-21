#include "../includes/cub3d.h"
#include <math.h>
#define M_PI   3.14159265358979323846264338327950288
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

extern int map[w][h];
// !!USE SHIFT TO DEVIDE BY 64 WHILE LOOPING FOR WALL
double  calculate_distance(t_data *data, double cx, double  cy, double castAngle)
{
    //TODO
    double distance;

    distance = fabs((data->player->posy - cy) / sin(degToRad(castAngle)));
    return (distance);
}

double   verticalraycast(t_data *data, double castangle, int i)
{
    
    if (castangle == 0 || castangle == 180.0 || castangle == 360.0
        ||  castangle == 90.0 || castangle == 270.0)
    {
        return (verticalraycast(data, castangle + 60.0 / SCREEN_W, i));
    }
    if (castangle > 0 && castangle < 90)
        return (vertical_casting_1(data, castangle, i));
    else if (castangle > 90 && castangle < 180)
        return (vertical_casting_2(data, castangle, i));
    else if (castangle > 180 && castangle < 270)
        return (vertical_casting_3(data, castangle, i));
    else /*if (castangle > 270 && castangle < 360)*/
        return (vertical_casting_4(data, castangle, i));
}

/*name were swapped.*/
double   horizontalraycast(t_data *data, double castAngle, int i)
{
    if (castAngle > 0 && castAngle < 90)
        return (horizontalraycast_1(data, castAngle, i));
    else if (castAngle > 90 && castAngle < 180)
        return (horizontalraycast_2(data, castAngle, i));
    else if (castAngle > 180 && castAngle < 270)
        return (horizontalraycast_3(data, castAngle, i));
    else/* if (castAngle > 270 && castAngle < 360)*/
        return (horizontalraycast_4(data, castAngle, i));
}