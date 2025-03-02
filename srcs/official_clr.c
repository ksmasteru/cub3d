/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   official_clr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:23:29 by sel-hadd          #+#    #+#             */
/*   Updated: 2025/02/22 20:17:04 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	hanlde_error(error_code err)
{
	printf("Error\n");
	print_error_message(err);
	exit(err);
}

void	print_error(t_map_data	*data, char	*msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	exit (1);
}

static void	set_color(char *buffer, char type, t_map_data *data, char *start)
{
	static int	f_i;
	static int	c_i;

	on_off(buffer);
	if ((type == 'F') && (f_i < 3))
	{
		data->floor_color[f_i] = ft_atoi(start);
		if (data->floor_color[f_i] < 0 || data->floor_color[f_i] > 250)
			print_error(data, "color out of range");
		f_i++;
	}
	else if ((type == 'C') && (c_i < 3))
	{
		data->ceiling_color[c_i] = ft_atoi(start);
		if (data->ceiling_color[c_i] < 0 || data->ceiling_color[c_i] > 250)
			print_error(data, "color out of range");
		c_i++;
	}
	else if (f_i >= 3 || c_i >= 3)
		print_error(data, "invalid color format");
	on_off(buffer);
}

static void	clr(char *buffer, t_map_data *data, error_code *code, char type)
{
	char	*start;

	while (buffer)
	{
		if (*buffer == '\0')
			break ;
		if (!is_digit(*buffer))
		{
			*code = ERR_INVALID_COLOR_FORMAT;
			print_error(data, "invalid color");
		}
		start = buffer;
		while (is_digit(*buffer))
			buffer++;
		if (*buffer == ',' || *buffer == '\n')
			set_color(buffer, type, data, start);
		else
		{
			*code = ERR_MISSING_COLOR;
			print_error(data, "missing color");
		}
		buffer++;
	}
	*code = ERR_NONE;
}

error_code	is_color(char *buffer, t_map_data *data)
{
	char		*start;
	char		type;
	error_code	code;

	if ((*buffer == 'F' || *buffer == 'C') && is_space(*(buffer + 1)))
	{
		type = *buffer;
		if (!is_space(*(buffer + 1)))
			hanlde_error(ERR_INVALID_COLOR_FORMAT);
		buffer = (buffer + 1);
		while (is_space(*buffer))
			buffer++;
		clr(buffer, data, &code, type);
		return (code);
	}
	else
		return (ERR_NOT_IMG);
}
