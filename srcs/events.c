#include "../includes/cub3d.h"

int	close_win(t_data *data)
{
	//mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(0);
}

int update_player_pos(t_data *data, int scale)
{
     // TODO
}

int rotate_player_dir(t_data *data, int keycode)
{
    // TODO
}


int	pressed_key_event(int keycode, t_data *data)
{
  bool update_img;

  update_img = true;
	if (keycode == 53 || keycode  == XK_Up || keycode == XK_Down
    || keycode == XK_Right || keycode == XK_Left)
	{
		if (keycode == 53)
	    	close_win(data);
		else if (keycode == XK_Down)
			update_img = update_player_pos(data, -1);
        else if (keycode == XK_Right|| keycode == XK_Left)
            rotate_player_dir(data, keycode);
		if (update_img)
            render_walls(data);
	}
    return (0);
}