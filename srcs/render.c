/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <hes-saqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:55 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/02/22 18:42:26 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

void	draw_planes(t_data	*data, int stripex, t_pixdata pixdata)
{
	drawceiling(data, stripex, pixdata.y_min);
	draw_walls_1(data, &pixdata, stripex, pixdata.texpos);
	drawfloor(data, stripex, pixdata.y_max);
}

void	put_wall_side(t_data *data, int stripex, double distance, int side)
{
	t_pixdata	pixdata;
	double		texpos;
	double		projection_d;

	projection_d = (SCREEN_W / 2) * tan(degtorad(30));
	pixdata.slice_height = ((double)data->texheight / distance)
		* (projection_d);
	pixdata.x_offset = (int)data->player->ver_hitx[stripex]
		% (data->texwidth - 1);
	pixdata.step = 1.0 * data->texwidth / pixdata.slice_height;
	pixdata.y_min = SCREEN_H / 2 - pixdata.slice_height / 2;
	if (pixdata.y_min < 0)
		pixdata.y_min = 0;
	pixdata.y_max = SCREEN_H / 2 + pixdata.slice_height / 2;
	if (pixdata.y_max >= SCREEN_H)
		pixdata.y_max = SCREEN_H - 1;
	texpos = (pixdata.y_min - SCREEN_H / 2 + pixdata.slice_height / 2)
		* pixdata.step;
	pixdata.y_xpm = (int)texpos & (data->texwidth - 1);
	drawceiling(data, stripex, pixdata.y_min);
	draw_wall_side(data, stripex, &pixdata, texpos);
	drawfloor(data, stripex, pixdata.y_max);
}

void	put_wall(t_data *data, int stripex, double distance, int side)
{
	t_pixdata	pixdata;

	set_wall_type(data, side);
	pixdata.projection_d = (SCREEN_W / 2) * tan(degtorad(30));
	pixdata.y_xpm = 0;
	if (distance > sqrt(data->map_data->h * data->map_data->h
			+ data->map_data->w * data->map_data->w))
		distance = fabs(data->map_data->w - data->player->posx);
	pixdata.slice_height = ((double)data->texheight / distance)
		* (pixdata.projection_d);
	if (side == 0)
		return (put_wall_side(data, stripex, distance, side));
	pixdata.x_offset = (int)data->player->ver_hity[stripex]
		% (data->texheight - 1);
	pixdata.step = 1.0 * data->texheight / pixdata.slice_height;
	pixdata.y_min = SCREEN_H / 2 - pixdata.slice_height / 2;
	if (pixdata.y_min < 0)
		pixdata.y_min = 0;
	pixdata.y_max = SCREEN_H / 2 + pixdata.slice_height / 2;
	if (pixdata.y_max >= SCREEN_H)
		pixdata.y_max = SCREEN_H - 1;
	pixdata.texpos = (pixdata.y_min - SCREEN_H / 2 + pixdata.slice_height / 2)
		* pixdata.step;
	pixdata.y_xpm = (int)pixdata.texpos & (data->texheight - 1);
	draw_planes(data, stripex, pixdata);
}

void	put_walls(t_data *data)
{
	int		i;
	double	castangle;
	double	sep_angle;

	sep_angle = (double)FOW / SCREEN_W;
	castangle = data->player->view_deg + (double)FOW / 2;
	i = 0;
	while (i < SCREEN_W)
	{
		update_ray_dir(&(data->ray), castangle);
		put_wall(data, i, data->player->distance[i], data->player->side[i]);
		castangle -= sep_angle;
		i++;
	}
}

int	render_walls(t_data *data)
{
	int		i;
	double	sep_angle;
	double	castangle;

	i = -1;
	sep_angle = (double)FOW / SCREEN_W;
	castangle = data->player->view_deg + (double)FOW / 2;
	data->player->beta_angle = (double)FOW / 2;
	set_new_img(data);
	while (++i < SCREEN_W)
	{
		data->player->distance[i] = raycast_1(data, castangle,
				data->player->side + i, i);
		castangle -= sep_angle;
		data->player->beta_angle -= sep_angle;
	}
	put_walls(data);
	if (data->old_img->mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->old_img->mlx_img);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->mlx_img, 0,
		0);
	put_mini_map(data);
	data->old_img->mlx_img = data->img->mlx_img;
	return (0);
}
