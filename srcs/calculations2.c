/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <hes-saqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:55 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/02/22 18:41:39 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#define M_PI 3.14159265358979323846264338327950288

double	horizontalraycast_1(t_data *data, double castAngle, int i)
{
	t_rayvars	rayvars;

	rayvars.xa = data->texwidth;
	rayvars.ya = tan(degtorad(castAngle)) * data->texheight * -1;
	rayvars.rx = (((int)data->player->posx / data->texwidth)
			* data->texwidth) + data->texwidth;
	data->player->box_x = (int)rayvars.rx / data->texwidth;
	rayvars.ry = tan(degtorad(castAngle)) * (rayvars.rx - data->player->posx);
	rayvars.ry = data->player->posy - fabs(rayvars.ry);
	data->player->box_y = (int)rayvars.ry / data->texheight;
	if (rayvars.ry < 0)
		return (1e30);
	while (data->map[data->player->box_y][data->player->box_x] == 0)
	{
		rayvars.ry += rayvars.ya;
		rayvars.rx += rayvars.xa;
		if (rayvars.ry < 0)
			return (1e30);
		data->player->box_x = (int)rayvars.rx / data->texwidth;
		data->player->box_y = (int)rayvars.ry / data->texheight;
	}
	data->player->hor_hitx[i] = rayvars.rx;
	data->player->hor_hity[i] = rayvars.ry;
	return (calculate_distance(data, rayvars.rx, rayvars.ry, castAngle));
}

double	horizontalraycast_2(t_data *data, double castAngle, int i)
{
	t_rayvars	rayvars;

	rayvars.xa = data->texwidth * -1;
	rayvars.ya = tan(degtorad(castAngle)) * data->texheight;
	rayvars.rx = ((int)data->player->posx / data->texwidth)
		* data->texwidth;
	data->player->box_x = (int)(rayvars.rx - 1) / data->texwidth;
	rayvars.ry = tan(degtorad(castAngle)) * (data->player->posx - rayvars.rx);
	rayvars.ry = data->player->posy - fabs(rayvars.ry);
	data->player->box_y = (int)rayvars.ry / data->texheight;
	if (rayvars.ry < 0)
		return (1e30);
	while (data->map[data->player->box_y][data->player->box_x] == 0)
	{
		rayvars.ry += rayvars.ya;
		rayvars.rx += rayvars.xa;
		if (rayvars.ry < 0)
			return (1e30);
		data->player->box_x = (int)(rayvars.rx - 1) / data->texwidth;
		data->player->box_y = (int)rayvars.ry / data->texwidth;
	}
	data->player->hor_hitx[i] = rayvars.rx;
	data->player->hor_hity[i] = rayvars.ry;
	return (calculate_distance(data, rayvars.rx, rayvars.ry, castAngle));
}

double	horizontalraycast_3(t_data *data, double castAngle, int i)
{
	t_rayvars	rayvars;

	rayvars.xa = data->texwidth * -1;
	rayvars.ya = tan(degtorad(castAngle)) * data->texheight;
	rayvars.rx = ((int)data->player->posx / data->texwidth) * data->texwidth;
	data->player->box_x = (int)(rayvars.rx - 1) / data->texwidth;
	rayvars.ry = tan(degtorad(castAngle)) * (data->player->posx - rayvars.rx);
	rayvars.ry = data->player->posy + fabs(rayvars.ry);
	data->player->box_y = (int)rayvars.ry / data->texheight;
	if (rayvars.ry > data->map_data->h)
		return (1e30);
	while (data->map[data->player->box_y][data->player->box_x] == 0)
	{
		rayvars.ry += rayvars.ya;
		rayvars.rx += rayvars.xa;
		if (rayvars.ry > data->map_data->h)
			return (1e30);
		data->player->box_x = (int)(rayvars.rx - 1) / data->texwidth;
		data->player->box_y = (int)rayvars.ry / data->texheight;
	}
	data->player->hor_hitx[i] = rayvars.rx;
	data->player->hor_hity[i] = rayvars.ry;
	return (calculate_distance(data, rayvars.rx, rayvars.ry, castAngle));
}

double	horizontalraycast_4(t_data *data, double castAngle, int i)
{
	t_rayvars	rayvars;

	rayvars.xa = data->texwidth;
	rayvars.ya = tan(degtorad(castAngle)) * data->texheight * -1;
	rayvars.rx = (((int)data->player->posx / data->texwidth)
			* data->texwidth) + data->texwidth;
	data->player->box_x = (int)rayvars.rx / data->texwidth;
	rayvars.ry = tan(degtorad(castAngle)) * (rayvars.rx - data->player->posx);
	rayvars.ry = data->player->posy + fabs(rayvars.ry);
	data->player->box_y = (int)rayvars.ry / data->texheight;
	if (rayvars.ry > data->map_data->h)
		return (1e30);
	while (data->map[data->player->box_y][data->player->box_x] == 0)
	{
		rayvars.ry += rayvars.ya;
		if (rayvars.ry > data->map_data->h)
			return (1e30);
		rayvars.rx += rayvars.xa;
		data->player->box_x = (int)(rayvars.rx) / data->texwidth;
		data->player->box_y = (int)rayvars.ry / data->texheight;
	}
	data->player->hor_hitx[i] = rayvars.rx;
	data->player->hor_hity[i] = rayvars.ry;
	return (calculate_distance(data, rayvars.rx, rayvars.ry, castAngle));
}
