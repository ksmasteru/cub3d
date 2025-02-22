NAME = parsing

SRC = get_next_line_utils.c get_next_line.c \
	official_clean_map.c official_clr.c official_file_check.c \
	official_main.c official_txt.c \
	utilies.c

OBJ = $(SRC:.c=.o)


all : $(NAME)

$(NAME) : $(OBJ)
	cc $(OBJ) -g3 -o $@

%.o : %.c
	cc -c -g3 $< -o $@

clean : 
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re : fclean all
