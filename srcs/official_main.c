#include "../includes/parsing.h"

void print_map_data(t_map_data data)
{
	printf("\n");
	printf("--------------\n");
    printf("North texture: %s\n", data.north_texture);
    printf("South texture: %s\n", data.south_texture);
    printf("West texture: %s\n", data.west_texture);
    printf("East texture: %s\n", data.east_texture);

    printf("Floor color: RGB(%d, %d, %d)\n", data.floor_color[0], data.floor_color[1], data.floor_color[2]);
    printf("Ceiling color: RGB(%d, %d, %d)\n", data.ceiling_color[0], data.ceiling_color[1], data.ceiling_color[2]);

    printf("Map dimensions: %dx%d\n", data.map_width, data.map_height);

    // Printing the map if it's a 2D array of characters
    printf("Map:\n");
    for (int i = 0; i < data.map_height; i++) {
        printf("%s\n", data.map[i]);
    }
    printf("Player position: (%d, %d)\n", data.player_x, data.player_y);
    printf("Player direction: %c\n", data.player_dir);
	printf("--------------");
	printf("\n");
}

int is_repitor(t_map_data *data)
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


void print_error_message(error_code code)
{
    switch (code) {
        case ERR_NONE:
            printf("ERR_NONE\n");
            break;
        case ERR_FILE_NOT_FOUND:
            printf("ERR_FILE_NOT_FOUND\n");
            break;
        case ERR_FILE_EXTENSION:
            printf("ERR_FILE_EXTENSION\n");
            break;
        case ERR_EMPTY_FILE:
            printf("ERR_EMPTY_FILE\n");
            break;
        case ERR_FILE_PERMISSION:
            printf("ERR_FILE_PERMISSION\n");
            break;
        case ERR_MISSING_TEXTURE:
            printf("ERR_MISSING_TEXTURE\n");
            break;
        case ERR_DUPLICATE_TEXTURE:
            printf("ERR_DUPLICATE_TEXTURE\n");
            break;
        case ERR_INVALID_TEXTURE_PATH:
            printf("ERR_INVALID_TEXTURE_PATH\n");
            break;
        case ERR_TEXTURE_FILE_MISSING:
            printf("ERR_TEXTURE_FILE_MISSING\n");
            break;
        case ERR_MISSING_COLOR:
            printf("ERR_MISSING_COLOR\n");
            break;
        case ERR_DUPLICATE_COLOR:
            printf("ERR_DUPLICATE_COLOR\n");
            break;
        case ERR_INVALID_COLOR_FORMAT:
            printf("ERR_INVALID_COLOR_FORMAT\n");
            break;
        case ERR_COLOR_OUT_OF_RANGE:
            printf("ERR_COLOR_OUT_OF_RANGE\n");
            break;
        case ERR_MAP_NOT_CLOSED:
            printf("ERR_MAP_NOT_CLOSED\n");
            break;
        case ERR_INVALID_MAP_CHAR:
            printf("ERR_INVALID_MAP_CHAR\n");
            break;
        case ERR_MULTIPLE_PLAYERS:
            printf("ERR_MULTIPLE_PLAYERS\n");
            break;
        case ERR_MISSING_PLAYER:
            printf("ERR_MISSING_PLAYER\n");
            break;
        case ERR_INVALID_MAP_START:
            printf("ERR_INVALID_MAP_START\n");
            break;
        case ERR_INVALID_LINE:
            printf("ERR_INVALID_LINE\n");
            break;
        case ERR_MEMORY_ALLOCATION:
            printf("ERR_MEMORY_ALLOCATION\n");
            break;
        case ERR_NOT_TEXTURE:
            printf("ERR_NOT_TEXTURE\n");
            break;
        case ERR_NOT_IMG:
            printf("ERR_NOT_IMG\n");
            break;
        case ERR_NOT_MAP:
            printf("ERR_NOT_MAP\n");
            break;
        default:
            printf("Unknown error code\n");
    }
}

static void	assign_struct(t_map_data *data)
{
	data->east_texture = NULL;
	data->west_texture = NULL;
	data->south_texture = NULL;
	data->north_texture = NULL;
	data->ceiling_color[0] = -1;
	data->ceiling_color[1] = -1;
	data->ceiling_color[2] = -1;
	data->floor_color[0] = -1;
	data->floor_color[1] = -1;
	data->floor_color[2] = -1;
	data->player_dir = '\0';
	data->map_height = 0;
	data->map_width = 0;
	data->player_x = 0;
	data->player_y = 0;
}

static void	start_parsing(int fd, char *buffer, t_map_data *data)
{
	size_t		size = 0;
	size_t		buffer_size;
	error_code	err_texture;
	error_code	err_img;
	error_code	err_map;

	while (buffer)
	{
		if (*buffer != '\n')
		{
			trim_buffer(&buffer);
			err_texture = is_texture(buffer, data);
			err_img = is_color(buffer, data);
			size = is_map(buffer, data, fd);
			if ((err_texture != ERR_NONE && err_texture != ERR_NOT_TEXTURE)
				|| (err_img != ERR_NONE && err_img != ERR_NOT_IMG))
					exit(printf("error o safi"));
			else if ((err_texture == ERR_NOT_TEXTURE) && (err_img == ERR_NOT_IMG) && size == 0)
				exit(printf("imposter line [%s]", buffer));
			else if (size > 0)
				break;
		}
		buffer = get_next_line(fd);
        allocs_addback(&data->allocs, buffer);
	}
}

t_map_data  *init_t_map_data()
{
    t_map_data *data;

    data = (t_map_data *)malloc(sizeof(t_map_data));
    data->north_texture = NULL;
    data->south_texture = NULL;
    data->west_texture = NULL;
    data->east_texture = NULL;
    data->map = NULL;
    data->allocs = NULL;
    return (data);
}

t_map_data* parse_cub_file(int ac, char **av)
{
	t_map_data	*data;
	size_t		size;
	int			fd;
	char		*buffer;
	error_code	err;

    data = init_t_map_data();
	if (ac == 2)
	{
		check_file(av[1], &fd);
		close (fd);
		assign_struct(data);
		fd = open_file(av[1], 0);
		buffer = get_next_line(fd);
        allocs_addback(&data->allocs, buffer);
		if (buffer == NULL)
		{
			hanlde_error(ERR_INVALID_LINE);
			return (NULL);
		}
		start_parsing(fd, buffer, data);
		printf("done parsing\n");
		if (data->map_height > 0)
		{
			char *iter = data->map[data->map_height-1];
			while (*iter)
			{
				if (*iter != '1')
					return(printf("error last 11111111\n"), NULL);
				iter++;
			}
		}
		if (!data->east_texture || !data->west_texture || !data->south_texture || !data->north_texture)
			return(printf("misssing paths\n"), NULL);
		return (data);
	}
	else
		printf("entre correct args number!!\n");
	return (NULL);
}
