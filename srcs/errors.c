/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:07:34 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/03/01 15:07:36 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	print_file_errors(t_error_code code)
{
	if (code == ERR_FILE_NOT_FOUND)
		printf("ERR_FILE_NOT_FOUND\n");
	else if (code == ERR_FILE_EXTENSION)
		printf("ERR_FILE_EXTENSION\n");
	else if (code == ERR_EMPTY_FILE)
		printf("ERR_EMPTY_FILE\n");
	else if (code == ERR_FILE_PERMISSION)
		printf("ERR_FILE_PERMISSION\n");
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
}

void	print_general_errors(t_error_code code)
{
	if (code == ERR_INVALID_LINE)
		printf("ERR_INVALID_LINE\n");
	else if (code == ERR_MEMORY_ALLOCATION)
		printf("ERR_MEMORY_ALLOCATION\n");
	else if (code == ERR_NOT_TEXTURE)
		printf("ERR_NOT_TEXTURE\n");
	else if (code == ERR_NOT_IMG)
		printf("ERR_NOT_IMG\n");
	else if (code == ERR_NOT_MAP)
		printf("ERR_NOT_MAP\n");
}
