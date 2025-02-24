#include "../includes/parsing.h"

void	p(char *str)
{
	if (str)
		printf("%s\n", str);
}

static int is_extension(char *file_name)
{

    char *dot = strrchr(file_name, '.'); // Find last '.'

    if (!dot || dot == file_name) // No dot or dot at the start
        return (0);
    return(strcmp(dot, ".cub") == 0); // Ensure it's exactly ".cub"
}

static int	is_readable(char *file_name, int *fd)
{
	*fd = open(file_name, O_RDONLY);
	return (*fd != -1);
}

static int	is_empty(int fd)
{
	char	buff;
	ssize_t bytes_read;

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
