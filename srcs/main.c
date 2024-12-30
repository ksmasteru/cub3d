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
    {
        printf("keypress up/down\n");
        return (update_player_pos(data, keycode, 0.5));
    }
    if (keycode == XK_Right || keycode == XK_Left)
    {
                printf("keypress r/l\n");
        return (rotate_player_dir(data, keycode, 0.5));
    }
    return (0);
}

int set_up_wall_xpms(t_data *data)
{
    // array of xpm images;
    int width;
    int height;

    data->xpm_imgs = (t_image *)malloc(sizeof(t_image) * TEXTURES_NUMBERS);
    if (!data->xpm_imgs)
        return (-1);
    data->xpm_imgs[0].mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, "./eagle.xpm", &width, &height);
    data->xpm_imgs[0].adrs = mlx_get_data_addr(data->xpm_imgs[0].mlx_img, &(data->xpm_imgs[0].bpp), &(data->xpm_imgs[0].size_line), &(data->xpm_imgs[0].endian));
    data->xpm_imgs[1].mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, "./bluestone.xpm", &width, &height);
    data->xpm_imgs[1].adrs = mlx_get_data_addr(data->xpm_imgs[1].mlx_img, &(data->xpm_imgs[1].bpp), &(data->xpm_imgs[1].size_line), &(data->xpm_imgs[1].endian));
    data->xpm_imgs[2].mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, "./colorstone.xpm", &width, &height);
    data->xpm_imgs[2].adrs = mlx_get_data_addr(data->xpm_imgs[2].mlx_img, &(data->xpm_imgs[2].bpp), &(data->xpm_imgs[2].size_line), &(data->xpm_imgs[2].endian));
    return (1);
}

int main()
{
    t_data *data;

    data = malloc(sizeof(t_data));
    if (!data)
        return (1);
    if (!init_data(data))
        return (1);
    if (!set_up_wall_xpms(data))
        return (1);
    render_walls(data);
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
    mlx_hook(data->win_ptr, 2, 1L<<0, pressed_key_event, data);
	//mlx_key_hook(data->win_ptr, pressed_key_event, data);
    mlx_loop(data->mlx_ptr);
}