/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:27:25 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/03/01 19:27:29 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include "parsing.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TEXHEIGHT 64
# define TEXWDITH 64
# define SCREEN_W 640
# define SCREEN_H 480
# define FOW 60
# define ROTSPEED 1.5
# define MOVE_SPEED 32.0
# define H1 8
# define S 2.0
# define TEXTURES_NUMBERS 4
# define FLOOR_COLOR 0x808080
# define CEILING_COLOR 0x404040
# define SLIDE_SPEED 7.0
# define W_B 20.0
# define SLIDE_CST 2.0

typedef struct s_wallvars
{
	double		ratio_x;
	int			wallx;
	int			box_x;
}				t_wallvars;

typedef struct s_rayvars
{
	int			hit;
	double		rx;
	double		ry;
	double		xa;
	double		ya;
}				t_rayvars;

typedef struct s_pixdata
{
	int			slice_height;
	char		*xpm_pixel;
	int			x_xpm;
	int			y_xpm;
	int			x_offset;
	int			pixel_repeat;
	char		*pixel;
	double		step;
	double		texpos;
	int			color;
	int			y_max;
	int			y_min;
	double		projection_d;
}				t_pixdata;

typedef struct s_player
{
	double		posx;
	double		posy;
	double		view_deg;
	double		beta_angle;
	double		hitx;
	int			mouse_x;
	double		hity;
	int			box_x;
	int			box_y;
	int			wall_type;
	double		*ver_hitx;
	double		*ver_hity;
	double		*hor_hitx;
	double		*hor_hity;
	double		*distance;
	int			*side;
}				t_player;

typedef struct s_image
{
	void		*mlx_img;
	int			bpp;
	int			endian;
	int			size_line;
	char		*adrs;
}				t_image;

typedef struct s_ray
{
	int			dir_x;
	int			dir_y;
}				t_ray;

typedef struct s_data
{
	t_player	*player;
	int			**map;
	void		*mlx_ptr;
	void		*win_ptr;
	int			texwidth;
	int			texheight;
	t_image		*img;
	t_image		*old_img;
	t_image		*mini_map;
	t_image		*xpm_imgs;
	t_ray		ray;
	t_map_data	*map_data;
}				t_data;

typedef struct s_map
{
	int			mini_map_w;
	int			mini_map_h;
	int			w_pixels;
	int			h_pixels;
	int			p_x;
	int			p_y;
}				t_map;

int				close_win(t_data *data);
int				render_walls(t_data *data);
bool			rotate_player_dir(t_data *data, int keycode, double ratio);
int				pressed_key_event(int keycode, t_data *data);
double			horizontalraycast(t_data *data, double castAngle, int i);
double			verticalraycast(t_data *data, double castAngle, int i);
double			raycast(t_data *data, double castAngle, int *side);
void			set_new_img(t_data *data);
double			calculate_distance(t_data *data, double cx, double cy,
					double castAngle);
double			x_axis_raycast(t_data *data, double castAngle, int i);
double			y_axis_raycast(t_data *data, double castAngle, int i);
void			update_ray_dir(t_ray *ray, double view_deg);
bool			player_move_down(t_data *data, double old_posx, double old_posy,
					double ratio);
bool			player_move_up(t_data *data, double old_posx, double old_posy,
					double ratio);
bool			update_player_pos(t_data *data, int keycode, double ratio);
void			show_player_data(t_data *data);
char			*ft_strdup2(char *s1);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strjoin2(char *s1, char *s2, char *str);
char			*ft_itoa(int num);
void			put_wall_side(t_data *data, int stripex, double distance,
					int side);
int				put_mini_map(t_data *data);
double			vertical_casting_1(t_data *data, double castangle, int i);
double			vertical_casting_2(t_data *data, double castangle, int i);
double			vertical_casting_3(t_data *data, double castangle, int i);
double			vertical_casting_4(t_data *data, double castangle, int i);
double			horizontalraycast_1(t_data *data, double castAngle, int i);
double			horizontalraycast_2(t_data *data, double castAngle, int i);
double			horizontalraycast_3(t_data *data, double castAngle, int i);
double			horizontalraycast_4(t_data *data, double castAngle, int i);
double			raycast_1(t_data *data, double castangle, int *side, int i);
void			drawceiling(t_data *data, int stripex, int y_min);
void			drawfloor(t_data *data, int stripex, int y_max);
double			degtorad(double degrees);
double			radtodeg(double radians);
t_map_data		*parse_cub_file(int ac, char **av);
void			init_player_data(t_data *data);
void			set_2d_int_map(t_data *data);
void			set_wall_type(t_data *data, int side);
void			free_t_map_data(t_map_data *data);
int				init_data(int ac, char **av, t_data *data);
#endif
