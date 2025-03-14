/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <hes-saqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:55 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/02/22 18:41:32 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

double	vertical_casting_1(t_data *data, double castangle, int i)
{
	t_rayvars	ray_data;

	ray_data.xa = data->texwidth / tan(degtorad(castangle));
	ray_data.ya = data->texheight * -1;
	ray_data.ry = ((int)data->player->posy / data->texheight) * data->texheight;
	data->player->box_y = (int)(ray_data.ry - 1) / data->texheight;
	ray_data.rx = ((data->player->posy - ray_data.ry)
			/ tan(degtorad(castangle)));
	ray_data.rx = data->player->posx + fabs(ray_data.rx);
	data->player->box_x = (int)ray_data.rx / data->texwidth;
	if (ray_data.rx > data->map_data->w)
		return (1e30);
	while (data->map[data->player->box_y][data->player->box_x] == 0)
	{
		ray_data.ry += ray_data.ya;
		ray_data.rx += ray_data.xa;
		if (ray_data.rx > data->map_data->w)
			return (1e30);
		data->player->box_y = (int)(ray_data.ry - 1) / data->texheight;
		data->player->box_x = (int)ray_data.rx / data->texwidth;
	}
	data->player->ver_hitx[i] = ray_data.rx;
	data->player->ver_hity[i] = ray_data.ry;
	return (calculate_distance(data, ray_data.ry, castangle));
}

void	set_wall_type(t_data	*data, int side)
{
	if (side == 0 && data->ray.dir_y < 0)
		data->player->wall_type = 0;
	if (side == 0 && data->ray.dir_y >= 0)
		data->player->wall_type = 1;
	if (side == 1 && data->ray.dir_x < 0)
		data->player->wall_type = 2;
	if (side == 1 && data->ray.dir_x >= 0)
		data->player->wall_type = 3;
	else
		data->player->wall_type = 0;
}

double	vertical_casting_2(t_data *data, double castangle, int i)
{
	t_rayvars	ray_data;

	ray_data.xa = data->texwidth / tan(degtorad(castangle));
	ray_data.ya = data->texheight * -1;
	ray_data.ry = ((int)data->player->posy / data->texheight) * data->texheight;
	data->player->box_y = (int)(ray_data.ry - 1) / data->texheight;
	ray_data.rx = ((data->player->posy - ray_data.ry)
			/ tan(degtorad(castangle)));
	ray_data.rx = data->player->posx - fabs(ray_data.rx);
	data->player->box_x = (int)ray_data.rx / data->texwidth;
	if (ray_data.rx < 0)
		return (1e30);
	while (data->map[data->player->box_y][data->player->box_x] == 0)
	{
		ray_data.ry += ray_data.ya;
		ray_data.rx += ray_data.xa;
		if (ray_data.rx < 0)
			return (1e30);
		data->player->box_y = (int)(ray_data.ry - 1) / data->texheight;
		data->player->box_x = (int)ray_data.rx / data->texwidth;
	}
	data->player->ver_hitx[i] = ray_data.rx;
	data->player->ver_hity[i] = ray_data.ry;
	set_wall_type(data, castangle);
	return (calculate_distance(data, ray_data.ry, castangle));
}

double	vertical_casting_4(t_data *data, double castangle, int i)
{
	t_rayvars	raydata;

	raydata.xa = data->texwidth / tan(degtorad(castangle)) * -1;
	raydata.ya = data->texheight;
	raydata.ry = (((int)data->player->posy / data->texheight)
			* data->texwidth) + data->texheight;
	data->player->box_y = (int)raydata.ry / data->texheight;
	raydata.rx = (raydata.ry - data->player->posy) / tan(degtorad(castangle));
	raydata.rx = data->player->posx + fabs(raydata.rx);
	data->player->box_x = (int)raydata.rx / data->texheight;
	if (raydata.rx < 0)
		return (1e30);
	while (data->map[data->player->box_y][data->player->box_x] == 0)
	{
		raydata.ry += raydata.ya;
		raydata.rx += raydata.xa;
		if (raydata.rx > data->map_data->w)
			return (1e30);
		data->player->box_y = (int)raydata.ry / data->texheight;
		data->player->box_x = (int)raydata.rx / data->texwidth;
	}
	data->player->ver_hitx[i] = raydata.rx;
	data->player->ver_hity[i] = raydata.ry;
	set_wall_type(data, castangle);
	return (calculate_distance(data, raydata.ry, castangle));
}

double	vertical_casting_3(t_data *data, double castangle, int i)
{
	t_rayvars	ray_data;

	ray_data.xa = data->texwidth / tan(degtorad(castangle)) * -1;
	ray_data.ya = data->texheight;
	ray_data.ry = (((int)data->player->posy / data->texheight)
			* data->texheight) + data->texheight;
	data->player->box_y = (int)ray_data.ry / data->texheight;
	ray_data.rx = (ray_data.ry - data->player->posy) / tan(degtorad(castangle));
	ray_data.rx = data->player->posx - fabs(ray_data.rx);
	data->player->box_x = (int)ray_data.rx / data->texwidth;
	if (ray_data.rx < 0)
		return (1e30);
	while (data->map[data->player->box_y][data->player->box_x] == 0)
	{
		ray_data.ry += ray_data.ya;
		ray_data.rx += ray_data.xa;
		if (ray_data.rx < 0)
			return (1e30);
		data->player->box_y = (int)ray_data.ry / data->texheight;
		data->player->box_x = (int)ray_data.rx / data->texwidth;
	}
	data->player->ver_hitx[i] = ray_data.rx;
	data->player->ver_hity[i] = ray_data.ry;
	return (calculate_distance(data, ray_data.ry, castangle));
}
