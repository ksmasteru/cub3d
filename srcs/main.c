/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <hes-saqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:55 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/02/22 19:22:22 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_data2(t_data *data)
{
	init_player_data(data);
	data->player->distance = malloc(sizeof(int)
			* SCREEN_W);
	allocs_addback(&data->map_data->allocs, data->player->distance);
	data->player->side = (int *)malloc(sizeof(int) * SCREEN_W);
	allocs_addback(&data->map_data->allocs, data->player->side);
	data->player->hor_hitx = (int *)malloc(sizeof(int)
			* SCREEN_W);
	allocs_addback(&data->map_data->allocs, data->player->hor_hitx);
	data->player->hor_hity = (int *)malloc(sizeof(int)
			* SCREEN_W);
	allocs_addback(&data->map_data->allocs, data->player->hor_hity);
	data->player->ver_hitx = (int *)malloc(sizeof(int)
			* SCREEN_W);
	allocs_addback(&data->map_data->allocs, data->player->ver_hitx);
	data->player->ver_hity = (int *)malloc(sizeof(int)
			* SCREEN_W);
	allocs_addback(&data->map_data->allocs, data->player->ver_hity);
	data->mini_map->mlx_img = NULL;
	data->img->mlx_img = NULL;
	data->player->mouse_x = SCREEN_W / 2;
	return (1);
}

int	check_tex_dim(t_data *data, int *width, int *height)
{
	int	i;

	i = 1;
	while (i < TEXTURES_NUMBERS)
	{
		if ((width[i] != width[0]) || (height[i] != height[0]))
		{
			printf("Please choose similar texture dimensions\n");
			return (-1);
		}
		i++;
	}
	data->texheight = *height;
	data->texwidth = *width;
	return (0);
}

int	set_up_wall_xpms(t_data *data)
{
	int	width[4];
	int	height[4];

	data->xpm_imgs = (t_image *)malloc(sizeof(t_image) * TEXTURES_NUMBERS);
	data->xpm_imgs[0].mlx_img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map_data->north_texture, width, height);
	data->xpm_imgs[0].adrs = mlx_get_data_addr(data->xpm_imgs[0].mlx_img,
			&(data->xpm_imgs[0].bpp), &(data->xpm_imgs[0].size_line),
			&(data->xpm_imgs[0].endian));
	data->xpm_imgs[2].mlx_img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map_data->west_texture, width + 2, height + 2);
	data->xpm_imgs[2].adrs = mlx_get_data_addr(data->xpm_imgs[2].mlx_img,
			&(data->xpm_imgs[2].bpp), &(data->xpm_imgs[2].size_line),
			&(data->xpm_imgs[2].endian));
	data->xpm_imgs[3].mlx_img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map_data->east_texture, width + 3, height + 3);
	data->xpm_imgs[3].adrs = mlx_get_data_addr(data->xpm_imgs[3].mlx_img,
			&(data->xpm_imgs[3].bpp), &(data->xpm_imgs[3].size_line),
			&(data->xpm_imgs[3].endian));
	data->xpm_imgs[1].mlx_img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map_data->south_texture, width + 1, height + 1);
	data->xpm_imgs[1].adrs = mlx_get_data_addr(data->xpm_imgs[1].mlx_img,
			&(data->xpm_imgs[1].bpp), &(data->xpm_imgs[1].size_line),
			&(data->xpm_imgs[1].endian));
	return (check_tex_dim(data, width, height));
}

t_data	*init_full_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->map_data = (t_map_data *)malloc(sizeof(t_map_data));
	if (!data->map_data)
		return (NULL);
	init_t_map_data(data->map_data);
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (printf("Error : please enter correct number of arguments\n")
			, 1);
	data = init_full_data();
	if (!data)
		return (1);
	if (parse_cub_file(ac, av, data->map_data) < 0)
	{
		allocs_clean_up(data->map_data->allocs);
		free(data->map_data);
		free(data);
		return (1);
	}
	if (!init_data(data))
	{
		free(data);
		return (1);
	}
	render_walls(data);
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, pressed_key_event, data);
	mlx_loop(data->mlx_ptr);
}
