#include "parsing.h"

void	on_off(char *change)
{
	static char	c;

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

char	*is_path(char *path)
{
	int		img_fd;
	char	*new_line;

	if (!*path)
		return (0);
	while (is_space(*path))
		path++;
	if (*path)
	{
		new_line = strchr(path, '\n');
		if (new_line == NULL)
		{
			printf("new line address is %p\n",new_line);
			exit(1);
		}
		on_off(new_line);
		path = strdup(path);
		on_off(new_line);
		img_fd = open(path, O_RDONLY);
		if (img_fd == -1)
			hanlde_error(ERR_INVALID_TEXTURE_PATH);
		else
		{
			close(img_fd);
			return (path);
		}
	}
	else
		return (NULL);
}

static int	is_texture_full(t_map_data *data)
{
	return (data->north_texture && data->south_texture && data->west_texture && data->east_texture);
}

static int	identifier_found(char *buffer)
{
	if (((buffer[0] == 'N') && (buffer[1] == 'O') && (is_space(buffer[2]))) ||
		((buffer[0] == 'S') && (buffer[1] == 'O') && (is_space(buffer[2]))) ||
		((buffer[0] == 'W') && (buffer[1] == 'E') && (is_space(buffer[2]))) ||
		((buffer[0] == 'E') && (buffer[1] == 'A') && (is_space(buffer[2]))))
		{
			return (1);
		}
	return (0);
}

static int	set_texture(t_map_data *data, char *buffer, char *img_path)
{
	if ((buffer[0] == 'N') && !data->north_texture)
		return (data->north_texture = img_path, 1);
	else if ((buffer[0] == 'S'))
		return (data->south_texture = img_path, 1);
	else if ((buffer[0] == 'W'))
		return (data->west_texture = img_path, 1);
	else if ((buffer[0] == 'E'))
		return (data->east_texture = img_path, 1);
	else
		return (0);
}

error_code	is_texture(char *buffer, t_map_data *data)
{
	char	*img_path;

	if (identifier_found(buffer))
	{
		img_path = is_path(&buffer[2]);
		if (img_path)
		{
			if (set_texture(data, buffer, img_path) == 1)
				return (ERR_NONE);
		}
	}
	else
		return (ERR_NOT_TEXTURE);
}
