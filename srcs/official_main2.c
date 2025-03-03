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

int is_repitor(t_map_data *data)
{
	if (!strcmp(data->south_texture, data->west_texture)
		|| !strcmp(data->south_texture, data->east_texture)
		|| !strcmp(data->south_texture, data->north_texture)
		|| !strcmp(data->north_texture, data->west_texture)
		|| !strcmp(data->north_texture, data->east_texture)
		|| !strcmp(data->east_texture, data->west_texture))
			return (1);
	return (0);
}

void print_error_message(error_code code)
{
    const char *error_messages[] = {
        "ERR_NONE",
        "ERR_FILE_NOT_FOUND",
        "ERR_FILE_EXTENSION",
        "ERR_EMPTY_FILE",
        "ERR_FILE_PERMISSION",
        "ERR_MISSING_TEXTURE",
        "ERR_DUPLICATE_TEXTURE",
        "ERR_INVALID_TEXTURE_PATH",
        "ERR_TEXTURE_FILE_MISSING",
        "ERR_MISSING_COLOR",
        "ERR_DUPLICATE_COLOR",
        "ERR_INVALID_COLOR_FORMAT",
        "ERR_COLOR_OUT_OF_RANGE",
        "ERR_MAP_NOT_CLOSED",
        "ERR_INVALID_MAP_CHAR",
        "ERR_MULTIPLE_PLAYERS",
        "ERR_MISSING_PLAYER",
        "ERR_INVALID_MAP_START",
        "ERR_INVALID_LINE",
        "ERR_MEMORY_ALLOCATION",
        "ERR_NOT_TEXTURE",
        "ERR_NOT_IMG",
        "ERR_NOT_MAP"
    };    
    if (code >= 0 && code < 23)
        printf("%s\n", error_messages[code]);
    else
        printf("Unknown error code\n");
}

void	assign_struct(t_map_data *data)
{
	data->east_texture = NULL;
	data->west_texture = NULL;
	data->south_texture = NULL;
	data->north_texture = NULL;
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
}

void	start_parsing(int fd, char *buffer, t_map_data *data)
{
	size_t		size = 0;
	size_t		buffer_size;
	error_code	err_texture;
	error_code	err_img;
	error_code	err_map;

	while (buffer)
	{
		if (*buffer != '\n')
		{
			trim_buffer(&buffer);
			err_texture = is_texture(buffer, data);
			err_img = is_color(buffer, data);
			size = is_map(buffer, data, fd);
			if ((err_texture != ERR_NONE && err_texture != ERR_NOT_TEXTURE)
				|| (err_img != ERR_NONE && err_img != ERR_NOT_IMG))
					exit(printf("error o safi"));
			else if ((err_texture == ERR_NOT_TEXTURE) && (err_img == ERR_NOT_IMG) && size == 0)
				exit(printf("imposter line [%s]", buffer));
			else if (size > 0)
				break;
		}
		buffer = get_next_line(fd);
        allocs_addback(&data->allocs, buffer);
	}
}

void	init_t_map_data(t_map_data	*data)
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
}
