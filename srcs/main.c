#include "../includes/cub3d.h"

int init_data(t_data *data)
{
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
        return (-1);
    data->win_ptr = mlx_new_window(data->mlx_ptr, SCREEN_W, SCREEN_H, "CUB3D");
    if (!data->win_ptr)
        return (-1);
    data->player = malloc(sizeof(t_player));
    if (!data->player)
        return (-1);
    data->img = malloc(sizeof(t_image));
    if (!data->img)
        return (-1);
    data->mini_map = malloc(sizeof(t_image));
    if (!data->mini_map)
        return (-1);
    data->mini_map->mlx_img = NULL;
    data->img->mlx_img = NULL;
    data->player->posx = 1034;
    data->player->posy = 243;
    data->player->view_deg = 45;
}

int key_pressed(int keycode, t_data  *data)
{
    printf("keycode %d was held pressed\n", keycode); //works.
    // so how.
    // player moves up by which ratio ?
    if (keycode == XK_Up || keycode == XK_Down)
        return (update_player_pos(data, keycode));
    if (keycode == XK_Right || keycode == XK_Left)
        return (rotate_player_dir(data, keycode));
    return (0);
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
    mlx_hook(data->win_ptr, 2, 1L<<0, key_pressed, data);
	mlx_key_hook(data->win_ptr, pressed_key_event, data);
    mlx_loop(data->mlx_ptr);
}