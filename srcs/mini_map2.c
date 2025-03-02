/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <hes-saqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:55 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/02/22 18:42:21 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_map.h"
#include "../includes/parsing.h"

void	fill_player_position(t_map *mini_map, t_image *img, t_data *data,
		int color)
{
	mini_map->p_x = (int)data->player->posx / data->texwidth
		* mini_map->w_pixels;
	mini_map->p_y = (int)data->player->posy / data->texheight
		* mini_map->h_pixels;
	fill_square_pixels(mini_map, img, color);
}

void	check_last_close(char *iter)
{
	if (*iter == '\n' && (*(iter - 1) != '1'))
		hanlde_error(ERR_MAP_NOT_CLOSED);
}
