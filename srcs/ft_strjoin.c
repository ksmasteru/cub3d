/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:31:53 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/03/05 13:31:54 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_size(int n)
{
	int i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int num)
{
	char		*dst;
	int			count;
	int			i;
	long int	n;

	n = num;
	count = count_size(n);
	i = 0;
	if (n < 0 || count == 0)
		count++;
    dst = (char *)malloc(sizeof(char) * (count + 1));
    dst[count] = 0;
	if (n < 0)
	{
		n *= -1;
		dst[0] = '-';
		i++;
	}
	while (count > i)
	{
		count--;
		dst[count] = (n % 10) + '0';
		n /= 10;
	}
	return (dst);
}

char	*ft_strdup2(char *s1)
{
	char	*str;
	int		size;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	size = strlen(s1);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1_lent;
	int		s2_lent;
	char	*str;

	if (s1 == NULL)
		return (ft_strdup2(s2));
	if (s2 == NULL)
		return (ft_strdup2(s1));
	s1_lent = strlen(s1);
	s2_lent = strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_lent + s2_lent + 1));
	if (!str)
		return (NULL);
	return (ft_strjoin2(s1, s2, str));
}

char	*ft_strjoin2(char *s1, char *s2, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}