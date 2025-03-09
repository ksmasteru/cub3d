/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <hes-saqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:55 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/02/22 19:22:22 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_data(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (-1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCREEN_W, SCREEN_H, "CUB3D");
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (-1);
	data->img = malloc(sizeof(t_image));
	data->old_img = malloc(sizeof(t_image));
	if (!data->old_img)
		return (-1);
	data->old_img->mlx_img = NULL;
	data->player->beta_angle = (double)FOW / 2;
	if (set_up_wall_xpms(data) != 0)
	{
		free_t_map_data(data->map_data);
		return (1);
	}
	data->mini_map = malloc(sizeof(t_image));
	if (!data->mini_map)
		return (-1);
	return (init_data2(data));
}

void	init_player_data(t_data *data)
{
	if (data->map_data->player_dir == 'N')
		data->player->view_deg = 91;
	else if (data->map_data->player_dir == 'E')
		data->player->view_deg = 181;
	else if (data->map_data->player_dir == 'S')
		data->player->view_deg = 271;
	else
		data->player->view_deg = 1;
	data->map_data->w = data->texwidth * data->map_data->map_width;
	data->map_data->h = data->texheight * data->map_data->map_height;
	set_2d_int_map(data);
}
