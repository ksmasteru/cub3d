#include "parsing.h"

// int	start_the_show_a(char *buffer, int *c_t, int *f_i, char start, error_code *code)
// {
// 	on_off(buffer);
// 			if ((type == 'F') && (f_i < 3))
// 			{
// 				data->floor_color[f_i] = ft_atoi(start);
// 				if (data->floor_color[f_i] < 0 || data->floor_color[f_i] > 250)
// 				{
// 					*code = ERR_COLOR_OUT_OF_RANGE;
// 					return ;
// 				}
// 				f_i++;
// 			}
// 			else if ((type == 'C') && (c_i < 3))
// 			{
// 				data->ceiling_color[c_i] = ft_atoi(start);
// 				if (data->ceiling_color[c_i] < 0 || data->ceiling_color[c_i] > 250)
// 				{
// 					*code = ERR_COLOR_OUT_OF_RANGE;
// 					return ;
// 				}
// 				c_i++;
// 			}
// 			on_off(buffer);
// }

static void	start_the_show(char *buffer, t_map_data *data, error_code *code, char type)
{
	char		*start;
	static int	f_c[2];
	static int	f_i;
	static int	c_i;

	while(buffer)
	{
		if (*buffer == '\0')
			break;
		if (!is_digit(*buffer))
		{
			*code = ERR_INVALID_COLOR_FORMAT;
			return ;
		}
		start = buffer;
		while (is_digit(*buffer))
			buffer++;
		if (*buffer == ',' || *buffer == '\n')
		{
			on_off(buffer);
			if ((type == 'F') && (f_i < 3))
			{
				data->floor_color[f_i] = ft_atoi(start);
				if (data->floor_color[f_i] < 0 || data->floor_color[f_i] > 250)
				{
					*code = ERR_COLOR_OUT_OF_RANGE;
					return ;
				}
				f_i++;
			}
			else if ((type == 'C') && (c_i < 3))
			{
				data->ceiling_color[c_i] = ft_atoi(start);
				if (data->ceiling_color[c_i] < 0 || data->ceiling_color[c_i] > 250)
				{
					*code = ERR_COLOR_OUT_OF_RANGE;
					return ;
				}
				c_i++;
			}
			on_off(buffer);
		}

		else
		{
			*code = ERR_MISSING_COLOR;
			return ;
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
			// return (ERR_INVALID_COLOR_FORMAT);
		buffer = (buffer + 1);
		while (is_space(*buffer))
			buffer++;
		start_the_show(buffer, data, &code, type);
		return (code);
	}
	else
		return (ERR_NOT_IMG);
}
