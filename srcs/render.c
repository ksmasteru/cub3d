#include "../includes/cub3d.h"
#include <math.h>
#define M_PI   3.14159265358979323846264338327950288
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

// each wall is 64*64.
//            cx = (int)(data->player->posx / texwidth) * texwidth + texwidth;

int map[8][8]={
{1, 1 , 1, 1, 1, 1, 1, 1},
{1, 0 , 0, 1, 0, 0, 0, 1},
{1, 0 , 0, 1, 0, 0, 0, 1},
{1, 0 , 1, 0, 0, 0, 1, 1},
{1, 0 , 0, 0, 0, 0, 0, 1},
{1, 0 , 0, 0, 0, 0, 0, 1},
{1, 0 , 0, 0, 0, 0, 0, 1},
{1, 1 , 1, 1, 1, 1, 1, 1},
};
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
double   x_axis_raycast(t_data *data, double castAngle)
{
    // @returns distance
    // keeps increasing in x side untill finding a wall.
    double cx;
    double cy;
    int hit;
    double distance;

    //castAngle = 0;
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
        if (cx < 0) // in case above is at 1;
            cx = 0;
        //printf("first box cx is %f and its box value is %d %d\n", cx, (int)cx / 64, (int)cy / 64);
    }
    /*for (int  i = 0 ; i < 8 ; i++)
    {
        printf("{");
        for (int j = 0 ; j < 8 ; j++)
            printf("%d ", map[i][j]);
        printf("}\n");
    }*/
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
    castAngle = 180;
    printf("Cast angle is %f\n", castAngle);
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
    castAngle = 270;
    if (castAngle == 0 || castAngle == 180)
    {
        cy = data->player->posy;
        if (castAngle == 0)
            cx = (int)(data->player->posx / texwidth) * texwidth + texwidth;
        else
            cx = (int) (data->player->posx / texwidth) * texwidth - texwidth; // first wall at left credentials.
        if (cx < 0) // in case above is at 1;
            cx = 0;
    }

    else if (castAngle == 90 || castAngle == 270)
    {
        cx = data->player->posx;
        if (castAngle == 90)
            cy = (int)(data->player->posy / texheight) * texheight - texheight;
        else
            cy = (int)(data->player->posy / texheight) * texheight + texheight;
        if (cy < 0)
            cy = 0;
    }
    /*printf("cx[%f] cy[%f] boxX[%d] boxY[%d]\n", cx, cy, (int)cx / 64, (int)cy / 64);
    exit (1);*/
    /*else*/ if (castAngle > 0 && castAngle < 180)
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
    if (map[(int)cx / 64][(int)cy / 64] != 0)
        hit = 1;
    while (hit != 1)
    {
        //printf("entered  hit loop\n");
        // traverse upward
        if (castAngle >= 0 && castAngle <= 180)
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
        if (map[(int)cx / 64][(int)cy / 64] != 0)
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
    
    if ((castAngle > 0 && castAngle <= 90)
        || (castAngle > 270 && castAngle < 360))
    {
        if (castAngle == 90)
            castAngle = 88;
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
        if (castAngle == 90 + 180)
            castAngle = 90 + 180 - 2;
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
        //printf("current cx[%d] cy[%d]\n", (int)cx, (int)cy);
        if (map[(int)cx / 64][(int)cy / 64] != 0)
            hit = 1;
    }
    //printf("found wall at [%d] [%d]\n", (int)cx / 64, (int)cy /64);
    distance = calculate_distance(data, cx, cx, castAngle);
   // printf("vertical distance to the wall is %f\n", distance);
    return (distance);
}


void    put_wall(t_data *data, int stripex,  double distance)
{
    // PUTS VERLINE .
    // distance ratio ?
    int slice_height;
    int projection_d = (WIDTH / 2) * tan(degToRad(30)); /*ambigous*/
    printf("putwall distance is %f\n", distance);
    slice_height = (texheight / distance) * (projection_d); // this should be round up distance too small ? 
    printf("slice height is %d\n", slice_height);
    // drawing from middle of screen;
    int y_min =  HEIGHT / 2 - slice_height / 2;
    if (y_min <= 0)
        y_min = 1;
    int y_max = HEIGHT / 2 + slice_height / 2;
    if (y_max >= HEIGHT)
        y_max = HEIGHT - 1;
    char *pixel;
    while (y_min != y_max)
    {
        pixel = data->img->adrs + data->img->size_line * y_min +
            stripex * (data->img->bpp / 8);
        *(int *)pixel = 0x00ff00;
        y_min++;
    }
}

double   raycast(t_data *data, double castAngle)
{
    double horizontalray;
    double verticalray;

    castAngle = 90;
    if (castAngle == 0 || castAngle == 180)
        return (x_axis_raycast(data, castAngle));
    else if (castAngle == 90 || castAngle == 270)
        return (y_axis_raycast(data, castAngle));
    verticalray = verticalraycast(data, castAngle);
    horizontalray = horizontalraycast(data, castAngle);
    if (verticalray < horizontalray)
    {
        printf("distance to the wall is %f\n", verticalray);
        printf("coreccted distance to the wall is %f\n", verticalray * cos(degToRad(data->player->beta_angle)));
        return (verticalray * cos(degToRad(data->player->beta_angle)));
    }
    printf("distance to the wall is %f\n", horizontalray);
    printf("corrected distance to the wall is %f\n", horizontalray * cos(degToRad(data->player->beta_angle)));
    return (horizontalray * cos(degToRad(data->player->beta_angle)));
}

void set_new_img(t_data *data)
{
    if (data->img->mlx_img)
    {
        mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
        data->img->mlx_img = NULL;
    }
    data->img->mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
    data->img->adrs = mlx_get_data_addr(data->img->mlx_img, &(data->img->bpp), &(data->img->size_line), &(data->img->endian));
}

int render_walls(t_data *data)
{
    double wallheight;
    int i;
    double  sep_angle;
    double   castAngle;

    i = 0;
    sep_angle = 60.0 / WIDTH;
    castAngle = data->player->view_deg + 30;
    data->player->beta_angle = 30;
    printf("start boxX[%d] boxY[%d]\n", (int)data->player->posx / 64, (int)data->player->posy / 64);
    while (i < WIDTH)
    {
        //printf("cast angle is %f\n", castAngle);
        wallheight = raycast(data, castAngle);
        exit(1);
        put_wall(data, i, wallheight);
        castAngle -= sep_angle;
        data->player->beta_angle -= sep_angle;
        i++;
    }
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->mlx_img, 0, 0);
    return (0);
}