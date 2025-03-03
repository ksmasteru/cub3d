/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:27:54 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/03/01 19:27:56 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFF_SIZE 50

typedef enum t_error_code
{
	ERR_NONE,
	ERR_FILE_NOT_FOUND,
	ERR_FILE_EXTENSION,
	ERR_EMPTY_FILE,
	ERR_FILE_PERMISSION,
	ERR_MISSING_TEXTURE,
	ERR_DUPLICATE_TEXTURE,
	ERR_INVALID_TEXTURE_PATH,
	ERR_TEXTURE_FILE_MISSING,
	ERR_MISSING_COLOR,
	ERR_DUPLICATE_COLOR,
	ERR_INVALID_COLOR_FORMAT,
	ERR_COLOR_OUT_OF_RANGE,
	ERR_MAP_NOT_CLOSED,
	ERR_INVALID_MAP_CHAR,
	ERR_MULTIPLE_PLAYERS,
	ERR_MISSING_PLAYER,
	ERR_INVALID_MAP_START,
	ERR_NEW_LINE_IN_MAP,
	ERR_INVALID_LINE,
	ERR_MEMORY_ALLOCATION,
	ERR_NOT_TEXTURE,
	ERR_NOT_IMG,
	ERR_NOT_MAP,
}					t_error_code;

typedef struct s_allocs
{
	struct s_allocs	*next;
	void			*addr;
}					t_allocs;

typedef struct s_map_data
{
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;

	int				floor_color[3];
	int				ceiling_color[3];

	char			**map;
	int				map_height;
	int				map_width;
	int				w;
	int				h;
	int				player_x;
	int				player_y;
	char			player_dir;
	t_allocs		*allocs;
}					t_map_data;

typedef struct s_ptrs
{
	char			**ptr_txt;
	char			**ptr_colors;
	char			**ptr_map;
}					t_ptrs;

typedef struct s_parse
{
	size_t			size;
	size_t			buffer_size;
	t_error_code	err_texture;
	t_error_code	err_img;
	t_error_code	err_map;
}					t_parse;

t_error_code		is_texture(char *buffer, t_map_data *data);
void				check_file(char *file_name, int *fd);
t_error_code		is_color(char *buffer, t_map_data *data);
int					is_map(char *buffer, t_map_data *data, int fd);

char				*get_next_line(int fd);
void				*my_malloc(size_t size);
void				cleanup(void);
int					is_space(char c);
int					is_digit(char c);
int					ft_atoi(const char *str);
void				trim_buffer(char **buffer);
void				on_off(char *change);
char				**read_filo(char *file_name, int *fd, t_map_data *data);
void				on_off(char *change);
int					open_file(char *file_name, int close_flag);
void				hanlde_error(t_error_code err);
void				print_map_data(t_map_data data);
void				print_error_message(t_error_code code);
void				allocs_addback(t_allocs **allocs, void *addr);
void				allocs_clean_up(t_allocs **allocs);
t_allocs			*make_new_node(void *addr);
void				set_map_line(char *buffer, size_t *size, t_map_data *data);
int					is_allawed(char *iter);
void				check_position(char *iter, t_map_data *data, int w, int h);
void				assign_directions(int w, int h, t_map_data *data);
void				print_error_message(t_error_code code);
void				print_general_errors(t_error_code code);
void				print_map_errors(t_error_code code);
void				print_color_errors(t_error_code code);
void				print_texture_errors(t_error_code code);
void				print_file_errors(t_error_code code);
void				ft_trim(char *str);
void				check_errors(char *buffer, size_t size,
						t_error_code err_img, t_error_code err_texture);
int					is_repitor(t_map_data *data);
void				print_error_message(t_error_code code);
void				print_map_errors(t_error_code code);
void				print_color_errors(t_error_code code);
void				print_texture_errors(t_error_code code);
#endif
