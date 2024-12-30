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
#define MAP_W1 512
#define MAP_H1 512
#define MINI_MAP_H   (MAP_W / 10)
#define MINI_MAP_W  (MAP_H / 10)
#define FOW 60
#define ROTSPEED 1.5
#define MOVE_SPEED 31.0
#define w 24
#define h 24
#define h1 8
#define w1 8
#define M_PI   3.14159265358979323846264338327950288
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)
#define projection_d (SCREEN_W / 2) * tan(degToRad(30))
#define TEXTURES_NUMBERS 3
typedef struct s_player{
     double    posx;
     double    posy;
     double    view_deg;
     double    beta_angle;
     double    hitx;
     double    hity;
     int       box_x;
     int       box_y;
     int       wall_type;
     double    ver_hitx;
     double    ver_hity;
     double    hor_hitx;
     double    hor_hity;
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
     t_image   *mini_map;
     t_image   *xpm_imgs;
     t_ray     ray;
}t_data;

typedef struct s_map{
     int  mini_map_w;
     int  mini_map_h;
     int  w_pixels;
     int  h_pixels;
     int  p_x;
     int  p_y;
}t_map;

int	close_win(t_data *data);
int render_walls(t_data *data);
bool rotate_player_dir(t_data *data, int keycode, double ratio);
int	pressed_key_event(int keycode, t_data *data);
double   horizontalraycast(t_data *data, double castAngle);
double   verticalraycast(t_data *data, double castAngle);
double   raycast(t_data *data, double castAngle, int *side);
void set_new_img(t_data *data);
double  calculate_distance(t_data *data, double cx, double cy, double castAngle);
double   x_axis_raycast(t_data *data, double castAngle);
double  y_axis_raycast(t_data *data, double castAngle);
void update_ray_dir(t_ray *ray, double view_deg);
bool player_move_down(t_data *data, double old_posx, double old_posy, double ratio);
bool player_move_up(t_data *data, double old_posx, double old_posy, double ratio);
bool update_player_pos(t_data *data, int keycode, double ratio);
void	show_player_data(t_data *data);
char	*ft_strdup2(char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin2(char *s1, char *s2, char *str);
char		*ft_itoa(int num);
static int	count_size(int n);
void    put_wall_side(t_data *data, int stripex, double distance, int side);
int  put_mini_map(t_data *data);
double  vertical_casting_1(t_data *data, double castangle);
double  vertical_casting_2(t_data *data, double castangle);
double  vertical_casting_3(t_data *data, double castangle);
double  vertical_casting_4(t_data *data, double castangle);
double   horizontalraycast_1(t_data *data, double castAngle);
double   horizontalraycast_2(t_data *data, double castAngle);
double   horizontalraycast_3(t_data *data, double castAngle);
double   horizontalraycast_4(t_data *data, double castAngle);
double  raycast_1(t_data   *data, double castangle, int *side);
#endif