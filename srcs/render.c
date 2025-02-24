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

/*not used.*/

/*for side == 0 x_side hit*/
void	put_wall_side(t_data *data, int stripex, double distance, int side)
{
	t_pixdata	pixdata;
	double		texpos;
	double		projection_d;

	projection_d = (SCREEN_W / 2) * tan(degtorad(30));
	pixdata.slice_height = ((double)texheight / distance) * (projection_d);
	pixdata.x_offset = (int)data->player->ver_hitx[stripex] % (texwidth - 1);
	pixdata.step = 1.0 * texwidth / pixdata.slice_height;
	pixdata.y_min = SCREEN_H / 2 - pixdata.slice_height / 2;
	if (pixdata.y_min < 0)
		pixdata.y_min = 0;
	pixdata.y_max = SCREEN_H / 2 + pixdata.slice_height / 2;
	if (pixdata.y_max >= SCREEN_H)
		pixdata.y_max = SCREEN_H - 1;
	texpos = (pixdata.y_min - SCREEN_H / 2 + pixdata.slice_height / 2)
		* pixdata.step;
	pixdata.y_xpm = (int)texpos & (texwidth - 1);
	drawceiling(data, stripex, pixdata.y_min);
	draw_wall_side(data, stripex, &pixdata, texpos);
	drawfloor(data, stripex, pixdata.y_max);
}

void	put_wall(t_data *data, int stripex, double distance, int side)
{
	t_pixdata	pixdata;
	double		texpos;
	double		projection_d;

	projection_d = (SCREEN_W / 2) * tan(degtorad(30));
	pixdata.y_xpm = 0;
	if (distance > sqrt(data->map_data->h * data->map_data->h + data->map_data->w * data->map_data->w))
		distance = fabs(data->map_data->w - data->player->posx);
	pixdata.slice_height = ((double)texheight / distance) * (projection_d);
	if (side == 0)
		return (put_wall_side(data, stripex, distance, side));
	pixdata.x_offset = (int)data->player->ver_hity[stripex] % (texheight - 1);
	pixdata.step = 1.0 * texheight / pixdata.slice_height;
	pixdata.y_min = SCREEN_H / 2 - pixdata.slice_height / 2;
	if (pixdata.y_min < 0)
		pixdata.y_min = 0;
	pixdata.y_max = SCREEN_H / 2 + pixdata.slice_height / 2;
	if (pixdata.y_max >= SCREEN_H)
		pixdata.y_max = SCREEN_H - 1;
	texpos = (pixdata.y_min - SCREEN_H / 2 + pixdata.slice_height / 2)
		* pixdata.step;
	pixdata.y_xpm = (int)texpos & (texheight - 1);
	drawceiling(data, stripex, pixdata.y_min);
	draw_walls_1(data, &pixdata, stripex, texpos);
	drawfloor(data, stripex, pixdata.y_max);
}

void	put_walls(t_data *data)
{
	int	i;

	i = 0;
	while (i < SCREEN_W)
	{
		put_wall(data, i, data->player->distance[i], data->player->side[i]);
		i++;
	}
}

int	render_walls(t_data *data)
{
	int		i;
	double	sep_angle;
	double	castAngle;

	i = -1;
	sep_angle = (double)FOW / SCREEN_W;
	castAngle = data->player->view_deg + (double)FOW / 2;
	data->player->beta_angle = (double)FOW / 2;
	set_new_img(data);
	while (++i < SCREEN_W)
	{
		data->player->distance[i] = raycast_1(data, castAngle,
				data->player->side + i, i);
		castAngle -= sep_angle;
		data->player->beta_angle -= sep_angle;
	}
	put_walls(data);
	if (data->old_img->mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->old_img->mlx_img);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->mlx_img, 0,
			0);
	show_player_data(data);
	put_mini_map(data);
	data->old_img->mlx_img = data->img->mlx_img;
	return (0);
}
