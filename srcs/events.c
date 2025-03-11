/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <hes-saqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:55 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/03/11 21:01:40 by hes-saqu         ###   ########.fr       */
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

bool	update_player_pos(t_data *data, int keycode,
	double ratio, double castangle)
{
	bool	boolx;
	bool	booly;

	if (keycode == XK_w)
	{
		boolx = update_player_posx_upkey(data, ratio, castangle);
		booly = update_player_posy_upkey(data, ratio, castangle);
	}
	else if (keycode == XK_s)
	{
		boolx = update_player_posx_downkey(data, ratio, castangle);
		booly = update_player_posy_downkey(data, ratio, castangle);
	}
	else if (keycode == XK_d)
	{
		boolx = update_player_posx_rkey(data, ratio, castangle);
		booly = update_player_posy_rkey(data, ratio, castangle);
	}
	else if (keycode == XK_a)
	{
		boolx = update_player_posx_lkey(data, ratio, castangle);
		booly = update_player_posy_lkey(data, ratio, castangle);
	}
	return (boolx || booly);
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
	double	castangle;

	update_img = true;
	castangle = fixed_angle(data);
	if (keycode == XK_Escape || keycode == XK_w || keycode == XK_s
		|| keycode == XK_a || keycode == XK_d
		|| keycode == XK_Right || keycode == XK_Left)
	{
		update_ray_dir(&(data->ray), castangle);
		if (keycode == XK_Escape)
			close_win(data);
		else if (keycode == XK_w || keycode == XK_s || keycode == XK_a
			|| keycode == XK_d)
			update_img = update_player_pos(data, keycode, 0.3, castangle);
		else if (keycode == XK_Right || keycode == XK_Left)
			update_img = rotate_player_dir(data, keycode, 0.3);
		if (update_img)
			render_walls(data);
	}
	return (0);
}
