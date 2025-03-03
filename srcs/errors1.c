/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:54:35 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/03/03 13:54:41 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	is_repitor(t_map_data *data)
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

void	print_texture_errors(t_error_code code)
{
	if (code == ERR_MISSING_TEXTURE)
		printf("ERR_MISSING_TEXTURE\n");
	else if (code == ERR_DUPLICATE_TEXTURE)
		printf("ERR_DUPLICATE_TEXTURE\n");
	else if (code == ERR_INVALID_TEXTURE_PATH)
		printf("ERR_INVALID_TEXTURE_PATH\n");
	else if (code == ERR_TEXTURE_FILE_MISSING)
		printf("ERR_TEXTURE_FILE_MISSING\n");
}

void	print_color_errors(t_error_code code)
{
	if (code == ERR_MISSING_COLOR)
		printf("ERR_MISSING_COLOR\n");
	else if (code == ERR_DUPLICATE_COLOR)
		printf("ERR_DUPLICATE_COLOR\n");
	else if (code == ERR_INVALID_COLOR_FORMAT)
		printf("ERR_INVALID_COLOR_FORMAT\n");
	else if (code == ERR_COLOR_OUT_OF_RANGE)
		printf("ERR_COLOR_OUT_OF_RANGE\n");
}

void	print_map_errors(t_error_code code)
{
	if (code == ERR_MAP_NOT_CLOSED)
		printf("ERR_MAP_NOT_CLOSED\n");
	else if (code == ERR_INVALID_MAP_CHAR)
		printf("ERR_INVALID_MAP_CHAR\n");
	else if (code == ERR_MULTIPLE_PLAYERS)
		printf("ERR_MULTIPLE_PLAYERS\n");
	else if (code == ERR_MISSING_PLAYER)
		printf("ERR_MISSING_PLAYER\n");
	else if (code == ERR_INVALID_MAP_START)
		printf("ERR_INVALID_MAP_START\n");
	else if (code == ERR_INVALID_LINE)
		printf("ERR_INVALID_LINE\n");
}

void	print_error_message(t_error_code code)
{
	if (code == ERR_NONE)
		printf("ERR_NONE\n");
	else if (code == ERR_FILE_NOT_FOUND)
		printf("ERR_FILE_NOT_FOUND\n");
	else if (code == ERR_FILE_EXTENSION)
		printf("ERR_FILE_EXTENSION\n");
	else if (code == ERR_EMPTY_FILE)
		printf("ERR_EMPTY_FILE\n");
	else if (code == ERR_FILE_PERMISSION)
		printf("ERR_FILE_PERMISSION\n");
	else if (code == ERR_MEMORY_ALLOCATION)
		printf("ERR_MEMORY_ALLOCATION\n");
	else if (code == ERR_NOT_TEXTURE)
		printf("ERR_NOT_TEXTURE\n");
	else if (code == ERR_NOT_IMG)
		printf("ERR_NOT_IMG\n");
	else if (code == ERR_NOT_MAP)
		printf("ERR_NOT_MAP\n");
	else
	{
		print_texture_errors(code);
		print_color_errors(code);
		print_map_errors(code);
	}
}
