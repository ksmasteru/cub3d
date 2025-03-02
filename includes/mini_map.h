/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:27:42 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/03/01 19:27:45 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_MAP_H
# define MINI_MAP_H

# include "../includes/cub3d.h"
t_map	fill_map_data(t_data *data);
int		fill_square_pixels(t_map *map, t_image *img, int color);
int		put_mini_map(t_data *data);
#endif
