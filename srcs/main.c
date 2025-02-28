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

void	free_2d_str(char	**str)
{
	int i;

	i = 0;
	while(str[i])
		free(str[i++]);
	free(str[i]);
	free(str);
}

void	free_t_map_data(t_map_data	 *data)
{
	if (data->north_texture)
		free(data->north_texture);
	if (data->south_texture)
		free(data->south_texture);
	if (data->west_texture)
		free(data->west_texture);
	if (data->east_texture)
		free(data->east_texture);
	/*if (data->map)
		free_2d_str(data->map);*/
	if (data->allocs != NULL)
	 	allocs_clean_up(&data->allocs);
}

int	init_data(int ac, char **av, t_data *data)
{
	data->map_data = parse_cub_file(ac, av);
	if (!data->map_data)
		free_t_map_data(data->map_data);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (-1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCREEN_W, SCREEN_H, "CUB3D");
	if (!data->win_ptr)
		return (-1);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (-1);
	data->img = malloc(sizeof(t_image));
	if (!data->img)
		return (-1);
	data->old_img = malloc(sizeof(t_image));
	if (!data->old_img)
		return (-1);
	data->old_img->mlx_img = NULL;
	data->player->beta_angle = (double)FOW / 2;
	data->mini_map = malloc(sizeof(t_image));
	if (!data->mini_map)
		return (-1);
	return (init_data2(data));
}

void	set_2d_int_map(t_data	*data)
{
	int i;
	int j;

	i = 0;
	data->map = (int**)malloc(sizeof(int *) * data->map_data->map_height);
	while (i < data->map_data->map_height)
		data->map[i++] = (int *)malloc(sizeof(int) * data->map_data->map_width);
	i = 0;
	while (i < data->map_data->map_height)
	{
		j = 0;
		while (j < data->map_data->map_width)
		{
			if (data->map_data->map[i][j] >= '0' && data->map_data->map[i][j] <= '9')
				data->map[i][j] = data->map_data->map[i][j] - 48;
			else if (data->map_data->map[i][j] == '\0')
			{
				while (j < data->map_data->map_width)
					data->map[i][j++] = 1;
				continue;
			}
			else
			{
				data->map[i][j] = 0;
				data->player->posy = i * texheight + texheight / 2;
				data->player->posx = j * texwidth + texwidth / 2;
				printf("\nplayer x %d player y %d\n", j, i);
			}
			printf("%d", data->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	init_player_data(t_data *data)
{
	if (data->map_data->player_dir == 'N')
		data->player->view_deg = 91;
	else if (data->map_data->player_dir == 'E')
		data->player->view_deg = 181;
	else if (data->map_data->player_dir == 'S')
		data->player->view_deg = 271;
	else
		data->player->view_deg = 1;
	data->map_data->w = texwidth * data->map_data->map_width;
	data->map_data->h = texheight * data->map_data->map_height;
	set_2d_int_map(data);
}

int	init_data2(t_data *data)
{
	init_player_data(data);
	data->player->distance = (double *)malloc(sizeof(double) * data->map_data->w);
	if (!data->player->distance)
		return (-1);
	data->player->side = (int *)malloc(sizeof(int) * data->map_data->w);
	if (!data->player->side)
		return (-1);
	data->player->hor_hitx = (double *)malloc(sizeof(double) * data->map_data->w);
	data->player->hor_hity = (double *)malloc(sizeof(double) * data->map_data->w);
	data->player->ver_hitx = (double *)malloc(sizeof(double) * data->map_data->w);
	data->player->ver_hity = (double *)malloc(sizeof(double) * data->map_data->w);
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

int	set_up_wall_xpms(t_data *data)
{
	int	width;
	int	height;

	data->xpm_imgs = (t_image *)malloc(sizeof(t_image) * TEXTURES_NUMBERS);
	if (!data->xpm_imgs)
		return (-1);
	data->xpm_imgs[0].mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, 
		data->map_data->north_texture, &width, &height);
	data->xpm_imgs[0].adrs = mlx_get_data_addr(data->xpm_imgs[0].mlx_img,
		&(data->xpm_imgs[0].bpp), &(data->xpm_imgs[0].size_line),
			&(data->xpm_imgs[0].endian));
	data->xpm_imgs[2].mlx_img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->map_data->west_texture, &width, &height);
	data->xpm_imgs[2].adrs = mlx_get_data_addr(data->xpm_imgs[2].mlx_img,
		&(data->xpm_imgs[2].bpp), &(data->xpm_imgs[2].size_line),
			&(data->xpm_imgs[2].endian));
	data->xpm_imgs[3].mlx_img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->map_data->east_texture, &width, &height);
	data->xpm_imgs[3].adrs = mlx_get_data_addr(data->xpm_imgs[3].mlx_img,
		&(data->xpm_imgs[3].bpp), &(data->xpm_imgs[3].size_line),
			&(data->xpm_imgs[3].endian));
	data->xpm_imgs[1].mlx_img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->map_data->south_texture, &width, &height);
	data->xpm_imgs[1].adrs = mlx_get_data_addr(data->xpm_imgs[1].mlx_img,
		&(data->xpm_imgs[1].bpp), &(data->xpm_imgs[1].size_line),
			&(data->xpm_imgs[1].endian));
	return (1);
}

int	main(int ac, char **av)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (!init_data(ac, av, data))
	{
		free_t_map_data(data->map_data);
		return (1);
	}
	if (!set_up_wall_xpms(data))
	{
		free_t_map_data(data->map_data);
		return (1);
	}
	render_walls(data);
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, pressed_key_event, data);
	mlx_loop(data->mlx_ptr);
}