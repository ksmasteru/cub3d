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

void	free_t_data(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->map_data->map_height)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
}

int	close_win(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	free_t_map_data(data->map_data);
	free_t_data(data);
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
	if (data->map[(int)data->player->posy / data->texheight]
		[(int)data->player->posx / data->texwidth] != 0)
	{
		data->player->posy = old_posy;
		return (false);
	}
	return (true);
}

bool	update_player_posy_upkey(t_data *data, double ratio,
		double castangle)
{
	double	ratio_y;
	int		wally;
	int		boxy;

	ratio_y = MOVE_SPEED * sin(degtorad(castangle)) * ratio * -1.00;
	if (data->map[(int)(data->player->posy + ratio_y)
		/ data->texheight][(int)data->player->posx / data->texwidth] != 0)
		return (false);
	data->player->posy += ratio_y;
	if (data->ray.dir_y > 0)
	{
		wally = (int)data->player->posy / data->texheight
			* data->texheight + data->texheight;
		boxy = wally / data->texheight;
	}
	else
	{
		wally = (int)data->player->posy / data->texheight
			* data->texheight;
		boxy = (wally - 1) / data->texheight;
	}
	if (data->map[boxy][(int)data->player->posx / data->texwidth] != 0
		&& (abs(wally - (int)data->player->posy) < W_B))
		data->player->posy = wally + W_B * data->ray.dir_y * -1;
	return (true);
}

bool	update_player_posy_downkey(t_data *data, double ratio, double castAngle)
{
	double	ratio_y;
	int		wally;
	int		boxy;

	ratio_y = MOVE_SPEED * sin(degtorad(castAngle)) * ratio;
	if ((data->map[(int)(data->player->posy + ratio_y)
			/ data->texheight][(int)data->player->posx / data->texwidth] != 0))
		return (false);
	data->player->posy += ratio_y;
	if (data->ray.dir_y > 0)
	{
		wally = (int)data->player->posy / data->texheight * data->texheight;
		boxy = (wally - 1) / data->texheight;
	}
	else
	{
		wally = (int)data->player->posy / data->texheight
			* data->texheight + data->texheight;
		boxy = wally / data->texheight;
	}
	if (data->map[boxy][(int)data->player->posx / data->texwidth] != 0
		&& (abs(wally - (int)data->player->posy) < W_B))
		data->player->posy = wally + S + W_B * data->ray.dir_y;
	return (true);
}
