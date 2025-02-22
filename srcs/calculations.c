/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <hes-saqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:55 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/02/22 18:41:25 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#define M_PI 3.14159265358979323846264338327950288

extern int	map[w][h];

double	calculate_distance(t_data *data, double cx, double cy, double castAngle)
{
	double	distance;

	distance = fabs((data->player->posy - cy) / sin(degtorad(castAngle)));
	return (distance);
}

double	verticalraycast(t_data *data, double castangle, int i)
{
	if (castangle == 0 || castangle == 180.0 || castangle == 360.0
		|| castangle == 90.0 || castangle == 270.0)
	{
		return (verticalraycast(data, castangle + 60.0 / SCREEN_W, i));
	}
	if (castangle > 0 && castangle < 90)
		return (vertical_casting_1(data, castangle, i));
	else if (castangle > 90 && castangle < 180)
		return (vertical_casting_2(data, castangle, i));
	else if (castangle > 180 && castangle < 270)
		return (vertical_casting_3(data, castangle, i));
	else
		return (vertical_casting_4(data, castangle, i));
}

double	horizontalraycast(t_data *data, double castAngle, int i)
{
	if (castAngle > 0 && castAngle < 90)
		return (horizontalraycast_1(data, castAngle, i));
	else if (castAngle > 90 && castAngle < 180)
		return (horizontalraycast_2(data, castAngle, i));
	else if (castAngle > 180 && castAngle < 270)
		return (horizontalraycast_3(data, castAngle, i));
	else
		return (horizontalraycast_4(data, castAngle, i));
}
