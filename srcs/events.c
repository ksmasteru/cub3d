#include "../includes/cub3d.h"
#include <stdbool.h>

#define map_w 24
#define map_h 24
extern int map[24][24];
extern double angle;
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
// update the positin then check if its a wall.

	//ray = data->ray;
	//box_x = (int)old_posx / texwidth * texwidth; // current box_x;
	//box_y = (int )old_posy / texheight * texheight;// current box_y;
	// this method doesnt seem good as playerray can have positive x componemet but still wont 
	// go to right.
	/*if (ray.dir_x > 0) //apply this to vertical and horizontal casting
		box_x++;
	else
		box_x--;
	if (ray.dir_y > 0)
		box_y++;
	else
		box_y--;*/
	// check if next box is a wall.
	printf("ray dir x %d ray dir y %d\n", ray.dir_x, ray.dir_y);
	if (ray.dir_x > 0)
		data->player->posx += fabs(MOVE_SPEED * cos(degToRad(data->player->view_deg))); // MOVE SPEED VALUE ?
	else if (ray.dir_x < 0)
		data->player->posx -=  fabs(MOVE_SPEED * cos(degToRad(data->player->view_deg)));
	if (ray.dir_y > 0)
		data->player->posy += fabs(MOVE_SPEED * sin(degToRad(data->player->view_deg))); // sin at this degree is negative
	else if (ray.dir_y < 0)
		data->player->posy -= fabs(MOVE_SPEED * sin(degToRad(data->player->view_deg)));
	// check if its inside a wall. if yes reverse
	printf("new player posx %d posy %d\n", (int)data->player->posx, (int)data->player->posy);
	// first check if its out of bounds.
	if (data->player->posx > map_h * texwidth)
		data->player->posx = map_h  * texwidth - 1;
	else if (data->player->posx < 0)
		data->player->posx = 1;
	if (data->player->posy > map_h * texheight)
		data->player->posy = map_h * texheight - 1;
	else if (data->player->posy < 0)
		data->player->posx = 1;
	if (map[(int)data->player->posy / texheight][(int)data->player->posx / texwidth] != 0)/*wall*/ // it could be equal to -1 : outofpbound
	{
		data->player->posx = old_posx;// or increment by the necessary value. % distance.
		data->player->posy = old_posy;
		return (false); // dont update img.
	}
	return (true);
}

// MOVE DOWN IF NO WALL IS BEHIND THE PLAYER. : inverse of move_up semantics
// of increment/decrementing pos
bool player_move_down(t_data *data, double old_posx, double old_posy)
{
	int box_x;
	int box_y;
	t_ray ray;

	ray = data->ray;
	printf("ray dir x %d ray dir y %d\n", ray.dir_x, ray.dir_y); // dirx == 0 ?
	if (ray.dir_x > 0)
		data->player->posx -= fabs(MOVE_SPEED * cos(degToRad(data->player->view_deg))); // MOVE SPEED VALUE ?
	else if (ray.dir_x < 0)
		data->player->posx +=  fabs(MOVE_SPEED * cos(degToRad(data->player->view_deg)));
	if (ray.dir_y > 0)
		data->player->posy -= fabs(MOVE_SPEED * sin(degToRad(data->player->view_deg)));
	else if (ray.dir_y < 0)
		data->player->posy += fabs(MOVE_SPEED * sin(degToRad(data->player->view_deg)));
	if (data->player->posx > map_w * texwidth)
		data->player->posx = map_w  * texwidth - 1;
	else if (data->player->posx < 0)
		data->player->posx = 1;
	if (data->player->posy > map_h * texheight)
		data->player->posy = map_h * texheight - 1;
	else if (data->player->posy < 0)
		data->player->posx = 1;
	printf("new player posx %d posy %d\n", (int)data->player->posx, (int)data->player->posy);
	if (map[(int)data->player->posy / texheight][(int)data->player->posx / texwidth] != 0)
	{
		data->player->posx = old_posx;
		data->player->posy = old_posy;
		return (false);
	}
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
	if (keycode == XK_Up)
		return (player_move_up(data, old_posx, old_posy));
	return (player_move_down(data, old_posx, old_posy));
}

bool rotate_player_dir(t_data *data, int keycode)
{
    // TODO
	if (keycode == XK_Right)
	{
		data->player->view_deg -= ROTSPEED * 10;
		if (data->player->view_deg < -180)
			data->player->view_deg = 180 - abs((int)data->player->view_deg) % 180;
	}
	else
		data->player->view_deg = (int)(ROTSPEED * 10 + data->player->view_deg) % 360;
	printf("new player->view_deg is %f\n", data->player->view_deg);
	//angle = data->player->view_deg;
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
		else if (keycode == XK_Down || keycode == XK_Up)
			update_img = update_player_pos(data, keycode);
        else if (keycode == XK_Right|| keycode == XK_Left)
            update_img = rotate_player_dir(data, keycode);
		if (update_img)
		{
			printf("image to be updated with view :%f posx %d posy %d\n", data->player->view_deg
			,(int)data->player->posx, (int)data->player->posy);
            render_walls(data);
		}
	}
    return (0);
}