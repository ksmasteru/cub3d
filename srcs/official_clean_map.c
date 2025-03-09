/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   official_clean_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:51:41 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/03/01 11:07:14 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	resize(t_map_data *data, char ***array, int size)
{
	char	**vector;
	int		i;

	i = 0;
	vector = (char **)malloc(sizeof(char *) * (size + 1));
	if (!vector)
		hanlde_error(ERR_MEMORY_ALLOCATION);
	while (i < size && size > 0)
	{
		if ((*array)[i] != NULL)
			vector[i] = (*array)[i];
		else
			vector[i] = NULL;
		i++;
	}
	*array = vector;
	allocs_addback(&data->allocs, vector);
}

void	set_map_line(char *buffer, size_t *size, t_map_data *data)
{
	char	*new_line;

	new_line = strchr(buffer, '\n');
	on_off(new_line);
	(data)->map[*size] = strdup(buffer);
	allocs_addback(&data->allocs, (data)->map[*size]);
	on_off(new_line);
	*size += 1;
}

int	is_allawed(char *iter)
{
	if (*iter != '1' && *iter != '0' && *iter != 'N' && *iter != 'W'
		&& *iter != 'E' && *iter != 'S' && *iter != ' ')
		hanlde_error(ERR_INVALID_MAP_CHAR);
	return (0);
}

void	check_position(char *iter, t_map_data *data, int w, int h)
{
	if ((*iter == 'N' || *iter == 'W' || *iter == 'E' || *iter == 'S'))
	{
		if (data->player_dir == '\0')
		{
			data->player_x = w;
			data->player_y = h;
			data->player_dir = *iter;
		}
		else
			hanlde_error(ERR_MULTIPLE_PLAYERS);
	}
}

void	assign_directions(int w, int h, t_map_data *data)
{
	if (w > data->map_width)
		data->map_width = w;
	if (h > data->map_height)
		data->map_height = h;
}
