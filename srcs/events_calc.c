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

extern double	angle;

double	degtorad(double degrees)
{
	return ((degrees)*M_PI / 180.0);
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

void	show_player_data(t_data *data)
{
	char	*p_posx;
	char	*p_posy;
	char	*p_view;
	char	*posx;
	char	*posy;
	char	*view_deg;

	posx = ft_itoa((int)data->player->posx);
	posy = ft_itoa((int)data->player->posy);
	view_deg = ft_itoa((int)data->player->view_deg);
	p_posx = ft_strjoin("posx: ", posx);
	p_posy = ft_strjoin("posy: ", posy);
	p_view = ft_strjoin("view_deg: ", view_deg);
	mlx_string_put(data->mlx_ptr, data->win_ptr, SCREEN_W / 2, SCREEN_H / 10,
			0xffffff, p_posx);
	mlx_string_put(data->mlx_ptr, data->win_ptr, SCREEN_W / 2, SCREEN_H / 10
			+ 20, 0xffffff, p_posy);
	mlx_string_put(data->mlx_ptr, data->win_ptr, SCREEN_W / 2, SCREEN_H / 10
			+ 40, 0xffffff, p_view);
	free(p_posx);
	free(p_posy);
	free(p_view);
	free(posx);
	free(posy);
	free(view_deg);
}
