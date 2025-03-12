BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCS		=	srcs/main.c srcs/events.c srcs/render.c srcs/calculations.c  \
				srcs/events_calc.c srcs/ft_strjoin.c srcs/mini_map.c	\
				srcs/calculations1.c srcs/calculations2.c srcs/dispatcher.c \
				srcs/events2.c srcs/mini_map2.c srcs/draw.c \
				srcs/get_next_line_utils.c srcs/get_next_line.c \
				srcs/official_clean_map.c srcs/official_clr.c srcs/official_file_check.c \
				srcs/official_main.c srcs/official_txt.c srcs/events3.c \
				srcs/utilies.c srcs/t_allocs.c srcs/official_clean_map2.c srcs/utilies1.c \
				srcs/utilies2.c srcs/main_2.c srcs/official_main2.c srcs/errors1.c \
				srcs/l_key.c srcs/r_key.c
SRCS_B		= 	srcs_bonus/main_bonus.c \

NAME		= cub3d
NAME_B		= cub3d_bonus
minilibx	= mlx/libmlx.a
OBJS_DIR	= objs/
OBJS_DIR_B	= objs_b/
OBJS		= $(SRCS:.c=.o)
OBJS_B		= $(SRCS_B:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
OBJECTS_PREFIXED_B = $(addprefix $(OBJS_DIR_B), $(OBJS_B))
CC			= gcc
CC_FLAGS	= -g -Wall -Werror -Wextra
MLB_FLAGS	= -I -g3 -L /usr/X11/lib -Lincludes -L./mlx -lmlx -Imlx -lXext -lX11 -lz -lm

$(OBJS_DIR)%.o : %.c includes/cub3d.h
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)srcs
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR_B)%.o : %.c includes/cub3d.h
	@mkdir -p $(OBJS_DIR_B)	
	@mkdir -p $(OBJS_DIR_B)srcs_bonus
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS_PREFIXED) maker
	@$(CC) $(CC_FLAGS) -o $(NAME) $(OBJECTS_PREFIXED) $(MLB_FLAGS)

$(NAME_B): $(OBJECTS_PREFIXED_B) maker
	@$(CC) -o $(NAME_B) $(OBJECTS_PREFIXED_B) $(CC_FLAGS) $(MLB_FLAGS)

all: $(NAME)

maker:
	@make -C mlx

clean:
	@rm -rf $(OBJS_DIR)
	@rm -rf $(OBJS_DIR_B)
	@echo "${GRN}[CLEAN]${RST} done"

fclean: clean
	@make clean -C mlx
	@rm -f $(NAME)
	@rm -f $(NAME_B)
	@echo "${GRN}[FCLEAN]${RST} done"

re: fclean all

.PHONY:		all clean fclean re