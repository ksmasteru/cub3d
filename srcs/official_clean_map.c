#include "../includes/parsing.h"

void	hanlde_error(error_code err)
{
	print_error_message(err);
	exit(err);
}
void    resize(t_map_data	*data, char ***array, int size)
{
    char    **vector;
    int        i;

    i = 0;
    vector = (char **)malloc(sizeof(char *) * (size + 1));
	if (!vector)
		hanlde_error(ERR_MEMORY_ALLOCATION);
	// !check for allocation fail
    while (i < size && size > 0)
    {
		if ((*array)[i] != NULL)
        	vector[i] = (*array)[i];
		else
			vector[i] = NULL;
        i++;
    }
	//!!!!!!!!!!!!!!!!!
	//if (*array)
    	//free(*array);
    *array = vector;
	allocs_addback(&data->allocs, vector);
}

static void	set_map_line(char *buffer, size_t *size, t_map_data *data)
{
	char	*new_line;

	new_line = strchr(buffer, '\n');
	on_off(new_line);
	(data)->map[*size] = strdup(buffer);
	allocs_addback(&data->allocs, (data)->map[*size]);
	on_off(new_line);
	*size += 1;
}

static int	is_allawed(char *iter)
{

	if (*iter != '1' && *iter != '0' &&  *iter != 'N' &&
		  *iter != 'W' && *iter != 'E' && *iter != 'S' && *iter != ' ')
		  hanlde_error(ERR_INVALID_MAP_CHAR);
}

void	check_position(char *iter, t_map_data *data, int w, int h)
{
	if ((*iter == 'N' ||  *iter == 'W' || *iter == 'E' || *iter == 'S'))
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

static void assign_directions(int w, int h, t_map_data *data)
{
	if (w > data->map_width)
		data->map_width = w;
	if (h > data->map_height)
		data->map_height = h;
}

static void	check_last_close(char *iter)
{
	if (*iter == '\n' && (*(iter -1) != '1'))
		hanlde_error(ERR_MAP_NOT_CLOSED);
}

static void	check_start_close(char *iter)
{
	if (*iter != '1')
		hanlde_error(ERR_MAP_NOT_CLOSED);
}

static void	read_map(int fd, t_map_data *data, size_t *size)
{
	char	*buffer;
	char	*iter;
	int		w;
	int		h;

	h = 1;
	buffer = get_next_line(fd);
	allocs_addback(&data->allocs, buffer);
	while (buffer && *buffer != '\n')
	{
		w = 0;
		h++;
		iter = buffer;
		check_start_close(iter);
		while (*iter && *iter != '\n')
		{
			is_allawed(iter);
			check_position(iter, data, w, h);
			iter++;
			w++;
		}
		check_last_close(iter);
		assign_directions(w, h, data);
		resize(data, &data->map, *size);
		set_map_line(buffer, size, data);
		buffer = get_next_line(fd);
		allocs_addback(&data->allocs, buffer);
	}
}

static void	check_eomap(t_map_data *data, int fd)
{
	char	*buffer;

	buffer = get_next_line(fd);
	allocs_addback(&data->allocs, buffer);
	while (buffer)
	{
		if (*buffer != '\n')
		hanlde_error(ERR_INVALID_LINE);
		buffer = get_next_line(fd);
		allocs_addback(&data->allocs, buffer);
	}
}

int	is_map(char *buffer, t_map_data *data, int fd)
{
	char	*iter;
	char	*new_line;
	size_t	size;

	size = 0;
	iter = buffer;
	if (*iter == '1')
	{
		while (*iter == '1')
			iter++;
		if ((*iter != '\n') && iter > buffer)
			hanlde_error(ERR_INVALID_MAP_START);
		resize(data, &data->map, size);
		set_map_line(buffer, &size, data);
		read_map(fd, data, &size);
		if (!data->player_x || !data->player_y || !data->player_dir)
			hanlde_error(ERR_MISSING_PLAYER);
		check_eomap(data, fd);
	}
	return (size);
}
