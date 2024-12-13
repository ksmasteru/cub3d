#include "../includes/cub3d.h"
#include <math.h>
#define M_PI   3.14159265358979323846264338327950288
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

extern int map[8][8];
double  calculate_distance(t_data *data, double cx, double cy, double castAngle)
{
    //TODO
    double distance;

    distance = sin(degToRad(castAngle)) * fabs(data->player->posy - cy); //  
    return (distance);
}
// cast a ray of castAngle stops when it hits a wall
// return distance from player to the wal

// !converting from box to numberis problematic box 1 is actulaly (1 + 1) * unit.
// change to be like y_axis_raycast if it causes bugs.
double   x_axis_raycast(t_data *data, double castAngle)
{
    double cx;
    double cy;
    int hit;
    double distance;
    //printf("castAngle is %f\n", castAngle);
    hit = 0;
    if (castAngle == 0 || castAngle == 180)
    {
        cy = data->player->posy;
        //printf("cy startposition is %f\n", cy);
        if (castAngle == 0)
            cx = (int)(data->player->posx / texwidth) * texwidth + texwidth;
        else
            cx = (int) (data->player->posx / texwidth) * texwidth - 1; // for rounding up. to make 3 == 2.
        if (cx < 0)
            cx = 0;
    }
    if (map[(int) cy / texheight][(int)cx / texheight] != 0)
        hit = 1;
    while (hit != 1) /*traverse right or left until hitting a wall*/
    {
        if (castAngle == 0)
            cx += texwidth;
        else
            cx -= texwidth;
        if (cx < 0)
            cx = 0;
        if (map[(int) cy / texheight][(int)cx / texheight] != 0)
             hit = 1;
    }
    //printf("found a wall at map[%d][%d]\n", (int)cx / texwidth, (int)cy / texheight);
    if (castAngle == 0)
         distance = (int)cx / texwidth * texwidth - data->player->posx; // current box lent excluded
    else
        distance = data->player->posx - (((int) (cx) / texwidth) * texwidth + texwidth); // current box lent included
    //printf("distance to x axis is %f cx value is %f\n", distance, cx);
    return (distance);
}

// cy and cx in this context are useless.
double  y_axis_raycast(t_data *data, double castAngle)
{
    double cx; // CREDENTIAL X : 
    double cy;// CREDENTIAL Y
    double distance;
    int hit;
    int box_y;// keep count of how many boxes were traveled.

    box_y = 0;
    hit = 0;
    cx = data->player->posx;
    if (castAngle == 90)
        cy = (int)(data->player->posy / texheight + 1) * texheight - texheight - 1; // go up -1 is import for credentials
    else
        cy = (int)(data->player->posy / texheight + 1) * texheight;
    if (cy < 0)
        cy = 0;
    if (map[(int)cy / texheight][(int)cx / texheight] != 0)
        hit = 1;
    printf("first box cy %f its box value is %d %d\n", cy, (int)cx/64, (int)cy/64);
    while (hit != 1)
    {
        if (castAngle == 90)
            cy -= texheight;
        else
            cy += texheight;
        if (cy < 0)
        {
            cy = 0;
            printf("ERROR CY IS NEGATIVE\n");
            exit(1);
        }
        box_y++;
        if (map[(int)cy / texheight][(int)cx / texwidth] != 0)
            hit = 1;
    }
    printf("found a wall at cy %f box %d %d\n", cy, (int)cx / 64, (int) cy / 64);
    distance = box_y * texheight + ((int)data->player->posy % texheight); 
    printf("distance across y axis ist %f\n", distance);
    return (distance);
}

// the actual distance. BOTH hit same wall. or at least pass tru the same grids.
double   horizontalraycast(t_data *data, double castAngle)
{
    //ya iknowns ca isnt
    double len;
    int hit;
    double cx;
    double cy;
    hit = 0;
    
    if (castAngle > 0 && castAngle < 180)
    {
        cy = ((int)data->player->posy / texheight) * texheight - 1;
        cx = roundf(data->player->posy - cy) / tan(degToRad(castAngle));
        cx += data->player->posx;
        /*printf("cy is %f cx is %f\n", cy, cx);
        printf("first cube horizontal intersection is at x:%d y:%d \n", (int)(cx/64)
        , (int)(cy / 64));
        exit(1);*/
    }
    else 
    {
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
    //printf("first cube horizontal intersection is at x:%d y:%d \n", (int)cx / 64,
      //  (int)cy / 64);
    if (map[(int)cy / 64][(int)cx / 64] != 0)
        hit = 1;
    while (hit != 1)
    {
        //printf("entered  hit loop\n");
        // traverse upward
        if (castAngle > 0 && castAngle < 180)
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
        if (map[(int)cy / 64][(int)cx / 64]!= 0)
            hit = 1;
    }
    //printf("found a wall at %d %d\n", (int)cx / 64, (int)cy / 64);
    double distance = calculate_distance(data, cx, cx, castAngle);
    //printf("horizontal distance to the wall is %f\n", distance);
    return (distance);
}

double   verticalraycast(t_data *data, double castAngle)
{
    double  len;
    double  cx;
    double  cy;
    int     hit;
    double distance;
    int xa;
    hit = 0;
    
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
    if (cy < 0)
        cy = 0;
    if (cx < 0)
        cx = 0;
    if (map[(int)cy / 64][(int)cx / 64] != 0)
            hit = 1;
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
        if (cx < 0)
            cx = 0;
        if (cy < 0)
            cy = 0;
        printf("current cx[%d] cy[%d]\n", (int)cx/ 64 , (int)cy / 64);
        if (map[(int)cy / 64][(int)cx / 64] != 0)
            hit = 1;
    }
    //printf("found wall at [%d] [%d]\n", (int)cx / 64, (int)cy /64);
    distance = calculate_distance(data, cx, cx, castAngle);
    //printf("vertical distance to the wall is %f\n", distance);
    return (distance);
}