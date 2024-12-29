#include "../includes/cub3d.h"
#include <math.h>
#define M_PI   3.14159265358979323846264338327950288
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

extern int map[w][h];

double  raycast_1(t_data   *data, double castangle, int *side)
{
    double horizontalray;
    double verticalray;
    double  ver_hitx;
    double  ver_hity;
    if (castangle < 0)
        castangle += 360.0;
    if (castangle > 0 && castangle < 90)
    {
        horizontalray = horizontalraycast_1(data, castangle);
        verticalray = vertical_casting_1(data, castangle);
    }
    else if (castangle > 90 && castangle < 180)
    {
        horizontalray = horizontalraycast_2(data, castangle);
        verticalray = vertical_casting_2(data, castangle);
    }
    else if (castangle > 180 && castangle < 270)
    {
        horizontalray = horizontalraycast_3(data, castangle);
        verticalray = vertical_casting_3(data, castangle);
    }
    else if (castangle > 270 && castangle < 360)
    {
        horizontalray = horizontalraycast_4(data, castangle);
        verticalray = vertical_casting_4(data, castangle);
    }
    else if (castangle > 360)
    {
         castangle -= 360.0;
         return (raycast_1(data, castangle, side));
    }
    else if (castangle == 0 || castangle == 180.0 || castangle == 360)
    {
        *side = 1;
        return (x_axis_raycast(data, castangle));
    }
    else if (castangle == 90.0 || castangle == 270.0)
    {
        *side = 0;
        return (y_axis_raycast(data, castangle));
    }
    if (verticalray < horizontalray)
    {
        //printf("for angle %f vertical height is %f because horizontal is %f\n", castangle, verticalray, horizontalray);
        *side = 0;
        return (verticalray) * cos(degToRad(data->player->beta_angle));
    }
    *side = 1;
    data->player->hitx = data->player->hor_hitx;
    data->player->hity = data->player->hor_hity;
    //}
    //printf("distance to the wall is %f\n", horizontalray);
    //printf("corrected distance to the wall is %f\n", horizontalray * cos(degToRad(data->player->beta_angle)));
    //printf("for angle %f horizontal height is %f because vertical was %f\n", castangle, horizontalray,verticalray);
    return (horizontalray) * cos(degToRad(data->player->beta_angle));
}