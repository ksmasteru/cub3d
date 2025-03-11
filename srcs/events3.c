/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:32:19 by hes-saqu          #+#    #+#             */
/*   Updated: 2025/03/11 17:34:52 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdbool.h>

bool	update_player_posx_rkey(t_data *data, double ratio, double castangle)
{
	t_wallvars	wallvars;

	if (castangle >= 0 && castangle <= 180)
	{
		wallvars.ratio_x = MOVE_SPEED * fabs(sin(degtorad(castangle))) * ratio;
		if ((data->map[(int)(data->player->posy)
				/ data->texheight][(int)(data->player->posx + wallvars.ratio_x)
				/ data->texwidth] != 0))
			return (false);
		update_rkey_x1(data, &wallvars);
	}
	else
	{
		wallvars.ratio_x = MOVE_SPEED * fabs(sin(degtorad(castangle)))
			* ratio * (-1);
		if ((data->map[(int)(data->player->posy)
				/ data->texheight][(int)(data->player->posx + wallvars.ratio_x)
				/ data->texwidth] != 0))
			return (false);
		update_rkey_x2(data, &wallvars);
	}
	return (true);
}

bool	update_player_posx_lkey(t_data *data, double ratio, double castangle)
{
	t_wallvars	wallvars;

	if (castangle >= 0 && castangle <= 180)
	{
		wallvars.ratio_x = MOVE_SPEED * fabs(sin(degtorad(castangle)))
			* ratio * (-1);
		if ((data->map[(int)(data->player->posy)
				/ data->texheight][(int)(data->player->posx + wallvars.ratio_x)
				/ data->texwidth] != 0))
			return (false);
		update_lkey_x1(data, &wallvars);
	}
	else
	{
		wallvars.ratio_x = MOVE_SPEED * fabs(sin(degtorad(castangle))) * ratio;
		if ((data->map[(int)(data->player->posy)
				/ data->texheight][(int)(data->player->posx + wallvars.ratio_x)
				/ data->texwidth] != 0))
			return (false);
		update_lkey_x2(data, &wallvars);
	}
	return (true);
}

bool	update_player_posy_rkey(t_data *data, double ratio, double castangle)
{
	t_wallvars	wallvars;

	if ((castangle >= 90 && castangle <= 270))
	{
		wallvars.ratio_y = MOVE_SPEED * fabs(cos(degtorad(castangle))) * ratio;
		if (data->map[(int)(data->player->posy - wallvars.ratio_y)
			/ data->texheight][(int)data->player->posx / data->texwidth] != 0)
			return (false);
		update_rkey_y1(data, &wallvars);
	}
	else
	{
		wallvars.ratio_y = MOVE_SPEED * fabs(cos(degtorad(castangle))) * ratio;
		if (data->map[(int)(data->player->posy - wallvars.ratio_y)
			/ data->texheight][(int)data->player->posx / data->texwidth] != 0)
			return (false);
		update_rkey_y2(data, &wallvars);
	}
	return (true);
}

bool	update_player_posy_lkey(t_data *data, double ratio, double castangle)
{
	t_wallvars	wallvars;

	if ((castangle >= 90 && castangle <= 270))
	{
		wallvars.ratio_y = MOVE_SPEED * fabs(cos(degtorad(castangle))) * ratio;
		if (data->map[(int)(data->player->posy - wallvars.ratio_y)
			/ data->texheight][(int)data->player->posx / data->texwidth] != 0)
			return (false);
		update_lkey_y1(data, &wallvars);
	}
	else
	{
		wallvars.ratio_y = MOVE_SPEED * fabs(cos(degtorad(castangle))) * ratio;
		if (data->map[(int)(data->player->posy - wallvars.ratio_y)
			/ data->texheight][(int)data->player->posx / data->texwidth] != 0)
			return (false);
		update_lkey_y2(data, &wallvars);
	}
	return (true);
}
