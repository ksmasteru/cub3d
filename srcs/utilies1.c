/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilies1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:15:57 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/03/02 16:15:59 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	ft_trim(char *str)
{
	while (*str)
	{
		str++;
	}
}

void	trim_buffer(char **buffer)
{
	char	*start;
	char	*end;

	if (buffer == NULL || *buffer == NULL || **buffer == '\0')
		return ;
	start = *buffer;
	while (*start != '\0' && is_space((unsigned char)*start))
		start++;
	if (*start == '\0')
	{
		*buffer = start;
		return ;
	}
	end = start + strlen(start) - 1;
	while (end > start && is_space((unsigned char)*end))
		end--;
	*(end + 1) = '\n';
	*buffer = start;
}

char	*ft_strim(char *str)
{
	int		i;
	int		j;
	char	*res;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	res = (char *)malloc(strlen(str) + 1);
	while (str[i] && isspace(str[i]))
		i++;
	while (str[i])
	{
		if (!isspace(str[i]))
			res[j++] = str[i++];
		else
			i++;
	}
	res[j] = '\0';
	return (res);
}
