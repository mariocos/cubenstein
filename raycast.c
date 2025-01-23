#include "cube.h"

void	init_vars(t_vars *v)
{
	v->x = -1;
}


void	ray_cast(t_data *g)
{
	t_vars	vars;

	init_vars(&vars);//not really implemented to be done
	while (++vars.x < WIDTH)
	{
		/*  ray dir and dist  */
		vars.camera_x = 2 * vars.x / (double)WIDTH - 1;
		vars.ray_dir_x = g->dir_x + vars.plane_x * camera_x;
	}

}