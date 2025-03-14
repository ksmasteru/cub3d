/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   official_main2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 02:01:25 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/03/03 02:01:26 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	start_parsing(int fd, char *buffer, t_map_data *data)
{
	t_parse	parse;

	parse.size = 0;
	while (buffer)
	{
		if (*buffer != '\n')
		{
			trim_buffer(&buffer);
			parse.err_texture = is_texture(buffer, data);
			parse.err_img = is_color(buffer, data);
			parse.size = is_map(buffer, data, fd);
			if ((parse.err_texture != ERR_NONE && parse.err_texture
					!= ERR_NOT_TEXTURE)
				|| (parse.err_img != ERR_NONE && parse.err_img != ERR_NOT_IMG))
				exit(printf("error"));
			else if ((parse.err_texture == ERR_NOT_TEXTURE)
				&& (parse.err_img == ERR_NOT_IMG) && parse.size == 0)
				exit(printf("imposter line [%s]", buffer));
			else if (parse.size > 0)
				break ;
		}
		buffer = get_next_line(fd);
		allocs_addback(&data->allocs, buffer);
	}
}

void	init_t_map_data(t_map_data *data)
{
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->west_texture = NULL;
	data->east_texture = NULL;
	data->map = NULL;
	data->allocs = NULL;
	data->ceiling_color[0] = -1;
	data->ceiling_color[1] = -1;
	data->ceiling_color[2] = -1;
	data->floor_color[0] = -1;
	data->floor_color[1] = -1;
	data->floor_color[2] = -1;
	data->player_dir = '\0';
	data->map_height = 0;
	data->map_width = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->f_count = 0;
	data->c_count = 0;
}
