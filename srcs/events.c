#include "../includes/cub3d.h"
#include <stdbool.h>

#define map_w 24
#define map_h 24
extern int map[24][24];
extern double angle;

int	close_win(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(0);
}

bool player_slide_xside(t_data *data)
{
	double old_posy;

	old_posy = data->player->posy;	
	if (data->ray.dir_y > 0)
		data->player->posy += fabs(SLIDE_SPEED * sin(data->player->view_deg));
	else
		data->player->posy -= fabs(SLIDE_SPEED * sin(data->player->view_deg));
	if (map[(int)data->player->posy / texheight][(int)data->player->posx / texwidth] != 0)
	{
		data->player->posy = old_posy;
		return (false);
	}
	return (true);
}

bool	update_player_posy_upkey(t_data *data, int keycode, double ratio, double castAngle)
{
	double	ratio_y;
	double	old_posy;
	int		wally;
	int		boxy;

	ratio_y = MOVE_SPEED * sin(degToRad(castAngle)) * ratio * -1.00;
	if (map[(int)(data->player->posy + ratio_y) / texheight][(int)data->player->posx / texwidth] != 0)
		return (false);
	data->player->posy += ratio_y;
	if (data->ray.dir_y > 0)
	{
		wally = (int)data->player->posy / texheight * texheight + texheight;
		boxy = wally / texheight;
	}
	else
	{
		wally = (int)data->player->posy / texheight * texheight;
		boxy = (wally - 1) / texheight;
	}
	if (map[boxy][(int)data->player->posx / texwidth] != 0 && (abs(wally - (int)data->player->posy) < WALL_BUFFER))
		data->player->posy = wally + WALL_BUFFER * data->ray.dir_y * -1;
	return (true);
}

bool	update_player_posy_downkey(t_data	*data, int keycode, double ratio, double castAngle)
{
	double	ratio_y;
	double	old_posy;
	int		wally;
	int		boxy;

	ratio_y = MOVE_SPEED * sin(degToRad(castAngle)) * ratio;
	if ((map[(int)(data->player->posy + ratio_y) / texheight][(int)data->player->posx / texwidth] != 0))
		return (false);
	data->player->posy += ratio_y;
	if (data->ray.dir_y > 0)
	{
		wally = (int)data->player->posy / texheight * texheight;
		boxy = (wally - 1) / texheight;
	}
	else
	{
		wally = (int)data->player->posy / texheight * texheight + texheight;
		boxy = wally / texheight;
	}
	if (map[boxy][(int)data->player->posx / texwidth] != 0 && (abs(wally - (int)data->player->posy) < WALL_BUFFER))
		data->player->posy = wally + SLIDE_CST + WALL_BUFFER * data->ray.dir_y;
	return (true);
}

bool	update_player_posx_upkey(t_data *data, int keycode, double ratio, double castAngle)
{
	double	ratio_x;
	double	old_posx;
	int		wallx;
	int		box_x;

	ratio_x = MOVE_SPEED * cos(degToRad(castAngle)) * ratio;
	if ((map[(int)data->player->posy / texheight][(int)(data->player->posx + ratio_x) / texwidth] != 0))
		return (false);
	data->player->posx += ratio_x;
	if (data->ray.dir_x > 0)
	{
		wallx = (int)data->player->posx / texwidth * texwidth + texwidth;
		box_x = wallx / texwidth;
	}
	else
	{
		wallx = (int)data->player->posx / texwidth * texwidth;
		box_x = (wallx - 1) / texwidth;
	}
	if (map[(int)data->player->posy /texheight][box_x] != 0 && (abs(wallx - (int)data->player->posx) < WALL_BUFFER))
		data->player->posx = wallx + SLIDE_CST + WALL_BUFFER * data->ray.dir_x * -1;
	return (true);
}

bool	update_player_posx_downkey(t_data *data, int keycode, double ratio, double castAngle)
{
	double	ratio_x;
	double	old_posx;
	int		wallx;
	int		box_x;

	ratio_x = MOVE_SPEED * cos(degToRad(castAngle)) * ratio * -1.00;
	if ((map[(int)data->player->posy / texheight][(int)(data->player->posx + ratio_x) / texwidth] != 0))
		return (false);
	data->player->posx += ratio_x;
	if (data->ray.dir_x > 0)
	{
		wallx = (int)data->player->posx / texwidth * texwidth;
		box_x = (wallx - 1) / texwidth;
	}
	else
	{
		wallx = (int)data->player->posx / texwidth * texwidth + texwidth;
		box_x = wallx / texwidth;
	}
	if (map[(int)data->player->posy /texheight][box_x] != 0 && (abs(wallx - (int)data->player->posx) < WALL_BUFFER))
		data->player->posx = wallx + SLIDE_CST +WALL_BUFFER * data->ray.dir_x;
	return (true);
}

bool update_player_pos(t_data *data, int keycode, double ratio)
{
	bool boolx;
	bool booly;
	double	castAngle;
	castAngle = data->player->view_deg;
	if (castAngle == 0 || castAngle == 90 || castAngle == 270
		|| castAngle == 180 || castAngle == 360)
		castAngle += 1;
	update_ray_dir(&(data->ray), castAngle);
	if (keycode == XK_Up)
	{
		boolx = update_player_posx_upkey(data, keycode, ratio, castAngle);
		booly = update_player_posy_upkey(data, keycode, ratio, castAngle);
	}
	else if (keycode == XK_Down)
	{
		boolx = update_player_posx_downkey(data, keycode, ratio, castAngle);
		booly = update_player_posy_downkey(data, keycode, ratio, castAngle);
	}
	if (boolx || booly)
		return (true);
	return (false);
}

bool rotate_player_dir(t_data *data, int keycode, double ratio)
{
	if (keycode == XK_Right)
	{
		data->player->view_deg -= ratio * ROTSPEED * 10;
		if (data->player->view_deg < -180)
			data->player->view_deg = 180 - abs((int)data->player->view_deg) % 180;
	}
	else
		data->player->view_deg = (int)(ratio * ROTSPEED * 10 + data->player->view_deg) % 360;
	return (true);
}

int	pressed_key_event(int keycode, t_data *data)
{
  bool update_img;
  update_img = true;
	if (keycode == 53 || keycode  == XK_Up || keycode == XK_Down
    		|| keycode == XK_Right || keycode == XK_Left)
	{
		if (keycode == 53)
	    	close_win(data);
		else if (keycode == XK_Down || keycode == XK_Up)
			update_img = update_player_pos(data, keycode, 0.3);
        else if (keycode == XK_Right || keycode == XK_Left)
            update_img = rotate_player_dir(data, keycode, 0.3);
		if (update_img)
            render_walls(data);
	}
    return (0);
}