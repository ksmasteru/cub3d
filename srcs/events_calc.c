/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <hes-saqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:55 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/02/22 18:41:53 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	degtorad(double degrees)
{
	return ((degrees) * M_PI / 180.0);
}

double	radtodeg(double radians)
{
	return (radians * 180.0 / M_PI);
}

void	update_ray_dir2(t_ray *ray, double view_deg)
{
	if (view_deg == 0 || view_deg == 360 || view_deg == 180)
	{
		ray->dir_y = 0;
		ray->dir_x = 1;
		if (view_deg == 180)
			ray->dir_x = -1;
	}
	else if (view_deg == 270 || view_deg == 90)
	{
		ray->dir_x = 0;
		ray->dir_y = 1;
		if (view_deg == 90)
			ray->dir_y = -1;
	}
}

void	update_ray_dir(t_ray *ray, double view_deg)
{
	if (view_deg < 0)
		view_deg += 360;
	if (view_deg != 0 && view_deg != 90 && view_deg != 180 && view_deg != 360
		&& view_deg != 270)
	{
		if (view_deg > 0 && view_deg < 180)
			ray->dir_y = -1;
		else
			ray->dir_y = 1;
		if ((view_deg > 0 && view_deg < 90) || (view_deg > 270
				&& view_deg < 360))
			ray->dir_x = 1;
		else
			ray->dir_x = -1;
	}
	else
		update_ray_dir2(ray, view_deg);
}
