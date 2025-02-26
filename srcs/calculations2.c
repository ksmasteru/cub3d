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
	double		distance;
	t_rayvars	rayvars;

	rayvars.xa = texwidth;
	rayvars.ya = tan(degtorad(castAngle)) * texheight * -1;
	rayvars.rx = (((int)data->player->posx >> 6) << 6) + texwidth;
	data->player->box_x = (int)rayvars.rx >> 6;
	rayvars.ry = tan(degtorad(castAngle)) * (rayvars.rx - data->player->posx);
	rayvars.ry = data->player->posy - fabs(rayvars.ry);
	data->player->box_y = (int)rayvars.ry >> 6;
	if (rayvars.ry < 0)
		return (1e30);
	while (data->map[data->player->box_y][data->player->box_x] == 0)
	{
		rayvars.ry += rayvars.ya;
		rayvars.rx += rayvars.xa;
		if (rayvars.ry < 0)
			return (1e30);
		data->player->box_x = (int)rayvars.rx >> 6;
		data->player->box_y = (int)rayvars.ry >> 6;
	}
	data->player->hor_hitx[i] = rayvars.rx;
	data->player->hor_hity[i] = rayvars.ry;
	distance = calculate_distance(data, rayvars.rx, rayvars.ry, castAngle);
	return (distance);
}

double	horizontalraycast_2(t_data *data, double castAngle, int i)
{
	double		distance;
	t_rayvars	rayvars;

	rayvars.xa = texwidth * -1;
	rayvars.ya = tan(degtorad(castAngle)) * texheight;
	rayvars.rx = ((int)data->player->posx >> 6) << 6;
	data->player->box_x = (int)(rayvars.rx - 1) >> 6;
	rayvars.ry = tan(degtorad(castAngle)) * (data->player->posx - rayvars.rx);
	rayvars.ry = data->player->posy - fabs(rayvars.ry);
	data->player->box_y = (int)rayvars.ry >> 6;
	if (rayvars.ry < 0)
		return (1e30);
	while (data->map[data->player->box_y][data->player->box_x] == 0)
	{
		rayvars.ry += rayvars.ya;
		rayvars.rx += rayvars.xa;
		if (rayvars.ry < 0)
			return (1e30);
		data->player->box_x = (int)(rayvars.rx - 1) >> 6;
		data->player->box_y = (int)rayvars.ry >> 6;
	}
	data->player->hor_hitx[i] = rayvars.rx;
	data->player->hor_hity[i] = rayvars.ry;
	distance = calculate_distance(data, rayvars.rx, rayvars.ry, castAngle);
	return (distance);
}

double	horizontalraycast_3(t_data *data, double castAngle, int i)
{
	t_rayvars	rayvars;
	double		distance;

	rayvars.xa = texwidth * -1;
	rayvars.ya = tan(degtorad(castAngle)) * texheight;
	rayvars.rx = ((int)data->player->posx >> 6) << 6;
	data->player->box_x = (int)(rayvars.rx - 1) >> 6;
	rayvars.ry = tan(degtorad(castAngle)) * (data->player->posx - rayvars.rx);
	rayvars.ry = data->player->posy + fabs(rayvars.ry);
	data->player->box_y = (int)rayvars.ry >> 6;
	if (rayvars.ry > data->map_data->h)
		return (1e30);
	while (data->map[data->player->box_y][data->player->box_x] == 0)
	{
		rayvars.ry += rayvars.ya;
		rayvars.rx += rayvars.xa;
		if (rayvars.ry > data->map_data->h)
			return (1e30);
		data->player->box_x = (int)(rayvars.rx - 1) >> 6;
		data->player->box_y = (int)rayvars.ry >> 6;
	}
	data->player->hor_hitx[i] = rayvars.rx;
	data->player->hor_hity[i] = rayvars.ry;
	distance = calculate_distance(data, rayvars.rx, rayvars.ry, castAngle);
	return (distance);
}

double	horizontalraycast_4(t_data *data, double castAngle, int i)
{
	t_rayvars	rayvars;
	double		distance;

	rayvars.xa = texwidth;
	rayvars.ya = tan(degtorad(castAngle)) * texheight * -1;
	rayvars.rx = (((int)data->player->posx >> 6) << 6) + texwidth;
	data->player->box_x = (int)rayvars.rx >> 6;
	rayvars.ry = tan(degtorad(castAngle)) * (rayvars.rx - data->player->posx);
	rayvars.ry = data->player->posy + fabs(rayvars.ry);
	data->player->box_y = (int)rayvars.ry >> 6;
	if (rayvars.ry > data->map_data->h)
		return (1e30);
	while (data->map[data->player->box_y][data->player->box_x] == 0)
	{
		rayvars.ry += rayvars.ya;
		if (rayvars.ry > data->map_data->h)
			return (1e30);
		rayvars.rx += rayvars.xa;
		data->player->box_x = (int)(rayvars.rx) >> 6;
		data->player->box_y = (int)rayvars.ry >> 6;
	}
	distance = calculate_distance(data, rayvars.rx, rayvars.ry, castAngle);
	data->player->hor_hitx[i] = rayvars.rx;
	data->player->hor_hity[i] = rayvars.ry;
	return (distance);
}
