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
