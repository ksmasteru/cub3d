#include "../includes/cub3d.h"
#include <stdbool.h>

extern int map[24][24];

int	close_win(t_data *data)
{
	//mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(0);
}

// MAKE IT MORE READEABLE WITH RAYDIRX RAYDIRY
// if MAP[BOX_X][BOX_Y] != 0 move
bool player_move_up(t_data *data, double old_posx, double old_posy)
{
	int box_x;
	int box_y;
	t_ray ray;

	ray = data->ray;
	box_x = (int)old_posx / texwidth * texwidth; // current box_x;
	box_y = (int )old_posy / texheight * texheight;// current box_y;
	if (ray.dir_x > 0) /*apply this to vertical and horizontal casting*/
		box_x++;
	else
		box_x--;
	if (ray.dir_y > 0)
		box_y++;
	else
		box_y--;
	// check if next box is a wall.
	if (map[box_y][box_x] != 0) /*wall found*/
		return false;// improve here for sliding or just going the % distance.
	data->player->posx += MOVE_SPEED * cos(data->player->view_deg); // MOVE SPEED VALUE ?
	data->player->posy += MOVE_SPEED * sin(data->player->view_deg);
	return (true);
}

// MOVE DOWN IF NO WALL IS BEHIND THE PLAYER. : inverse of move_up semantics
// you can alernatively make the player jump inside the next square instead
// of increment/decrementing pos
bool player_move_down(t_data *data, double old_posx, double old_posy)
{
	int box_x;
	int box_y;
	t_ray ray;

	ray = data->ray;
	box_x = (int)old_posx / texwidth * texwidth; // current box_x;
	box_y = (int )old_posy / texheight * texheight;// current box_y;
	if (ray.dir_x > 0) /*apply this to vertical and horizontal casting*/
		box_x--;
	else
		box_x++;
	if (ray.dir_y > 0)
		box_y--;
	else
		box_y++;
	// check if next box is a wall.
	if (map[box_y][box_x] != 0) /*wall found*/
		return false;// improve here for sliding or just going the % distance. or yo
	data->player->posx += MOVE_SPEED * cos(data->player->view_deg); // MOVE SPEED VALUE ?
	data->player->posy += MOVE_SPEED * sin(data->player->view_deg);
	return (true);
}

bool update_player_pos(t_data *data, int keycode)
{
	// CANNOT MOVE UP IF A WALL IS FORWARD VICE-VERSA
	double old_posx;
	double old_posy;
	int box_x;
	int box_y;
	// there is an easier method to see if can move up;
	old_posx = data->player->posx;
	old_posy = data->player->posy;
	// no need to update the ray.
	if (keycode == XK_Right)
		return (player_move_up(data, old_posx, old_posy));
	return (player_move_down(data, old_posx, old_posy));
}

bool rotate_player_dir(t_data *data, int keycode)
{
    // TODO
	if (keycode == XK_Right)
	{
		data->player->view_deg -= ROTSPEED * 15;
		if (data->player->view_deg < -180)
			data->player->view_deg = 180 - abs((int)data->player->view_deg) % 180;
	}
	else
		data->player->view_deg  = (int)(ROTSPEED * 10 + data->player->view_deg) % 360;
	return (true);
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
		else if (keycode == XK_Down || XK_Up)
			update_img = update_player_pos(data, keycode);
        else if (keycode == XK_Right|| keycode == XK_Left)
            update_img = rotate_player_dir(data, keycode);
		if (update_img)
		{
			printf("image to be updated with %f\n", data->player->view_deg);
            render_walls(data);
		}
	}
    return (0);
}