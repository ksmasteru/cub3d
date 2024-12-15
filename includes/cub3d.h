#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
# include <X11/keysym.h>
// THE MAP HAS NOTHING TO DO WITH THE SCREEN : FOW OF PLAYER IS THE SCREEN.
#define texheight 64
#define texwidth 64
#define SCREEN_W 640
#define SCREEN_H 480
#define MAP_W 1536
#define MAP_H 1536
#define FOW 60
#define ROTSPEED 1.5
#define MOVE_SPEED 31
typedef struct s_player{
     double posx;
     double posy;
     double view_deg;
     double beta_angle;
}t_player;

typedef struct s_image{
     void      *mlx_img;
     int       bpp;
     int       endian;
     int       size_line;
     char      *adrs;
}t_image;

typedef struct s_ray
{
     int dir_x;
     int dir_y;
}t_ray;

typedef struct s_data{
     t_player *player;
     void      *mlx_ptr;
     void      *win_ptr;
     t_image   *img;
     t_ray     ray;
}t_data;


int	close_win(t_data *data);
int render_walls(t_data *data);
bool update_player_pos(t_data *data, int scale);
bool rotate_player_dir(t_data *data, int keycode);
int	pressed_key_event(int keycode, t_data *data);
double   horizontalraycast(t_data *data, double castAngle);
double   verticalraycast(t_data *data, double castAngle);
double   raycast(t_data *data, double castAngle);
void set_new_img(t_data *data);
double  calculate_distance(t_data *data, double cx, double cy, double castAngle);
double   x_axis_raycast(t_data *data, double castAngle);
double  y_axis_raycast(t_data *data, double castAngle);
void update_ray_dir(t_ray *ray, double view_deg);
#endif