/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:14:24 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/03/01 15:14:26 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	on_off(char *change)
{
	static char	c;

	if (change == NULL)
		return ;
	if (c == '\0')
	{
		c = *change;
		*change = '\0';
	}
	else
	{
		*change = c;
		c = '\0';
	}
}

int	open_file(char *file_name, int close_flag)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (close_flag)
	{
		close(fd);
		return (1);
	}
	else
		return (fd);
}

int	is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	result *= sign;
	return (result);
}
