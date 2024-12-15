#include "../includes/cub3d.h"
#include <math.h>
#define M_PI   3.14159265358979323846264338327950288
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

extern int map[24][24];
double  calculate_distance(t_data *data, double cx, double cy, double castAngle)
{
    //TODO
    double distance;

    distance = fabs((data->player->posy - cy) / sin(degToRad(castAngle)));
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
    int box_x;
    //printf("castAngle is %f\n", castAngle);
    hit = 0;
    box_x = 0;
    cy = data->player->posy;
        //printf("cy startposition is %f\n", cy);
    if (castAngle == 0)
        cx = ((int)data->player->posx / texwidth) * texwidth + texwidth;
    else
        cx = ((int)data->player->posx / texwidth) * texwidth - 1;
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
        box_x++;
        if (map[(int) cy / texheight][(int)cx / texheight] != 0)
             hit = 1;
    }
    //printf("found a wall at map[%d][%d]\n", (int)cx / texwidth, (int)cy / texheight);
    if (box_x == 0)
        distance = (int)data->player->posx % texwidth; // current box lent excluded
    else
        distance = box_x * texwidth + (int)data->player->posx % texwidth; // current box lent included
    //printf("------------distance to x axis is %f cx value is %f-----------\n", distance, cx);
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
        cy = (int)data->player->posy / texheight * texheight - 1;
    else
        cy = (int)(data->player->posy / texheight) * texheight + texheight;
    if (map[(int)cy / texheight][(int)cx / texheight] != 0)
        hit = 1;
    //printf("first box cy %f its box value is %d %d\n", cy, (int)cx/64, (int)cy/64);
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
    //printf("found a wall at cy %f box %d %d\n", cy, (int)cx / 64, (int) cy / 64);
    if (box_y == 0)
        distance = (int)data->player->posy % texheight;
    else
        distance = box_y * texheight + (int)data->player->posy % texheight;
    return (distance * cos(degToRad(data->player->beta_angle)));
}

// the actual distance. BOTH hit same wall. or at least pass tru the same grids.
double   verticalraycast(t_data *data, double castAngle)
{
    //ya iknowns ca isnt
    double len;
    int hit;
    double cx;
    double cy;
    hit = 0;
    double xa;
    double ya;
    if (castAngle > 0 && castAngle < 180)
    {
        ya = texheight * -1;
        cy = ((int)data->player->posy / texheight) * texheight - 1;
        cx = ((data->player->posy - cy) / tan(degToRad(castAngle)));
        if (castAngle < 90)
            cx = data->player->posx + fabs(cx);
        else
            cx = data->player->posx - fabs(cx);
        // if ray is going rihgt side add
        // if it is going left side substaract : same proprety as tan so just add
        // and keep the sign of tan but data->player->posy - cy has to be positive.
        /*printf("cy is %f cx is %f\n", cy, cx);
        printf("first cube horizontal intersection is at x:%d y:%d \n", (int)(cx/64)
        , (int)(cy / 64));
        exit(1);*/
    }
    else 
    {
        //printf("down ward ray\n");
        ya = texheight;
        cy = ((int)data->player->posy / texheight) * texheight + texheight;
        cx = (cy - data->player->posy) / tan(degToRad(castAngle));
        //printf("cy is %f cx is %f\n", cy, cx);
        /*
            as above using the porprety of tan. only cx - posy has to be positve
        if (castAngle > 270)
            cx += data->player->posx;
        else if (castAngle < 270)
            cx = data->player->posx - cx;*/
        if (castAngle > 270)
            cx = data->player->posx + fabs(cx);
        else
            cx = data->player->posx - fabs(cx);
        /*cx = roundf(cx) / 64;
        cy = roundf(cy) / 64;
        printf("first cube horizontal intersection is at x:%d y:%d \n", ((int)cx/64)
        , ((int)cy / 64));
        exit(1);*/
    }
    if (cx < 0 || cx > MAP_W)
    {
         //printf("!!!!!width is too high!!!!!\n");
         return (1e30);
    }
    //printf("first cube horizontal intersection is at x:%d y:%d \n", (int)cx / 64,
      //  (int)cy / 64);
    if (map[(int)cy / 64][(int)cx / 64] != 0)
        hit = 1;
    xa = texwidth / tan(degToRad(castAngle));
    while (hit != 1)
    {
        //printf("entered  hit loop\n");
        // traverse upward
        cy += ya;// +texheight or -texheight
        cx += xa;
        // in case cy or cx get negative --> SEGV;
        if (map[(int)cy / texwidth][(int)cx / texheight]!= 0)
            hit = 1;
    }
    //printf("found a wall at %d %d\n", (int)cx / 64, (int)cy / 64);
    double distance = calculate_distance(data, cx, cy, castAngle);
    //printf("horizontal distance to the wall is %f\n", distance);
    return (distance);
}

/*name were swapped.*/
double   horizontalraycast(t_data *data, double castAngle)
{
    double  len;
    double  cx;
    double  cy;
    int     hit;
    double distance;
    double xa;
    double ya;
    hit = 0;
    // ah swaping value from negative to positive didnt take place !
    if ((castAngle > 0 && castAngle < 90)
        || (castAngle > 270 && castAngle < 360))
    {
        xa = texwidth;
        // finding  adjacent  : current + 1 BIG DISTANCE
        cx = ((int)data->player->posx / texwidth) * texwidth + texwidth; // box x
        // small distance
        //printf("cx value is %f and angle is %f\n", cx, castAngle);
        cy = tan(degToRad(castAngle)) * (cx - data->player->posx); // something is wrong in here
        //printf("cy value is %f\n", cy);
        if (castAngle > 0 && castAngle < 90)/*positive cy tan method doesnt apply here*/
            cy = data->player->posy - fabs(cy);
        else
            cy = data->player->posy + fabs(cy);
        /*as stated in horizontal raycasting : adding or substracting is decided
        by the sign of tan : this can only work for x as y sign isnt the same as tan.*/
        /*cx = roundf(cx) / 64;
        cy = roundf(cy) / 64;*/
        //printf("first cube horizontal intersection is at x:%d y:%d \n", ((int)cx/64)
       // , ((int)cy / 64));
        //exit(1);
    }
    else
    {
        // adjacent current - box
        xa = texwidth * -1;
        cx = ((int)data->player->posx / texwidth) * texwidth - 1; 
        //printf("data->player->posx[%f] - cx[%f] = [%f\n", data->player->posx, cx, data->player->posx - cx);
        cy =  tan(degToRad(castAngle)) * (data->player->posx - cx);
        //printf("opposent value is %f\n", cy);
        /* fabs (tan) ? because we decided when to add and -
         !!!! when to add and when to substract to cy : decided by tan sign.*/
        if (castAngle > 90 && castAngle < 180) /*negative cy*/
            cy = data->player->posy - fabs(cy);
        else
            cy = data->player->posy + fabs(cy);
        //printf("first cube horizontal intersection1 is at x:%d y:%d \n", ((int)cx) / 64
       // , ((int)cy) / 64);
        //exit(1);
    }
    if (cy < 0 || cy > MAP_H) /*enough ?*/
    {
        //printf("!!!!!!!!!!at angle %f cy is too high %f!!!!!!!!!!!!!\n", castAngle, cy);
        return (1e30);
    }
    if (map[(int)cy / 64][(int)cx / 64] != 0)
            hit = 1;
    ya = fabs(tan(degToRad(castAngle)) * texheight);// calculated one time for efficiency. : up positive,down negative
    // tan doesnt apply to ya ? it only apply to x;
    //printf("ya value is %f\n", ya);
    if (castAngle > 0 && castAngle < 180)
        ya *= -1;
    while (hit != 1) // xa stable.
    {
        cy += ya;
        cx += xa;
        // cy got negative.
        if(cy < 0)
            cy = 0;
        if (cy > MAP_H)
            cy = MAP_H - 1;
        printf("cx value %f cy value %f current cx[%d] cy[%d]\n", cx, cy, (int)cx/ 64 , (int)cy / 64);
        if (map[(int)cy / texheight][(int)cx / texwidth] != 0)
            hit = 1;
    }
    //printf("found wall at [%d] [%d]\n", (int)cx / 64, (int)cy /64);
    distance = calculate_distance(data, cx, cy, castAngle);
    //printf("vertical distance to the wall is %f\n", distance);
    return (distance);
}