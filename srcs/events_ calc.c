#include "../includes/cub3d.h"

/*given an angle sets raydirx and raydiry*/
void update_ray_dir(t_ray *ray, double view_deg)
{
    if (view_deg != 0 && view_deg != 90
		&& view_deg != 180 && view_deg != 360
			&& view_deg != 270)
	{
		if (view_deg > 0 && view_deg < 180)
			ray->dir_y = -1;
		else
			ray->dir_y = 1;
		if ((view_deg > 0 && view_deg < 90)
			|| (view_deg > 270 || view_deg < 360))
			ray->dir_x = 1;
		else
			ray->dir_x = -1;
	}
	else
	{
		if (view_deg == 0 || view_deg == 360 || view_deg == 180)
        {
            ray->dir_y = 0;
			ray->dir_x = 1;
            if (view_deg == 180)
                ray->dir_x = -1;
        }
        else if (view_deg == 270 || view_deg == 90)
        {
			ray->dir_x = 0;
            ray->dir_y = 1;
            if (view_deg == 90)
                ray->dir_y = -1; 
        }
	}
}