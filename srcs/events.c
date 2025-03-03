/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <hes-saqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:55 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/02/22 18:48:36 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdbool.h>

bool	update_player_posx_upkey(t_data *data, double ratio,
		double castAngle)
{
	t_wallvars	wallvars;

	wallvars.ratio_x = MOVE_SPEED * cos(degtorad(castAngle)) * ratio;
	if ((data->map[(int)data->player->posy
				/ data->texheight][(int)(data->player->posx + wallvars.ratio_x)
		/ data->texwidth] != 0))
		return (false);
	data->player->posx += wallvars.ratio_x;
	if (data->ray.dir_x > 0)
	{
		wallvars.wallx = (int)data->player->posx / data->texwidth
			* data->texwidth + data->texwidth;
		wallvars.box_x = wallvars.wallx / data->texwidth;
	}
	else
	{
		wallvars.wallx = (int)data->player->posx / data->texwidth
			* data->texwidth;
		wallvars.box_x = (wallvars.wallx - 1) / data->texwidth;
	}
	if (data->map[(int)data->player->posy / data->texheight][wallvars.box_x]
		!= 0 && (abs(wallvars.wallx - (int)data->player->posx) < W_B))
		data->player->posx = wallvars.wallx + S + W_B
			* data->ray.dir_x * (-1);
	return (true);
}

bool	update_player_posx_downkey(t_data *data, double ratio,
		double castAngle)
{
	t_wallvars	wallvars;

	wallvars.ratio_x = MOVE_SPEED * cos(degtorad(castAngle)) * ratio * -1.00;
	if ((data->map[(int)data->player->posy
				/ data->texheight][(int)(data->player->posx + wallvars.ratio_x)
		/ data->texwidth] != 0))
		return (false);
	data->player->posx += wallvars.ratio_x;
	if (data->ray.dir_x > 0)
	{
		wallvars.wallx = (int)data->player->posx / data->texwidth
			* data->texwidth;
		wallvars.box_x = (wallvars.wallx - 1) / data->texwidth;
	}
	else
	{
		wallvars.wallx = (int)data->player->posx / data->texwidth
			* data->texwidth + data->texwidth;
		wallvars.box_x = wallvars.wallx / data->texwidth;
	}
	if (data->map[(int)data->player->posy / data->texheight][wallvars.box_x]
		!= 0 && (abs(wallvars.wallx - (int)data->player->posx) < W_B))
		data->player->posx = wallvars.wallx + S + W_B * data->ray.dir_x;
	return (true);
}

bool	update_player_pos(t_data *data, int keycode, double ratio)
{
	bool	boolx;
	bool	booly;
	double	castangle;

	castangle = data->player->view_deg;
	if (castangle == 0 || castangle == 90 || castangle == 270
		|| castangle == 180 || castangle == 360)
		castangle += 1;
	update_ray_dir(&(data->ray), castangle);
	if (keycode == XK_Up)
	{
		boolx = update_player_posx_upkey(data, ratio, castangle);
		booly = update_player_posy_upkey(data, ratio, castangle);
	}
	else if (keycode == XK_Down)
	{
		boolx = update_player_posx_downkey(data, ratio, castangle);
		booly = update_player_posy_downkey(data, ratio, castangle);
	}
	if (boolx || booly)
		return (true);
	return (false);
}

bool	rotate_player_dir(t_data *data, int keycode, double ratio)
{
	if (keycode == XK_Right)
	{
		data->player->view_deg -= ratio * ROTSPEED * 10;
		if (data->player->view_deg < -180)
			data->player->view_deg = 180 - abs((int)data->player->view_deg)
				% 180;
	}
	else
		data->player->view_deg = (int)(ratio * ROTSPEED * 10
				+ data->player->view_deg) % 360;
	return (true);
}

int	pressed_key_event(int keycode, t_data *data)
{
	bool	update_img;

	update_img = true;
	if (keycode == 53 || keycode == XK_Up || keycode == XK_Down
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
