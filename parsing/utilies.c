#include "parsing.h"

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

int    ft_atoi(const char *str)
{
    int    result;
    int    sign;
    int    i;

    result = 0;
    sign = 1;
    i = 0;
    while (is_space(str[i]))
        i++;
    if (str[i] == '+' && str[i + 1] != '-')
        i++;
    /* if the current character is -, we make sign equal to -1 so
     * we can simply multiply the final result by this sign
     * to get the negative or positive number
     */
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (str[i] && str[i] >= 48 && str[i] <= 57)
    {
        /* take a look under this expandable, I made a clearer example
         * of how this part works
         */
        result *= 10;
	result += str[i] - 48;
	i++;
    }
    result *= sign;
    return (result);
}

void	ft_trim(char *str)
{
	while (*str)
	{
		str++;
	}
}
