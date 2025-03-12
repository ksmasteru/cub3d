/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <hes-saqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:55 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/02/22 18:41:47 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

void	draw_walls_1(t_data *data, t_pixdata *pixdata, int stripex,
		double texpos)
{
	while (pixdata->y_min != pixdata->y_max)
	{
		pixdata->xpm_pixel = data->xpm_imgs[data->player->wall_type].adrs
			+ data->xpm_imgs[data->player->wall_type].size_line * pixdata->y_xpm
			+ pixdata->x_offset * (data->xpm_imgs[data->player->wall_type].bpp
				/ 8);
		pixdata->pixel = data->img->adrs + data->img->size_line * pixdata->y_min
			+ stripex * (data->img->bpp / 8);
		*(int *)pixdata->pixel = *(int *)pixdata->xpm_pixel;
		texpos += pixdata->step;
		pixdata->y_xpm = (int)texpos & (data->texheight - 1);
		pixdata->y_min++;
	}
}

void	drawceiling(t_data *data, int stripex, int y_min)
{
	int		i;
	char	*pixel;

	i = 0;
	while (i < y_min)
	{
		pixel = data->img->adrs + data->img->size_line * i + stripex
			* (data->img->bpp / 8);
		*(int *)pixel = (data->map_data->ceiling_color[0] << 16) | 
			(data->map_data->ceiling_color[1] << 8) | data->map_data->ceiling_color[2];
		i++;
	}
}

void	drawfloor(t_data *data, int stripex, int y_max)
{
	char	*pixel;

	while (y_max < SCREEN_H)
	{
		pixel = data->img->adrs + data->img->size_line * y_max + stripex
			* (data->img->bpp / 8);
		*(int *)pixel = (data->map_data->floor_color[0] << 16) | 
			(data->map_data->floor_color[1] << 8) | data->map_data->floor_color[2];
		y_max++;
	}
}

void	draw_wall_side(t_data *data, int stripex, t_pixdata *pixdata,
		double texpos)
{
	int	t;

	t = data->player->wall_type;
	while (pixdata->y_min != pixdata->y_max)
	{
		pixdata->xpm_pixel = data->xpm_imgs[t].adrs
			+ data->xpm_imgs[t].size_line * pixdata->y_xpm + pixdata->x_offset
			* (data->xpm_imgs[t].bpp / 8);
		pixdata->pixel = data->img->adrs + data->img->size_line * pixdata->y_min
			+ stripex * (data->img->bpp / 8);
		*(int *)pixdata->pixel = *(int *)pixdata->xpm_pixel;
		pixdata->y_xpm = (int)texpos & (data->texheight - 1);
		texpos += pixdata->step;
		pixdata->y_min++;
	}
}

void	set_new_img(t_data *data)
{
	data->img->mlx_img = mlx_new_image(data->mlx_ptr, SCREEN_W, SCREEN_H);
	data->img->adrs = mlx_get_data_addr(data->img->mlx_img, &(data->img->bpp),
			&(data->img->size_line), &(data->img->endian));
}
