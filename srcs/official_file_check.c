/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   official_file_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:46:44 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/03/01 14:46:45 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	p(char *str)
{
	if (str)
		printf("%s\n", str);
}

static int	is_extension(char *file_name)
{
	char	*dot;

	dot = strrchr(file_name, '.');
	if (!dot || dot == file_name)
		return (0);
	return (strcmp(dot, ".cub") == 0);
}

static int	is_readable(char *file_name, int *fd)
{
	*fd = open(file_name, O_RDONLY);
	return (*fd != -1);
}

static int	is_empty(int fd)
{
	char	buff;
	ssize_t	bytes_read;

	bytes_read = read(fd, &buff, 1);
	if (bytes_read == 0)
		return (0);
	return (1);
}

void	check_file(char *file_name, int *fd)
{
	if (!is_readable(file_name, fd))
		hanlde_error(ERR_FILE_PERMISSION);
	if (!is_extension(file_name))
		hanlde_error(ERR_FILE_EXTENSION);
	if (!is_empty(*fd))
		hanlde_error(ERR_EMPTY_FILE);
	return ;
}
