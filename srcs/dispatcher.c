/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:55 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/02/22 18:38:57 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#define M_PI 3.14159265358979323846264338327950288

extern int	map[w][h];

void	reset_verhit(t_data *data, int i)
{
	data->player->ver_hitx[i] = data->player->hor_hitx[i];
	data->player->ver_hity[i] = data->player->hor_hity[i];
	data->player->wall_type = map[(int)data->player->hity
		/ texheight][(int)data->player->hitx / texwidth];
}

double	raycast_2(t_data *data, double castangle, int *side, int i)
{
	double	horizontalray;
	double	verticalray;

	if (castangle > 0 && castangle < 90)
	{
		horizontalray = horizontalraycast_1(data, castangle, i);
		verticalray = vertical_casting_1(data, castangle, i);
	}
	else if (castangle > 90 && castangle < 180)
	{
		horizontalray = horizontalraycast_2(data, castangle, i);
		verticalray = vertical_casting_2(data, castangle, i);
	}
	if (verticalray < horizontalray)
	{
		*side = 0;
		return (verticalray);
	}
	*side = 1;
	reset_verhit(data, i);
	return (horizontalray);
}

double	raycast_3(t_data *data, double castangle, int *side, int i)
{
	double	horizontalray;
	double	verticalray;
	double	smallest_distance;

	if (castangle > 180 && castangle < 270)
	{
		horizontalray = horizontalraycast_3(data, castangle, i);
		verticalray = vertical_casting_3(data, castangle, i);
	}
	else if (castangle > 270 && castangle < 360)
	{
		horizontalray = horizontalraycast_4(data, castangle, i);
		verticalray = vertical_casting_4(data, castangle, i);
	}
	if (verticalray < horizontalray)
	{
		*side = 0;
		return (verticalray);
	}
	*side = 1;
	reset_verhit(data, i);
	return (horizontalray);
}

double	raycast_1(t_data *data, double castangle, int *side, int i)
{
	double	smallest_distance;

	if (castangle < 0)
		castangle += 360.0;
	else if (castangle > 360)
	{
		castangle -= 360.0;
		return (raycast_1(data, castangle, side, i));
	}
	if (castangle == 0 || castangle == 180.0 || castangle == 360.0
		|| castangle == 90.0 || castangle == 270.0)
	{
		return (raycast_1(data, castangle + 60.0 / SCREEN_W, side, i));
	}
	if (castangle > 0 && castangle < 180)
		smallest_distance = raycast_2(data, castangle, side, i);
	else if (castangle > 180 && castangle < 360)
		smallest_distance = raycast_3(data, castangle, side, i);
	return ((smallest_distance)*cos(degtorad(data->player->beta_angle)));
}
