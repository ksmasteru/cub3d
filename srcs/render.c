#include "../includes/cub3d.h"
#include <math.h>


// each wall is 64*64.
//            cx = (int)(data->player->posx / texwidth) * texwidth + texwidth;

double angle;
int map[w][h]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,3,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
/*int map[w1][h1] = 
{
    {1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1}  
};*/

t_image     *get_xpm_img(t_data *data)
{
    int width;
    int height;

    t_image *img;

    img = malloc(sizeof(t_image));
    if (data->player->wall_type == 1)
        img->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, "./eagle.xpm", &width, &height);
    else if(data->player->wall_type == 2)
        img->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, "./bluestone.xpm", &width, &height);
    else
        img->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, "./colorstone.xpm", &width, &height);
    if (img->mlx_img == NULL)
    {
        printf("null img\n");
        exit(1);
    }
    img->adrs = mlx_get_data_addr(img->mlx_img, &(img->bpp), &(img->size_line), &(img->endian));
    return (img);
}

void    draw_wall_side(t_data   *data, int stripex, t_pixdata *pixdata, double texpos)
{
    while (pixdata->y_min != pixdata->y_max)
    {
        pixdata->xpm_pixel = data->xpm_imgs[0].adrs + data->xpm_imgs[0].size_line * pixdata->y_xpm +
            pixdata->x_offset * (data->xpm_imgs[0].bpp / 8);
        pixdata->pixel = data->img->adrs + data->img->size_line * pixdata->y_min +
            stripex * (data->img->bpp / 8);
        *(int *)pixdata->pixel = *(int *)pixdata->xpm_pixel;
        pixdata->y_xpm = (int)texpos & (texheight - 1);
        texpos += pixdata->step;
        pixdata->y_min++;
    }  
}
/*for side == 0 x_side hit*/
void    put_wall_side(t_data *data, int stripex, double distance, int side)
{
    t_pixdata pixdata;
    double  texpos;

    pixdata.slice_height = ((double)texheight / distance) * (projection_d); // this should be round up distance too small ? 
    pixdata.x_offset = (int)data->player->ver_hitx[stripex] % (texwidth - 1); // logical error. : should get actual position of the hit.
    //printf("for stripe %d of type 0 x offset is %d hit %f\n", stripex, x_offset, data->player->hitx);
    pixdata.step = 1.0 * texwidth / pixdata.slice_height;
    pixdata.y_min =  SCREEN_H / 2 - pixdata.slice_height / 2;
    if (pixdata.y_min < 0)
        pixdata.y_min = 0;
    pixdata.y_max = SCREEN_H / 2 + pixdata.slice_height / 2;
    if (pixdata.y_max >= SCREEN_H)
        pixdata.y_max = SCREEN_H - 1;
    texpos = (pixdata.y_min - SCREEN_H / 2 + pixdata.slice_height / 2) * pixdata.step;
    pixdata.y_xpm = (int)texpos & (texwidth -1);
    drawceiling(data, stripex, pixdata.y_min);
    draw_wall_side(data, stripex, &pixdata, texpos);
    drawfloor(data, stripex, pixdata.y_max);
}

void    drawceiling(t_data *data, int stripex, int y_min)
{
    int     i;
    char    *pixel;

    i = 0;
    while(i < y_min)
    {
        pixel = data->img->adrs + data->img->size_line * i +
            stripex * (data->img->bpp / 8);
        *(int *)pixel = CEILING_COLOR;
        i++;    
    }
}

void    drawfloor(t_data *data, int stripex, int y_max)
{
    char    *pixel;

    while(y_max < SCREEN_H)
    {
        pixel = data->img->adrs + data->img->size_line * y_max +
            stripex * (data->img->bpp / 8);
        *(int *)pixel = FLOOR_COLOR;
        y_max++;
    }
}

/*for side == 1 yside hit*/
void    draw_walls_1(t_data *data, t_pixdata* pixdata, int stripex, double texpos)
{
    while (pixdata->y_min != pixdata->y_max)
    {
        pixdata->xpm_pixel = data->xpm_imgs[1].adrs + data->xpm_imgs[1].size_line * pixdata->y_xpm +
            pixdata->x_offset * (data->xpm_imgs[1].bpp / 8);
        pixdata->pixel = data->img->adrs + data->img->size_line * pixdata->y_min +
            stripex * (data->img->bpp / 8);
        *(int *)pixdata->pixel = *(int *)pixdata->xpm_pixel;
        texpos += pixdata->step;
        pixdata->y_xpm = (int)texpos & (texheight - 1);
        pixdata->y_min++;
    }
}
void    put_wall(t_data *data, int stripex,  double distance, int side)
{
    t_pixdata pixdata;
    double  texpos;

    pixdata.y_xpm = 0;
    if (distance > sqrt(MAP_H * MAP_H + MAP_W * MAP_W)) /*BOTH VERTICAL AND HORIZONAL RETURNED HIGH VALUE*/
        distance = fabs(MAP_W - data->player->posx);
    pixdata.slice_height = ((double)texheight / distance) * (projection_d); // this should be round up distance too small ? 
    if (side == 0)
        return (put_wall_side(data, stripex, distance, side));
    pixdata.x_offset = (int)data->player->ver_hity[stripex] % (texheight - 1);//.this.
    pixdata.step = 1.0 * texheight / pixdata.slice_height; // by how much to increase  pix corrdinate.
    pixdata.y_min =  SCREEN_H / 2 - pixdata.slice_height / 2;
    if (pixdata.y_min < 0)
        pixdata.y_min = 0;
    pixdata.y_max = SCREEN_H / 2 + pixdata.slice_height / 2;
    if (pixdata.y_max >= SCREEN_H)
        pixdata.y_max = SCREEN_H - 1;
    texpos = (pixdata.y_min - SCREEN_H / 2 + pixdata.slice_height / 2) * pixdata.step;
    pixdata.y_xpm = (int)texpos & (texheight - 1);
    drawceiling(data, stripex, pixdata.y_min);
    draw_walls_1(data, &pixdata, stripex, texpos);
    drawfloor(data, stripex, pixdata.y_max);
}

void    put_walls(t_data *data)
{
    int i;

    i = 0;
    while  (i < SCREEN_W)
    {
        put_wall(data, i , data->player->distance[i], data->player->side[i]);
        i++;
    }
}

/*double   raycast(t_data *data, double castAngle, int *side)
{
    double horizontalray;
    double verticalray;
    double  ver_hitx;
    double  ver_hity;
    if (castAngle < 0)
        castAngle += 360.0;
    if (castAngle == 0 || castAngle == 180.0 || castAngle == 360)
    {
        *side = 1;
        return (x_axis_raycast(data, castAngle));
    }
    else if (castAngle == 90.0 || castAngle == 270.0)
    {
        *side = 0;
        return (y_axis_raycast(data, castAngle));
    }
    verticalray = verticalraycast(data, castAngle);
    ver_hitx = data->player->hitx;
    ver_hity = data->player->hity;
    horizontalray = horizontalraycast(data, castAngle);
    if (verticalray < horizontalray)
    {
        printf("for angle %f vertical height is %f because horizontal is %f\n", castAngle, verticalray, horizontalray);
        *side = 0;
        data->player->hitx = ver_hitx;
        data->player->hity = ver_hity;
        return (verticalray) * cos(degToRad(data->player->beta_angle));
    }
    *side = 1;
    //}
    //printf("distance to the wall is %f\n", horizontalray);
    //printf("corrected distance to the wall is %f\n", horizontalray * cos(degToRad(data->player->beta_angle)));
    printf("for angle %f horizontal height is %f because vertical was %f\n", castAngle, horizontalray,verticalray);
    return (horizontalray) * cos(degToRad(data->player->beta_angle));
}*/

void set_new_img(t_data *data)
{
    //if (data->img->mlx_img != NULL)/*here dont destroy the img untill the new img is ready*/
    //{
      //  mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
       // mlx_clear_window(data->mlx_ptr, data->win_ptr);
        //free(data->img->mlx_img);
        //data->img->mlx_img = NULL;
    //}
    data->img->mlx_img = mlx_new_image(data->mlx_ptr, SCREEN_W, SCREEN_H);
    data->img->adrs = mlx_get_data_addr(data->img->mlx_img, &(data->img->bpp), &(data->img->size_line), &(data->img->endian));
}

int render_walls(t_data *data)
{
    //double wallheight;
    int i;
    double  sep_angle;
    double   castAngle;
    int side;
    
    i = 0;
    //fflush(stdout);
    //printf("-------------------player view is %f---------------------\n", data->player->view_deg);
    sep_angle = (double)FOW / SCREEN_W;
    angle = data->player->view_deg;
    castAngle = data->player->view_deg + (double)FOW / 2;
    //update_ray_dir(&(data->ray), data->player->view_deg);
    //printf("cast angle is %f\n", castAngle);
    data->player->beta_angle = (double)FOW / 2; // works better than FOW / 2 somehow.
    //printf("start boxX[%d] boxY[%d]\n", (int)data->player->posx / 64, (int)data->player->posy / 64);
    //printf("beta angle is %f\n", data->player->beta_angle);
    set_new_img(data);
    while (i < SCREEN_W)
    {
        //printf("cast angle is %f\n", castAngle);
        data->player->distance[i] = raycast_1(data, castAngle, data->player->side + i, i);
        //printf("for cast angle %f wallheight is %f side is %d\n", castAngle, wallheight, side);
        //printf("stripex is %d side is %d\n", i, side);
        //if (castAngle > -12 && castAngle < -8)
        castAngle -= sep_angle;
        data->player->beta_angle -= sep_angle;
        i++;
    }
    put_walls(data);
    // swap images.
    //mlx_clear_window(data->mlx_ptr, data->win_ptr);
    // destroy old img.
    if (data->old_img->mlx_img)/*should just be an address n need to allocat*/
        mlx_destroy_image(data->mlx_ptr, data->old_img->mlx_img);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->mlx_img, 0, 0);
    show_player_data(data); // write on top of new img
    put_mini_map(data);
    // this img becomes the old img
    data->old_img->mlx_img = data->img->mlx_img;
    return (0);
}