/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <hes-saqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:55 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/02/22 18:42:16 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_map.h"

t_map	fill_map_data(t_data *data)
{
	t_map	map;

	map.mini_map_w = SCREEN_W / 4;
	map.mini_map_h = SCREEN_H / 4;
	while (map.mini_map_w % data->map_data->map_width != 0)
		map.mini_map_w++;
	while (map.mini_map_h % data->map_data->map_height != 0)
		map.mini_map_h++;
	map.w_pixels = map.mini_map_w / data->map_data->map_width;
	map.h_pixels = map.mini_map_h / data->map_data->map_height;
	map.p_x = 0;
	map.p_y = 0;
	if (data->mini_map->mlx_img != NULL)
		mlx_destroy_image(data->mlx_ptr, data->mini_map->mlx_img);
	data->mini_map->mlx_img = mlx_new_image(data->mlx_ptr, map.mini_map_w,
			map.mini_map_h);
	data->mini_map->adrs = mlx_get_data_addr(data->mini_map->mlx_img,
												&(data->mini_map->bpp),
												&(data->mini_map->size_line),
												&data->mini_map->endian);
	return (map);
}

int	fill_square_pixels(t_map *map, t_image *img, int color)
{
	int		it;
	int		it1;
	char	*pixel;
	int		p_y;
	int		p_x;

	p_y = map->p_y;
	p_x = map->p_x;
	it = 1;
	it1 = 1;
	while (it++ < map->w_pixels + 1)
	{
		p_y = map->p_y;
		pixel = img->adrs + img->size_line * p_y + p_x * (img->bpp) / 8;
		*(int *)pixel = color;
		it1 = 1;
		while (it1++ < map->h_pixels + 1)
		{
			pixel = img->adrs + img->size_line * p_y++ + p_x * img->bpp / 8;
			*(int *)pixel = color;
		}
		p_x++;
	}
}

int	put_ray(double view_deg, t_data *data, t_map *map)
{
	int		x;
	int		y;
	int		player_x;
	int		player_y;
	int		wall_x;
	int		wall_y;
	double	slope;

	x = 0;
	y = 0;
	player_x = (int)data->player->posx / texwidth * map->w_pixels;
	player_y = (int)data->player->posy / texwidth * map->h_pixels;
	slope = tan(degtorad(view_deg));
	slope *= -1;
	for (x = player_x; x < map->mini_map_w; x++)
	{
		y = slope * x - slope * player_x + player_y;
		if (y < 0)
			continue ;
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x0000ff);
	}
}

int	put_rays(t_data *data, t_map *map)
{
	double	view_deg;
	double	max_deg;
	double	low_deg;
	int		i;

	i = 0;
	view_deg = data->player->view_deg;
	max_deg = view_deg + 30;
	if (max_deg > 360)
		max_deg = (int)max_deg % 360;
	low_deg = view_deg - 30;
	put_ray(view_deg, data, map);
	put_ray(max_deg, data, map);
	put_ray(low_deg, data, map);
}

int	put_mini_map(t_data *data)
{
	int		i;
	int		j;
	t_map	mini_map;

	i = 0;
	j = 0;
	mini_map = fill_map_data(data);
	while (i < data->map_data->map_width)
	{
		j = 0;
		mini_map.p_y = i * mini_map.h_pixels;
		while (j < data->map_data->map_height)
		{
			mini_map.p_x = j * mini_map.w_pixels;
			if (data->map[i][j] != 0)
				fill_square_pixels(&mini_map, data->mini_map, 0x3333FF);
			else
				fill_square_pixels(&mini_map, data->mini_map, 0x99CCFF);
			j++;
		}
		i++;
	}
	fill_player_position(&mini_map, data->mini_map, data, 0xff0000);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->mini_map->mlx_img, 0, 0);
	put_rays(data, &mini_map);
}
