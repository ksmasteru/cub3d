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

// wall detected on xside ::--> slide on y side
bool player_slide_xside(t_data *data)
{
	double old_posy;

	old_posy = data->player->posy;	
	// update posy bases on viewdeg
	if (data->ray.dir_y > 0)
		data->player->posy += fabs(SLIDE_SPEED * sin(data->player->view_deg));
	else
		data->player->posy -= fabs(SLIDE_SPEED * sin(data->player->view_deg));
	// if new coordinates inside a wall reverse op.
	if (map[(int)data->player->posy / texheight][(int)data->player->posx / texwidth] != 0)
	{
		data->player->posy = old_posy;
		return (false);
	}
	printf("player xslide \n");
	return (true);
}

// wall detected on yside ::--> slide on x side
bool player_slide_yside(t_data *data)
{
	double old_posx;

	printf("player yslide\n");
	old_posx = data->player->posx;
	if (data->ray.dir_x > 0)
		data->player->posx += fabs(SLIDE_SPEED * cos(data->player->view_deg));
	else
		data->player->posx -= fabs(SLIDE_SPEED * cos(data->player->view_deg));
	if (map[(int)data->player->posy / texheight][(int)data->player->posx / texwidth] != 0)
	{
		data->player->posx = old_posx;
		return (false);
	}
	printf("player yslide done\n");
	return (true);
}

bool player_slide(t_data *data, int posx, int posy)
{
	int l_wallx;
	int	r_wallx;
	int up_wally;
	int dow_wally;
	int	wally;
	int wallx;
	l_wallx = (posx - 25) / texwidth;
	r_wallx = (posx + 25) / texwidth;
	up_wally = (posy - 25) / texheight;
	dow_wally = (posy + 25) / texheight;
	wally = posy / texheight;
	wallx = posx / texwidth;
	
	// you should substract 1 form wall it is up side.
	printf("wally %d wallx %d l_wallx %d r_wallx %d\n", wally, wallx, l_wallx, r_wallx);
	if ((map[wally][l_wallx] != 0) || (map[wally][r_wallx] != 0)) // a wall on x side--- > -+y
		return (player_slide_yside(data));
	else if ((map[up_wally][wallx] != 0) || (map[dow_wally][wallx] != 0))
		return (player_slide_xside(data));
	return (false);
}

// MAKE IT MORE READEABLE WITH RAYDIRX RAYDIRY
// if MAP[BOX_X][BOX_Y] != 0 move

// updates player posx, posy by x_offset y_offset respectively.
bool _player_move_up(t_data *data, double x_offset, double  y_offset)
{
	double	old_posx;
	double	old_posy;
	int i;

	i = 0;
	update_ray_dir(&(data->ray), data->player->view_deg);
	// what if posx posy get so big ?
	if (map[(int)(data->player->posy + y_offset) / 64][(int)(data->player->posx + x_offset) / 64] != 0)
		return (false);
	old_posx = data->player->posx;
	old_posy = data->player->posy;
	while (i < 20 && map[(int)(data->player->posy + y_offset) / 64][(int)(data->player->posx + x_offset) / 64] == 0)
	{
		if (data->ray.dir_x > 0) /*here*/
			data->player->posx += 1 * fabs(cos(degToRad(data->player->view_deg))); // MOVE SPEED VALUE ?
		else if (data->ray.dir_x < 0)
			data->player->posx -= 1 * fabs(cos(degToRad(data->player->view_deg)));
		if (data->ray.dir_y > 0)
			data->player->posy += 1 * fabs(sin(degToRad(data->player->view_deg))); // sin at this degree is negative
		else if (data->ray.dir_y < 0)
			data->player->posy -= 1 * fabs(sin(degToRad(data->player->view_deg)));
		i++;
	}
	if (i == 20)
	{
		printf("player isnt close to a wall by 20 units\n");
		data->player->posx += x_offset - i;
		data->player->posy += y_offset - i;
		return (true);
	}
	else 
	{
		data->player->posx = old_posx;
		data->player->posy = old_posy;
	}
	return (false);
}

bool player_move_up(t_data *data, double old_posx, double old_posy, double ratio)
{
	int box_x;
	int box_y;
	int	wally;
	int wallx;
	double	original_posx;
	double	original_posy;

	original_posx = old_posx;
	original_posy = old_posy;
	t_ray ray;
    update_ray_dir(&(data->ray), data->player->view_deg);
	ray = data->ray;
	if (ray.dir_x > 0) /*here*/
		data->player->posx += fabs(MOVE_SPEED * ratio * cos(degToRad(data->player->view_deg))); // MOVE SPEED VALUE ?
	else if (ray.dir_x < 0)
		data->player->posx -= fabs(MOVE_SPEED * ratio * cos(degToRad(data->player->view_deg)));
	if (ray.dir_y > 0)
		data->player->posy += fabs(MOVE_SPEED * ratio * sin(degToRad(data->player->view_deg))); // sin at this degree is negative
	else if (ray.dir_y < 0)
		data->player->posy -= fabs(MOVE_SPEED * ratio * sin(degToRad(data->player->view_deg)));
	/*check if its inside a wall. if yes reverse
	printf("new player posx %d posy %d\n", (int)data->player->posx, (int)data->player->posy);
	first check if its out of bounds. .. ?????*/
	if (data->player->posx > map_h * texwidth)
		data->player->posx = map_h  * texwidth - 1;
	else if (data->player->posx < 0)
		data->player->posx = 1;
	if (data->player->posy > map_h * texheight)
		data->player->posy = map_h * texheight - 1;
	else if (data->player->posy < 0)
		data->player->posx = 1;
	old_posx = data->player->posx;
	old_posy = data->player->posy;
	int i = 0;
	while (i < 20 && map[(int)data->player->posy / 64][(int)data->player->posx / 64] == 0)
	{
		if (ray.dir_x > 0) /*here*/
			data->player->posx += 1 * fabs(cos(degToRad(data->player->view_deg))); // MOVE SPEED VALUE ?
		else if (ray.dir_x < 0)
			data->player->posx -= 1 * fabs(cos(degToRad(data->player->view_deg)));
		if (ray.dir_y > 0)
			data->player->posy += 1 * fabs(sin(degToRad(data->player->view_deg))); // sin at this degree is negative
		else if (ray.dir_y < 0)
			data->player->posy -= 1 * fabs(sin(degToRad(data->player->view_deg)));
		i++;
	}
	if (i == 20)
	{
		printf("player isnt close to a wall by 20 units\n");
		data->player->posx = old_posx;
		data->player->posy = old_posy;
		return (true);
	}
	else /*i is less than 20 or inside the wall.*/
	{
		printf("player slide\n");
		// here. which direction caused getting inside the wall radius
		// posx got us inside the wall
		data->player->posx = original_posx;
		data->player->posy = original_posy;
		// if left side x is a wall
	/*if (map[(int)data->player->posy / 64][(int)(data->player->posx - 22) / 64] != 0
			|| map[(int)data->player->posy / 64][(int)(data->player->posx + 22) / 64] != 0)
	{
		if (map[(int)(data->player->posy + 22) / 64][(int)data->player->posx / 64] != 0 
				|| map[(int)(data->player->posy - 22) / 64][(int)data->player->posx / 64] != 0)
		{
			printf("junction !! stop\n");
			return (false);
		}
	}*/
		if (map[(int)data->player->posy / 64][(int)(data->player->posx - 31) / 64] != 0
			|| map[(int)data->player->posy / 64][(int)(data->player->posx + 31) / 64] != 0)
		{
			/*if (map[(int)(data->player->posy + 31) / 64][(int)data->player->posx / 64] != 0 
				|| map[(int)(data->player->posy - 31) / 64][(int)data->player->posx / 64] != 0)
				return (false);*/
			old_posy = data->player->posy;
			data->player->posy -= (SLIDE_SPEED * sin(degToRad(data->player->view_deg)));
			if (map[(int)data->player->posy / 64][(int)data->player->posx / 64] != 0)
			{
				data->player->posy = old_posy;
				return (false);
			}
			printf("updated posy\n");
			return true;
		}
		else if (map[(int)(data->player->posy + 31) / 64][(int)data->player->posx / 64] != 0 
				|| map[(int)(data->player->posy - 31) / 64][(int)data->player->posx / 64] != 0)
		{
			old_posx = data->player->posx;
			data->player->posx += (SLIDE_SPEED * cos(degToRad(data->player->view_deg)));
			// you should return update player pos. which will ensure 20 unit from wach wall.
			if (map[(int)data->player->posy / 64][(int)data->player->posx / 64] != 0)
			{
				data->player->posx = old_posx;
				return (false);
			}
			printf("updated posy\n");
			return true;
		}
		return (false);
		// here slide IN!
		//return (player_slide(data, data->player->posx, data->player->posy));
	}
	return (false);
}

// MOVE DOWN IF NO WALL IS BEHIND THE PLAYER. : inverse of move_up semantics
// of increment/decrementing pos
bool player_move_down(t_data *data, double old_posx, double old_posy, double ratio)
{
	int box_x;
	int box_y;
	t_ray ray;

	ray = data->ray;
	//printf("ray dir x %d ray dir y %d\n", ray.dir_x, ray.dir_y); // dirx == 0 ?
	if (ray.dir_x > 0)
		data->player->posx -= fabs(MOVE_SPEED * ratio * cos(degToRad(data->player->view_deg))); // MOVE SPEED VALUE ?
	else if (ray.dir_x < 0)
		data->player->posx += fabs(MOVE_SPEED * ratio * cos(degToRad(data->player->view_deg)));
	if (ray.dir_y > 0)
		data->player->posy -= fabs(MOVE_SPEED * ratio * sin(degToRad(data->player->view_deg)));
	else if (ray.dir_y < 0)
		data->player->posy += fabs(MOVE_SPEED * ratio * sin(degToRad(data->player->view_deg)));
	if (data->player->posx > map_w * texwidth)
		data->player->posx = map_w  * texwidth - 1;
	else if (data->player->posx < 0)
		data->player->posx = 1;
	if (data->player->posy > map_h * texheight)
		data->player->posy = map_h * texheight - 1;
	else if (data->player->posy < 0)
		data->player->posx = 1;
	//printf("new player posx %d posy %d\n", (int)data->player->posx, (int)data->player->posy);
	if (map[(int)data->player->posy / texheight][(int)data->player->posx / texwidth] != 0)
	{
		data->player->posx = old_posx;
		data->player->posy = old_posy;
		return (false);
	}
	//map[(int)data->player->posy / texwidth][(int)data->player->posx / texwidth] = 6;
	// anD OLD POSITION SHOULD BE 0
	//map[(int)old_posy / texwidth][(int)old_posx / texwidth] = 0;
	return (true);
}

bool	update_player_posy_upkey(t_data *data, int keycode, double ratio, double castAngle)
{
	double	ratio_y;
	double	old_posy;
	int		wally;
	int		boxy;

	ratio_y = MOVE_SPEED * sin(degToRad(castAngle)) * ratio * -1.00;
	if (map[(int)(data->player->posy + ratio_y) / texheight][(int)data->player->posx / texwidth] != 0)
		return (false);
	data->player->posy += ratio_y;
	if (data->ray.dir_y > 0)
	{
		wally = (int)data->player->posy / texheight * texheight + texheight;
		boxy = wally / texheight;
	}
	else
	{
		wally = (int)data->player->posy / texheight * texheight;
		boxy = (wally - 1) / texheight;
	}
	printf("wally is %d\n",wally);
	if (map[boxy][(int)data->player->posx / texwidth] != 0 && (abs(wally - (int)data->player->posy) < WALL_BUFFER))
	{
		printf("player soo close old posy %d", (int)data->player->posy);
		data->player->posy = wally + WALL_BUFFER * data->ray.dir_y * -1;
		printf("new posy %d\n", (int)data->player->posy);
	}
	return (true);
}

bool	update_player_posy_downkey(t_data	*data, int keycode, double ratio, double castAngle)
{
	double	ratio_y;
	double	old_posy;
	int		wally;
	int		boxy;

	ratio_y = MOVE_SPEED * sin(degToRad(castAngle)) * ratio;
	if ((map[(int)(data->player->posy + ratio_y) / texheight][(int)data->player->posx / texwidth] != 0))
		return (false);
	data->player->posy += ratio_y;
	if (data->ray.dir_y > 0) // wall behind you going back
	{
		wally = (int)data->player->posy / texheight * texheight;
		boxy = (wally - 1) / texheight;
	}
	else
	{
		wally = (int)data->player->posy / texheight * texheight + texheight;
		boxy = wally / texheight;
	}
	if (map[boxy][(int)data->player->posx / texwidth] != 0 && (abs(wally - (int)data->player->posy) < WALL_BUFFER))
		data->player->posy = wally + SLIDE_CST + WALL_BUFFER * data->ray.dir_y;
	return (true);
}

// updates players posx + makes sure there is atleast 20 units away from nearest x wall.
bool	update_player_posx_upkey(t_data *data, int keycode, double ratio, double castAngle)
{
	double	ratio_x;
	double	old_posx;
	int		wallx;
	int		box_x;

	ratio_x = MOVE_SPEED * cos(degToRad(castAngle)) * ratio;
	// rounding; if ray.dir_x == 0 return false ?
	if ((map[(int)data->player->posy / texheight][(int)(data->player->posx + ratio_x) / texwidth] != 0))
		return (false);
	data->player->posx += ratio_x;
	// 20 units from the nearest wall x of his direction.
	// if player going right
	if (data->ray.dir_x > 0)
	{
		wallx = (int)data->player->posx / texwidth * texwidth + texwidth;
		box_x = wallx / texwidth;
	}
	else
	{
		wallx = (int)data->player->posx / texwidth * texwidth;
		box_x = (wallx - 1) / texwidth;
	}
	printf("next wall x is %d\n", wallx);
	if (map[(int)data->player->posy /texheight][box_x] != 0 && (abs(wallx - (int)data->player->posx) < WALL_BUFFER)) // is a wall and it is less
	{
		printf("player too close old posx is %d", data->player->posx);
		data->player->posx = wallx + SLIDE_CST + WALL_BUFFER * data->ray.dir_x * -1;
		printf("new posx is %d\n", data->player->posx);
	}
	return (true);
}

bool	update_player_posx_downkey(t_data *data, int keycode, double ratio, double castAngle)
{
	double	ratio_x;
	double	old_posx;
	int		wallx;
	int		box_x;

	ratio_x = MOVE_SPEED * cos(degToRad(castAngle)) * ratio * -1.00;
	if ((map[(int)data->player->posy / texheight][(int)(data->player->posx + ratio_x) / texwidth] != 0))
		return (false);
	data->player->posx += ratio_x;
	if (data->ray.dir_x > 0)
	{
		wallx = (int)data->player->posx / texwidth * texwidth;
		box_x = (wallx - 1) / texwidth;
	}
	else
	{
		wallx = (int)data->player->posx / texwidth * texwidth + texwidth;
		box_x = wallx / texwidth;
	}
	if (map[(int)data->player->posy /texheight][box_x] != 0 && (abs(wallx - (int)data->player->posx) < WALL_BUFFER))
		data->player->posx = wallx + SLIDE_CST +WALL_BUFFER * data->ray.dir_x;
	return (true);
}

bool update_player_pos(t_data *data, int keycode, double ratio)
{
	// CANNOT MOVE UP IF A WALL IS FORWARD VICE-VERSA
	bool boolx;
	bool booly;
	double	castAngle;
	// there is an easier method to see if can move up;
	castAngle = data->player->view_deg;
	if (castAngle == 0 || castAngle == 90 || castAngle == 270
		|| castAngle == 180 || castAngle == 360)
		castAngle += 1;
	update_ray_dir(&(data->ray), castAngle);
	//old_posx = data->player->posx;
	//old_posy = data->player->posy;
	// no need to update the ray.
	//if (keycode == XK_Up)
	//	return (player_move_up(data, old_posx, old_posy, ratio));
	//return (player_move_down(data, old_posx, old_posy, ratio));
	if (keycode == XK_Up)
	{
		boolx = update_player_posx_upkey(data, keycode, ratio, castAngle);
		booly = update_player_posy_upkey(data, keycode, ratio, castAngle);
	}
	else if (keycode == XK_Down)
	{
		boolx = update_player_posx_downkey(data, keycode, ratio, castAngle);
		booly = update_player_posy_downkey(data, keycode, ratio, castAngle);
	}
	if (boolx || booly)
		return (true);
	return (false);
}

bool rotate_player_dir(t_data *data, int keycode, double ratio)
{
    // TODO
	if (keycode == XK_Right)
	{
		data->player->view_deg -= ratio * ROTSPEED * 10;
		if (data->player->view_deg < -180)
			data->player->view_deg = 180 - abs((int)data->player->view_deg) % 180;
	}
	else
		data->player->view_deg = (int)(ratio * ROTSPEED * 10 + data->player->view_deg) % 360;
	//printf("new player->view_deg is %f\n", data->player->view_deg);
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
			update_img = update_player_pos(data, keycode, 0.3);
        else if (keycode == XK_Right || keycode == XK_Left)
            update_img = rotate_player_dir(data, keycode, 0.3);
		if (update_img)
		{
			//printf("image to be updated with view :%f posx %d posy %d\n", data->player->view_deg
			//(int)data->player->posx, (int)data->player->posy);
            render_walls(data);
		}
	}
    return (0);
}