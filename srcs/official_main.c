/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   official_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:38:27 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/03/03 13:38:29 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_map_data	*initialize_and_check_file(int fd, char **av, t_map_data *data)
{
	init_t_map_data(data);
	check_file(av[1], &fd);
	close(fd);
	return (data);
}

int	validate_textures(t_map_data *data)
{
	if (!data->east_texture || !data->west_texture || !data->south_texture
		|| !data->north_texture)
	{
		printf("missing paths\n");
		return (0);
	}
	return (1);
}

int	validate_last_map_row(t_map_data *data)
{
	char	*iter;

	if (data->map_height > 0)
	{
		iter = data->map[data->map_height - 1];
		while (*iter)
		{
			if (*iter != '1')
			{
				printf("error last 11111111\n");
				return (0);
			}
			iter++;
		}
	}
	return (1);
}

t_map_data	*parse_cub_file(int ac, char **av)
{
	t_map_data	*data;
	int			fd;
	char		*buffer;

	(void) ac;
	data = (t_map_data *)malloc(sizeof(t_map_data));
	fd = open_file(av[1], 0);
	initialize_and_check_file(fd, av, data);
	buffer = get_next_line(fd);
	if (buffer == NULL)
	{
		hanlde_error(ERR_INVALID_LINE);
		return (NULL);
	}
	allocs_addback(&data->allocs, buffer);
	start_parsing(fd, buffer, data);
	if (!validate_last_map_row(data) || !validate_textures(data))
		return (NULL);
	if (data->f_count != 2 || data->c_count != 2)
		return (printf("Error : invalid color type\n"), NULL);
	return (data);
}
