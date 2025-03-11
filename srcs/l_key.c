/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_key.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:32:55 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/03/11 17:36:57 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdbool.h>

void	update_lkey_x1(t_data *data, t_wallvars *wallvars)
{
	data->player->posx += wallvars->ratio_x;
	wallvars->wallx = (int)data->player->posx / data->texwidth * data->texwidth;
	wallvars->box_x = (wallvars->wallx - 1) / data->texwidth;
	if (data->map[(int)data->player->posy
			/ data->texheight][wallvars->box_x] != 0 && (abs(wallvars->wallx
				- (int)data->player->posx) < W_B))
		data->player->posx = wallvars->wallx + S + W_B;
}

void	update_lkey_x2(t_data *data, t_wallvars *wallvars)
{
	data->player->posx += wallvars->ratio_x;
	wallvars->wallx = (int)data->player->posx / data->texwidth * data->texwidth
		+ data->texwidth;
	wallvars->box_x = wallvars->wallx / data->texwidth;
	if (data->map[(int)data->player->posy
			/ data->texheight][wallvars->box_x] != 0 && (abs(wallvars->wallx
				- (int)data->player->posx) < W_B))
		data->player->posx = wallvars->wallx + S + W_B * -1;
}

void	update_lkey_y1(t_data *data, t_wallvars *wallvars)
{
	data->player->posy += wallvars->ratio_y;
	wallvars->wally = (int)data->player->posy / data->texheight
		* data->texheight + data->texheight;
	wallvars->box_y = wallvars->wally / data->texheight;
	if (data->map[wallvars->box_y][(int)data->player->posx
		/ data->texwidth] != 0 && (abs(wallvars->wally
				- (int)data->player->posy) < W_B))
		data->player->posy = wallvars->wally + S + W_B * -1;
}

void	update_lkey_y2(t_data *data, t_wallvars *wallvars)
{
	data->player->posy -= wallvars->ratio_y;
	wallvars->wally = (int)data->player->posy / data->texheight
		* data->texheight;
	wallvars->box_y = (wallvars->wally - 1) / data->texheight;
	if (data->map[wallvars->box_y][(int)data->player->posx
		/ data->texwidth] != 0 && (abs(wallvars->wally
				- (int)data->player->posy) < W_B))
		data->player->posy = wallvars->wally + S + W_B;
}
