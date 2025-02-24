/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 04:11:14 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/02/25 15:25:46 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 25
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

void	add_node(t_list **head, char *buffer);
void	new_head(t_list **head);
char	*process_list(t_list *head);
void	read_file(t_list **head, int fd);
char	*get_next_line(int fd);
size_t	check_new(t_list **head);
size_t	count_line(t_list *head);
void	copy(t_list *head, char *line);
void	clear_list(t_list **head, char *str, t_list *node);
t_list	*last_node(t_list **head);
#endif
