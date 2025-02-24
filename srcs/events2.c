/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <hes-saqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:55 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/02/22 18:42:04 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdbool.h>

int	close_win(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(0);
}

bool	player_slide_xside(t_data *data)
{
	double	old_posy;

	old_posy = data->player->posy;
	if (data->ray.dir_y > 0)
		data->player->posy += fabs(SLIDE_SPEED * sin(data->player->view_deg));
	else
		data->player->posy -= fabs(SLIDE_SPEED * sin(data->player->view_deg));
	if (data->map[(int)data->player->posy / texheight][(int)data->player->posx
		/ texwidth] != 0)
	{
		data->player->posy = old_posy;
		return (false);
	}
	return (true);
}

bool	update_player_posy_upkey(t_data *data, int keycode, double ratio,
		double castAngle)
{
	double	ratio_y;
	double	old_posy;
	int		wally;
	int		boxy;

	ratio_y = MOVE_SPEED * sin(degtorad(castAngle)) * ratio * -1.00;
	if (data->map[(int)(data->player->posy + ratio_y)
		/ texheight][(int)data->player->posx / texwidth] != 0)
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
	if (data->map[boxy][(int)data->player->posx / texwidth] != 0 && (abs(wally
				- (int)data->player->posy) < WALL_BUFFER))
		data->player->posy = wally + WALL_BUFFER * data->ray.dir_y * -1;
	return (true);
}

bool	update_player_posy_downkey(t_data *data, int keycode, double ratio,
		double castAngle)
{
	double	ratio_y;
	double	old_posy;
	int		wally;
	int		boxy;

	ratio_y = MOVE_SPEED * sin(degtorad(castAngle)) * ratio;
	if ((data->map[(int)(data->player->posy + ratio_y)
			/ texheight][(int)data->player->posx / texwidth] != 0))
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
	if (data->map[boxy][(int)data->player->posx / texwidth] != 0 && (abs(wally
				- (int)data->player->posy) < WALL_BUFFER))
		data->player->posy = wally + SLIDE_CST + WALL_BUFFER * data->ray.dir_y;
	return (true);
}
