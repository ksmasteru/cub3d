#ifndef PAS
#define PAS

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 50;

typedef enum {
    // ✅ No error
    ERR_NONE,

    // 📂 File-related errors
    ERR_FILE_NOT_FOUND,      // File does not exist
    ERR_FILE_EXTENSION,      // Incorrect file extension (not .cub)
    ERR_EMPTY_FILE,          // The file is empty
    ERR_FILE_PERMISSION,     // Cannot read file due to permission issues

    // 🎨 Texture-related errors
    ERR_MISSING_TEXTURE,     // A required texture (NO, SO, WE, EA) is missing
    ERR_DUPLICATE_TEXTURE,   // A texture identifier appears more than once
    ERR_INVALID_TEXTURE_PATH,// Texture path is missing or invalid
    ERR_TEXTURE_FILE_MISSING,// Texture file does not exist

    // 🌈 Color-related errors
    ERR_MISSING_COLOR,       // A required color (F or C) is missing
    ERR_DUPLICATE_COLOR,     // A color definition appears more than once
    ERR_INVALID_COLOR_FORMAT,// Incorrect color format (should be R,G,B)
    ERR_COLOR_OUT_OF_RANGE,  // RGB values must be between 0 and 255

    // 🗺️ Map-related errors
    ERR_MAP_NOT_CLOSED,      // The map is not surrounded by walls
    ERR_INVALID_MAP_CHAR,    // The map contains invalid characters
    ERR_MULTIPLE_PLAYERS,    // More than one player (N, S, E, W) found
    ERR_MISSING_PLAYER,      // No player position found
    ERR_INVALID_MAP_START,   // The map appears before textures or colors
	ERR_NEW_LINE_IN_MAP,

    // 🔄 General errors
    ERR_INVALID_LINE,        // A line does not match any expected format
    ERR_MEMORY_ALLOCATION,   // Memory allocation failure

	//skip functions
	ERR_NOT_TEXTURE,
	ERR_NOT_IMG,
	ERR_NOT_MAP,
} error_code;


typedef struct s_allocs{
    struct s_allocs *next;
    void    *addr;
}t_allocs;

typedef struct s_map_data {
    // Texture paths
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;

    // Colors
    int floor_color[3];    // RGB values
    int ceiling_color[3];  // RGB values ??

    // Map data
    char **map;           // 2D array of map characters
    int map_height;
    int map_width;
    int w;
    int h;
    // Player info
    int player_x;         // Starting X position
    int player_y;         // Starting Y position
    char player_dir;      // N, S, E, or W
    t_allocs    *allocs;
} t_map_data;


typedef	struct s_ptrs
{
	// ptr_txt size is 4
	char **ptr_txt;
	// ptr_txt size is 2
	char **ptr_colors;
	// ptr_ size is EOF
	char **ptr_map;
}	t_ptrs;


// enum values	check_file(char *file_name, int *fd);

error_code	is_texture(char *buffer, t_map_data *data);
void	check_file(char *file_name, int *fd);
error_code	is_color(char *buffer, t_map_data *data);
int			is_map(char *buffer, t_map_data *data, int fd);

char	*get_next_line(int fd);
//memory
void	*my_malloc(size_t size);
void	cleanup(void);
// utilies
int		is_space(char c);
int		is_digit(char c);
int		ft_atoi(const char *str);
void	trim_buffer(char **buffer);
void	on_off(char *change);

//read
char	**read_filo(char *file_name, int *fd, t_map_data *data);
void	on_off(char *change);

int	open_file(char *file_name, int close_flag);
void	hanlde_error(error_code err);
void print_map_data(t_map_data data);
void print_error_message(error_code code);
void allocs_addback(t_allocs **allocs, void *addr);
void    allocs_clean_up(t_allocs **allocs);
t_allocs* make_new_node(void    *addr);

#endif
