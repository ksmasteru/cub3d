/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:01:03 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/02/22 18:44:22 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	check_new(t_list **head)
{
	t_list	*tmp;
	char	*data;

	if (!*head)
		return (0);
	tmp = *head;
	while (tmp)
	{
		data = tmp->content;
		while (*data)
		{
			if (*data == '\n')
				return (1);
			data++;
		}
		tmp = tmp->next;
	}
	return (0);
}

size_t	count_line(t_list *head)
{
	t_list	*tmp;
	char	*data;
	size_t	count;

	tmp = head;
	count = 0;
	while (tmp)
	{
		data = tmp->content;
		while (*data && (*data != '\n'))
		{
			count++;
			data++;
		}
		if (*data == '\n')
			return (++count);
		tmp = tmp->next;
	}
	return (count);
}

void	copy(t_list *head, char *line)
{
	t_list	*tmp;
	char	*data;

	if (!head || !line)
		return ;
	tmp = head;
	while (tmp)
	{
		data = tmp->content;
		while (*data && (*data != '\n'))
			*line++ = *data++;
		if (*data == '\n')
		{
			*line++ = '\n';
			*line = '\0';
			return ;
		}
		tmp = tmp->next;
	}
	*line = '\0';
}

void	clear_list(t_list **head, char *str, t_list *node)
{
	t_list	*tmp;
	t_list	*current;

	tmp = *head;
	while (tmp)
	{
		free(tmp->content);
		current = tmp;
		tmp = tmp->next;
		free(current);
	}
	if (*str)
	{
		node->content = str;
		node->next = NULL;
		*head = node;
		return ;
	}
	free(str);
	free(node);
	*head = NULL;
}

t_list	*last_node(t_list **head)
{
	t_list	*tmp;
	t_list	*last;

	tmp = *head;
	while (tmp)
	{
		last = tmp;
		tmp = tmp->next;
	}
	return (last);
}
