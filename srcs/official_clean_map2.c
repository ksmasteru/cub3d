/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   official_clean_map2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:43:28 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/03/01 14:43:30 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/mini_map.h"

void	check_start_close(char *iter)
{
	if (*iter != 0 && *iter != '1' && !isspace(*iter))
		hanlde_error(ERR_MAP_NOT_CLOSED);
}

void	process_map_line(char *buffer, t_map_data *data, size_t *size, int h)
{
	char	*iter;
	int		w;

	w = 0;
	iter = buffer;
	check_start_close(iter);
	while (*iter && *iter != '\n')
	{
		is_allawed(iter);
		check_position(iter, data, w, h);
		iter++;
		w++;
	}
	check_last_close(iter);
	assign_directions(w, h, data);
	resize(data, &data->map, *size);
	set_map_line(buffer, size, data);
}

void	read_map(int fd, t_map_data *data, size_t *size)
{
	char	*buffer;
	int		h;
	char	*trimmed;

	h = 1;
	trimmed = get_next_line(fd);
	buffer = ft_strim(trimmed);
	allocs_addback(&data->allocs, buffer);
	allocs_addback(&data->allocs, trimmed);
	while (buffer && *buffer != '\n')
	{
		h++;
		process_map_line(buffer, data, size, h);
		trimmed = get_next_line(fd);
		buffer = ft_strim(trimmed);
		allocs_addback(&data->allocs, buffer);
		allocs_addback(&data->allocs, trimmed);
	}
}

void	check_eomap(t_map_data *data, int fd)
{
	char	*buffer;

	buffer = get_next_line(fd);
	allocs_addback(&data->allocs, buffer);
	while (buffer)
	{
		if (*buffer != '\n')
			hanlde_error(ERR_INVALID_LINE);
		buffer = get_next_line(fd);
		allocs_addback(&data->allocs, buffer);
	}
}

int	is_map(char *buffer, t_map_data *data, int fd)
{
	char	*iter;
	size_t	size;

	size = 0;
	iter = buffer;
	if (*iter == '1')
	{
		while (*iter == '1')
			iter++;
		if ((*iter != '\n') && iter > buffer)
			hanlde_error(ERR_INVALID_MAP_START);
		resize(data, &data->map, size);
		set_map_line(buffer, &size, data);
		read_map(fd, data, &size);
		if (!data->player_x || !data->player_y || !data->player_dir)
			hanlde_error(ERR_MISSING_PLAYER);
		check_eomap(data, fd);
	}
	return (size);
}
