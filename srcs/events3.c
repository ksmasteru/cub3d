#include "../includes/cub3d.h"
#include <stdbool.h>

void    update_rkey_x1(t_data* data, double ratio, double castangle, t_wallvars* wallvars)
{   
        data->player->posx += wallvars->ratio_x;
        wallvars->wallx = (int)data->player->posx / data->texwidth * data->texwidth + data->texwidth;
        wallvars->box_x =  wallvars->wallx / data->texwidth;
        if (data->map[(int)data->player->posy / data->texheight][wallvars->box_x]
		    != 0 && (abs(wallvars->wallx - (int)data->player->posx) < W_B))
            data->player->posx = wallvars->wallx + S + W_B * -1;
}

bool    update_player_posx_rkey(t_data* data, double ratio, double castangle)
{
    t_wallvars wallvars;

    if(castangle >= 0 && castangle <= 180)
    {
        wallvars.ratio_x = MOVE_SPEED * fabs(sin(degtorad(castangle))) * ratio;
        if ((data->map[(int)(data->player->posy)
			/ data->texheight][(int)(data->player->posx + wallvars.ratio_x) / data->texwidth] != 0))
		return (false);
       update_rkey_x1(data, ratio, castangle, &wallvars);
    }
    else
    {
        wallvars.ratio_x = MOVE_SPEED * fabs(sin(degtorad(castangle))) * ratio * -1;
        if ((data->map[(int)(data->player->posy)
			/ data->texheight][(int)(data->player->posx + wallvars.ratio_x) / data->texwidth] != 0))
		return (false);
        data->player->posx += wallvars.ratio_x;
        wallvars.wallx = (int)data->player->posx / data->texwidth * data->texwidth;
        wallvars.box_x =  (wallvars.wallx - 1) / data->texwidth;
        if (data->map[(int)data->player->posy / data->texheight][wallvars.box_x]
		    != 0 && (abs(wallvars.wallx - (int)data->player->posx) < W_B))
            data->player->posx = wallvars.wallx + S + W_B;
    }
    return (true);
}

bool    update_player_posx_lkey(t_data* data, double ratio, double castangle)
{
    // mimics
    double  ratio_x;
    int     wallx;
    int     box_x;
    if (castangle >= 0 && castangle <= 180)
    {  
        // x same direction as y of down.
        ratio_x = MOVE_SPEED * fabs(sin(degtorad(castangle))) * ratio * -1;
        // ratio should always be negative in this side.
        if ((data->map[(int)(data->player->posy)
			/ data->texheight][(int)(data->player->posx + ratio_x) / data->texwidth] != 0))
		return (false);
        data->player->posx += ratio_x;
        // always traveling the left side of the wall on this side.
        wallx = (int)data->player->posx / data->texwidth * data->texwidth;
        box_x =  (wallx - 1) / data->texwidth;
        if (data->map[(int)data->player->posy / data->texheight][box_x]
		    != 0 && (abs(wallx - (int)data->player->posx) < W_B))
            data->player->posx = wallx + S + W_B;
    }
    else
    {
        // x same direction as y of down.
        ratio_x = MOVE_SPEED * fabs(sin(degtorad(castangle))) * ratio;
        if ((data->map[(int)(data->player->posy)
			/ data->texheight][(int)(data->player->posx + ratio_x) / data->texwidth] != 0))
		return (false);
        data->player->posx += ratio_x;
        // always traveling the right side + texwith;
        wallx = (int)data->player->posx / data->texwidth * data->texwidth + data->texwidth;
        box_x =  wallx / data->texwidth;
        if (data->map[(int)data->player->posy / data->texheight][box_x]
		    != 0 && (abs(wallx - (int)data->player->posx) < W_B))
            data->player->posx = wallx + S + W_B * -1;
    }
    return (true);
}

bool    update_player_posy_rkey(t_data* data, double ratio, double castangle)
{
    t_wallvars wallvars;

    if ((castangle >= 90 && castangle <= 270))
    {
        // y goes up with a positive value. it is going up.
        wallvars.ratio_y = MOVE_SPEED * fabs(cos(degtorad(castangle))) * ratio;
        if (data->map[(int)(data->player->posy - wallvars.ratio_y)
		    / data->texheight][(int)data->player->posx / data->texwidth] != 0)
		    return (false);
        data->player->posy -= wallvars.ratio_y;
        wallvars.wally = (int)data->player->posy / data->texheight * data->texheight;
        wallvars.box_y = (wallvars.wally - 1) / data->texheight;
        if (data->map[wallvars.box_y][(int)data->player->posx / data->texwidth] != 0
		    && (abs(wallvars.wally - (int)data->player->posy) < W_B))
        data->player->posy = wallvars.wally + S + W_B;  
    }
    else
    {
        wallvars.ratio_y = MOVE_SPEED * fabs(cos(degtorad(castangle))) * ratio;
        if (data->map[(int)(data->player->posy - wallvars.ratio_y)
		    / data->texheight][(int)data->player->posx / data->texwidth] != 0)
		    return (false);
        data->player->posy += wallvars.ratio_y;
        wallvars.wally = (int)data->player->posy / data->texheight * data->texheight + data->texheight;
        wallvars.box_y = wallvars.wally / data->texheight;
        if (data->map[wallvars.box_y][(int)data->player->posx / data->texwidth] != 0
		    && (abs(wallvars.wally - (int)data->player->posy) < W_B))
        data->player->posy = wallvars.wally + S + W_B * -1;          
    }
    return (true);
}

bool    update_player_posy_lkey(t_data* data, double ratio, double castangle)
{
    t_wallvars wallvars;
    
    if ((castangle >= 90 && castangle <= 270))
    {
        wallvars.ratio_y = MOVE_SPEED * fabs(cos(degtorad(castangle))) * ratio;
        if (data->map[(int)(data->player->posy - wallvars.ratio_y)
		    / data->texheight][(int)data->player->posx / data->texwidth] != 0)
		    return (false);
        data->player->posy += wallvars.ratio_y;
        wallvars.wally = (int)data->player->posy / data->texheight * data->texheight + data->texheight;
        wallvars.box_y = wallvars.wally / data->texheight;
        if (data->map[wallvars.box_y][(int)data->player->posx / data->texwidth] != 0
		    && (abs(wallvars.wally - (int)data->player->posy) < W_B))
        data->player->posy = wallvars.wally + S + W_B * -1;     
    }
    else
    {
        wallvars.ratio_y = MOVE_SPEED * fabs(cos(degtorad(castangle))) * ratio;
        if (data->map[(int)(data->player->posy - wallvars.ratio_y)
		    / data->texheight][(int)data->player->posx / data->texwidth] != 0)
		        return (false);
        data->player->posy -= wallvars.ratio_y;
        wallvars.wally = (int)data->player->posy / data->texheight * data->texheight;
        wallvars.box_y = (wallvars.wally - 1) / data->texheight;
        if (data->map[wallvars.box_y][(int)data->player->posx / data->texwidth] != 0
		    && (abs(wallvars.wally - (int)data->player->posy) < W_B))
        data->player->posy = wallvars.wally + S + W_B;         
    }
    return (true);
}