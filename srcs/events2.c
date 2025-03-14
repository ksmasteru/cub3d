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

void	free_data(t_data	*data)
{
	if (data->player)
		free(data->player);
}

int	close_win(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->mini_map->mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->xpm_imgs[0].mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->xpm_imgs[1].mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->xpm_imgs[2].mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->xpm_imgs[3].mlx_img);
	free(data->img);
	free(data->mini_map);
	free(data->xpm_imgs);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free_t_map_data(data->map_data);
	free_t_data(data);
	free_data(data);
	mlx_destroy_display(data->mlx_ptr);
	exit(0);
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
