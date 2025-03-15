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

void	free_2d_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str[i]);
	free(str);
}

void	free_t_map_data(t_map_data *data)
{
	if (data->allocs != NULL)
		allocs_clean_up(data->allocs);
}

void	set_2d_int_map_helper(t_data	*data, int i, int j)
{
	while (i < data->map_data->map_height)
	{
		j = 0;
		while (j < data->map_data->map_width)
		{
			if (data->map_data->map[i][j] == '0'
				|| data->map_data->map[i][j] == '1')
				data->map[i][j] = data->map_data->map[i][j] - 48;
			else if (data->map_data->map[i][j] == '\0')
			{
				while (j < data->map_data->map_width)
					data->map[i][j++] = 1;
				continue ;
			}
			else
			{
				data->map[i][j] = 0;
				data->player->posy = i * TEXHEIGHT + TEXHEIGHT / 2;
				data->player->posx = j * TEXWDITH + TEXWDITH / 2;
			}
			j++;
		}
		i++;
	}
}

void	set_2d_int_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->map = (int **)malloc(sizeof(int *) * data->map_data->map_height);
	while (i < data->map_data->map_height)
		data->map[i++] = (int *)malloc(sizeof(int) * data->map_data->map_width);
	i = 0;
	set_2d_int_map_helper(data, i, j);
}
