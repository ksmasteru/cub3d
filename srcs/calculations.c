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
// cast a ray of castAngle stops when it hits a wall
// return distance from player to the wal

// !converting from box to numberis problematic box 1 is actulaly (1 + 1) * unit.
// change to be like y_axis_raycast if it causes bugs.
double   x_axis_raycast(t_data *data, double castAngle)
{
    double rx;
    double ry;
    int hit;
    double distance;
    int box_x;
    //printf("castAngle is %f\n", castAngle);
    hit = 0;
    box_x = 0;
    ry = data->player->posy;
        //printf("ry startposition is %f\n", ry);
    data->player->box_y = ry / texheight;
    if (castAngle == 0)
    {
        rx = ((int)data->player->posx / texwidth) * texwidth + texwidth;
        data->player->box_x = rx / texwidth;
    }
    else
    {
        rx = ((int)data->player->posx / texwidth) * texwidth; // removed -1
        data->player->box_x = (rx - 1) / texwidth;
    }
    if (map[data->player->box_y][data->player->box_x] != 0)
    {
        data->player->hitx = rx;
        data->player->hity = ry;
        hit = 1;
        data->player->wall_type = map[data->player->box_y][data->player->box_x];
    }
    // ny how much should me increment box and boxy
    while (hit != 1) /*traverse right or left until hitting a wall*/
    {
        if (castAngle == 0)
        {
            data->player->box_x++;
            rx += texwidth;
        }
        else
        {
            data->player->box_x--;
            rx -= texwidth;
        }
        /*if (box_x < 0)
            box_x = 0;*/
        if (map[data->player->box_y][data->player->box_x] != 0)
        {
            data->player->hitx = rx;
            data->player->hity = ry;
            hit = 1;
            data->player->wall_type = map[data->player->box_y][data->player->box_x];
        }
    }
    //printf("found a wall at map[%d][%d]\n", (int)rx / texwidth, (int)ry / texheight);
    //if (box_x == 0)
      //  distance = (int)data->player->posx % texwidth; // current box lent excluded
    //else
    distance = fabs(data->player->posx - rx); // current box lent included
    //printf("------------distance to x axis is %f cx value is %f-----------\n", distance, ry);
    return (distance);
}

// ry and cx in this context are useless.
double  y_axis_raycast(t_data *data, double castAngle)
{
    double rx; // CREDENTIAL X : 
    double ry;// CREDENTIAL Y
    double distance;
    int hit;
    int box_y;// keep count of how many boxes were traveled.

    box_y = 0;
    hit = 0;
    rx = data->player->posx;
    data->player->box_x = (int)data->player->posx / texwidth;
    if (castAngle == 90)
    {
        ry = (int)data->player->posy / texheight * texheight;
        data->player->box_y = (ry - 1) / texheight;
    }
    else
    {
        ry = (int)(data->player->posy / texheight) * texheight + texheight;
        data->player->box_y = ry / texheight;
    }
    if (map[data->player->box_y][data->player->box_x] != 0)
    {
        data->player->hitx = rx;
        data->player->hity = ry;
        hit = 1;
        data->player->wall_type = map[data->player->box_y][data->player->box_x];
    }
    //printf("first box ry %f its box value is %d %d\n", ry, data->player->box_x, data->player->box_y);
    while (hit != 1)
    {
        if (castAngle == 90)
        {
            ry -= texheight;
            data->player->box_y--;
        }
        else
        {
            ry += texheight;
            data->player->box_y++;
        }
        if (ry < 0)
        {
            ry = 0;
           printf("ERROR ry IS NEGATIVE\n");
           exit(1);
        }
        //box_y++;
        if (map[data->player->box_y][data->player->box_x] != 0)
        {
            data->player->hitx = rx;
            data->player->hity = ry;
            hit = 1;
            data->player->wall_type = map[data->player->box_y][data->player->box_x];
        }
    }
    //printf("found a wall at ry %f box %d %d\n", ry, (int)rx / 64, (int) ry / 64);
    //if (box_y == 0)
     //   distance = (int)data->player->posy % texheight;
    //else
    //distance = box_y * texheight + (int)data->player->posy % texheight;
    distance = fabs(ry- data->player->posy);
    //return (distance * cos(degToRad(data->player->beta_angle))); // ! 0 ?
    return (distance);
}

// the actual distance. BOTH hit same wall. or at least pass tru the same grids.
double  set_xa(double castAngle)
{
    double xa;

    xa = fabs(texwidth / tan(degToRad(castAngle))); 
    if (castAngle > 90 && castAngle < 270)
        xa *= -1;
    return (xa);
}
double   verticalraycast(t_data *data, double castAngle)
{
    //ya is known ca isnt
    double len;
    int hit;
    double rx;
    double ry;
    hit = 0;
    double xa;
    double ya;

    xa = set_xa(castAngle);
    //printf("xa value is %f\n", xa);
    if (castAngle > 0 && castAngle < 180)
    {
        ya = texheight * -1;
        ry = ((int)data->player->posy / texheight) * texheight;
        data->player->box_y = (ry - 1) / texheight;
        //printf("vertical casting: next square y is %f box_y is %d\n", ry, data->player->box_y );
        rx = ((data->player->posy - ry) / tan(degToRad(castAngle)));
        if (castAngle < 90)
            rx = data->player->posx + fabs(rx);
        else
            rx = data->player->posx - fabs(rx);
        data->player->box_x = rx / texwidth;
        //printf("vertical casting: next square x is %f box_x is %d\n", rx, data->player->box_x );
        /*printf("ry is %f rx is %f\n", ry, rx);
        printf("first cube horizontal intersection is at x:%d y:%d \n", (int)(rx/64)
        , (int)(ry / 64));
        exit(1);*/
    }
    else 
    {
        //printf("down ward ray\n");
        ya = texheight;
        ry = ((int)data->player->posy / texheight) * texheight + texheight;
        data->player->box_y = ry / texheight;
        //printf("vertical casting: next square y is %f box_y is %d\n", ry, data->player->box_y );
        rx = (ry - data->player->posy) / tan(degToRad(castAngle));
        //printf("ry is %f rx is %f\n", ry, rx);
        /*
            as above using the porprety of tan. only rx - posy has to be positve
        if (castAngle > 270)
            rx += data->player->posx;
        else if (castAngle < 270)
            rx = data->player->posx - rx;*/
        if (castAngle > 270)
            rx = data->player->posx + fabs(rx);
        else
            rx = data->player->posx - fabs(rx);
        data->player->box_x = rx / texwidth;
        //printf("vertical casting: next square x is %f box_x is %d\n", rx, data->player->box_x );

        /*rx = roundf(rx) / 64;
        ry = roundf(ry) / 64;
        printf("first cube horizontal intersection is at x:%d y:%d \n", ((int)rx/64)
        , ((int)ry / 64));
        exit(1);*/
    }
    if (rx < 0 || rx > MAP_W)
    {
         //printf("!!!!!width is too high!!!!! rx is %f\n", rx);
         return (1e30);
    }
    //printf("first cube horizontal intersection is at x:%d y:%d \n", (int)rx / 64,
      //  (int)ry / 64);
    if (map[data->player->box_y][data->player->box_x] != 0)
    {
        data->player->hitx = rx;
        data->player->hity = ry;
        hit = 1;
        data->player->wall_type = map[data->player->box_y][data->player->box_x];
    }
    while (hit != 1)
    {
        //printf("entered  hit loop\n");
        // traverse upward
        ry += ya;// +texheight or -texheight
        rx += xa;
        // hard coded
        if (rx < 0)
        { 
            //printf("---------------returned high value becuase rx was %f-----------------\n", rx);
            return (1e30);            ry = 0;
        }
        if (rx > MAP_W)
        {
            //printf("---------------returned high value becuase rx was %f-----------------\n", rx);
            return (1e30);            ry = MAP_W - 1;
        }
        if (castAngle > 0 && castAngle < 180)
            data->player->box_y = (ry - 1) / texheight;
        else
            data->player->box_y = ry / texheight;
        data->player->box_x = rx / texwidth;
        // in case ry or rx get negative --> SEGV;
        //ry = roundf(ry);
        //rx = roundf(rx);
        //printf("vertical casting : rx value %f ry value %f\n", rx, ry);
        /*if (ry < 0)
            ry = 0;
        if (ry > h * texheight)
            ry = h * texheight - 1;
        if (rx < 0)
            rx = 0;
        if (rx > h * texwidth)
            rx = h * texwidth - 1;*/
        if (map[data->player->box_y][data->player->box_x]!= 0)
        {
            data->player->hitx = rx;
            data->player->hity = ry;
            hit = 1;
            data->player->wall_type = map[data->player->box_y][data->player->box_x];
        }
        /*else
            printf("vertical casting box_x %d box_y %drx %d ry %d werent a wall \n",
                data->player->box_x, data->player->box_y, (int)rx, (int)ry);*/
    }
    //printf("found a wall at %d %d\n", (int)rx / 64, (int)ry / 64);
    double distance = calculate_distance(data, rx, ry, castAngle);
    //printf("horizontal distance to the wall is %f\n", distance);
    return (distance);
}

/*name were swapped.*/
double   horizontalraycast(t_data *data, double castAngle)
{
    double  len;
    double  rx;
    double  ry;
    int     hit;
    double distance;
    double xa;
    double ya;
    hit = 0;
    if ((castAngle > 0 && castAngle < 90)
        || (castAngle > 270 && castAngle < 360))
    {
        xa = texwidth;
        // finding  adjacent  : current + 1 BIG DISTANCE
        rx = ((int)data->player->posx / texwidth) * texwidth + texwidth; // box x
        data->player->box_x = rx / texwidth;
        // small distance
        //printf("rx value is %f and angle is %f\n", rx, castAngle);
        ry = tan(degToRad(castAngle)) * (rx - data->player->posx); // something is wrong in here
        if (castAngle > 0 && castAngle < 90)/*positive ry tan method doesnt apply here*/
            ry = data->player->posy - fabs(ry);
        else
            ry = data->player->posy + fabs(ry);
        //printf("horizontal casting ry value is %f\n", ry); // make smaller map
        data->player->box_y = ry / texheight;
        /*as stated in horizontal raycasting : adding or substracting is decided
        by the sign of tan : this can only work for x as y sign isnt the same as tan.*/
        /*rx = roundf(rx) / 64;
        ry = roundf(ry) / 64;*/
        //printf("first cube horizontal intersection is at x:%d y:%d \n", ((int)rx/64)
       // , ((int)ry / 64));
        //exit(1);
    }
    else
    {
        // adjacent current - box
        xa = texwidth * -1;
        rx = ((int)data->player->posx / texwidth) * texwidth;
        //printf("data->player->posx[%f] - rx[%f] = [%f\n", data->player->posx, rx, data->player->posx - rx);
        data->player->box_x = (rx - 1) / texwidth;
        ry =  tan(degToRad(castAngle)) * (data->player->posx - rx);
        //printf("opposent value is %f\n", ry);
        /* fabs (tan) ? because we decided when to add and -
         !!!! when to add and when to substract to ry : decided by tan sign.*/
        if (castAngle > 90 && castAngle < 180) /*negative ry*/
            ry = data->player->posy - fabs(ry);
        else
            ry = data->player->posy + fabs(ry);
        data->player->box_y = ry / texheight;
        //printf("first cube horizontal intersection1 is at x:%d y:%d \n", ((int)rx) / 64
       // , ((int)ry) / 64);
        //exit(1);
    }
    if (ry < 0 || ry > MAP_H) /*enough ?*/
    {
        //printf("!!!!!!!!!!at angle %f ry is too high %f!!!!!!!!!!!!!\n", castAngle, ry);
        return (1e30);
    }
    if (map[data->player->box_y][data->player->box_x] != 0)
    {
        data->player->hitx = rx;
        data->player->hity = ry;
        hit = 1;
        data->player->wall_type = map[data->player->box_y][data->player->box_x];
    }
    ya = fabs(tan(degToRad(castAngle)) * texheight);// calculated one time for efficienry. : up positive,down negative
    // tan doesnt apply to ya ? it only apply to x;
    //printf("ya value is %f\n", ya);
    if (castAngle > 0 && castAngle < 180)
        ya *= -1;
    while (hit != 1) // xa stable. issue in this it has to be redone
    {/*there is no other way to avoid negtaive value but to round down.*/
        ry += ya;
        if (ry < 0)
        {
            //printf("---------------returned high value becuase ry was %f-----------------\n", ry);
            return (1e30);
            ry = 1;
        }
        if (ry > MAP_W)
        {
            //printf("---------------returned high value becuase ry was %f-----------------\n", ry);
            return (1e30);
            ry = MAP_W - 1;
        }
        rx += xa;
        // round down value ?
        if (castAngle > 90 && castAngle < 270)
            data->player->box_x = (rx - 1) / texwidth;
        else
            data->player->box_x = (rx) / texwidth;
        data->player->box_y = ry / texheight;
        //ry = roundf(ry);
        //rx = roundf(rx);
        // ry got negative.
        //printf("horizontal casting :rx value %f ry value %f angle %f\n", rx, ry, castAngle);
        //if(ry < 0)
          //  ry = 0;
        data->player->hitx = rx;
        data->player->hity = ry;
        /*if (ry > MAP_H)
            ry = MAP_H - 1;*/ // this is what causes rys to have similar values.
        //printf("rx value %f ry value %f current rx[%d] ry[%d]\n", rx, ry, (int)rx/ 64 , data->player->box_y);
        if (map[data->player->box_y][data->player->box_x] != 0)
            hit = 1;
    }
    //printf("found wall at [%d] [%d]\n", (int)rx / 64, (int)ry /64);
    data->player->wall_type = map[data->player->box_y][data->player->box_x];
    distance = calculate_distance(data, rx, ry, castAngle);
    //printf("vertical distance to the wall is %f\n", distance);
    return (distance);
}