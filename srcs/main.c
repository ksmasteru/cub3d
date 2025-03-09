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
	data->player->distance = (double *)malloc(sizeof(double)
			* data->map_data->w);
	if (!data->player->distance)
		return (-1);
	data->player->side = (int *)malloc(sizeof(int) * data->map_data->w);
	if (!data->player->side)
		return (-1);
	data->player->hor_hitx = (double *)malloc(sizeof(double)
			* data->map_data->w);
	data->player->hor_hity = (double *)malloc(sizeof(double)
			* data->map_data->w);
	data->player->ver_hitx = (double *)malloc(sizeof(double)
			* data->map_data->w);
	data->player->ver_hity = (double *)malloc(sizeof(double)
			* data->map_data->w);
	data->mini_map->mlx_img = NULL;
	data->img->mlx_img = NULL;
	data->player->mouse_x = SCREEN_W / 2;
	return (1);
}

int	key_pressed(int keycode, t_data *data)
{
	printf("keycode %d was held pressed\n", keycode);
	if (keycode == XK_Up || keycode == XK_Down)
	{
		printf("keypress up/down\n");
		return (update_player_pos(data, keycode, 0.5));
	}
	if (keycode == XK_Right || keycode == XK_Left)
	{
		printf("keypress r/l\n");
		return (rotate_player_dir(data, keycode, 0.5));
	}
	return (0);
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

int	main(int ac, char **av)
{
	t_data	*data;
	
	if (ac != 2)
		return(printf("Error : please enter correct number of arguments\n"), 1);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->map_data = parse_cub_file(ac, av);
	if (!data->map_data)
		free_t_map_data(data->map_data);
	if (!init_data(data))
	{
		free_t_map_data(data->map_data);
		return (1);
	}
	render_walls(data);
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, pressed_key_event, data);
	mlx_loop(data->mlx_ptr);
}
