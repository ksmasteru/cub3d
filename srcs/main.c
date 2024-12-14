#include "../includes/cub3d.h"

int init_data(t_data *data)
{
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
        return (-1);
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "CUB3D");
    if (!data->win_ptr)
        return (-1);
    data->player = malloc(sizeof(t_player));
    if (!data->player)
        return (-1);
    data->img = malloc(sizeof(t_image));
    if (!data->img)
        return (NULL);
    data->img->mlx_img = NULL;
    data->player->posx = 224;
    data->player->posy = 224;
    data->player->view_deg = 45;
}

int main()
{
    t_data *data;

    data = malloc(sizeof(t_data));
    if (!data)
        return (1);
    if (!init_data(data))
        return (1);
    render_walls(data);
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
	mlx_key_hook(data->win_ptr, pressed_key_event, data);
    mlx_loop(data->mlx_ptr);
}