#include "cube.h"

void	init_ray(t_data *c, t_vars *v)
{
	v->camera_x = c->rx * 2 / (double)WIDTH - 1;//
	//printf("camera x is %f\n", v->camera_x);
	v->ray_dx = c->player_dx + c->plane_x * v->camera_x;
	v->ray_dy = c->player_dy + c->plane_y * v->camera_x;//problem might be here
	//printf("ray dx %f and dy %f\n", v->ray_dx, v->ray_dy);
	v->map_x = (int)c->player_x;
	v->map_y = (int)c->player_y;
	//v->map_x = v->map_x >> 6;
	//v->map_y = v->map_y >> 6;
	v->r_delta_dist_x = fabs(1 / v->ray_dx);//has problem for values near zero
	v->r_delta_dist_y = fabs(1 / v->ray_dy);
	//printf("sied=1 rdistx %f and rdeltax %f\n", v->r_dist_x, v->r_delta_dist_x);
}


void	set_ray_step(t_data *c, t_vars *v)
{
	if (v->ray_dx < 0)
	{
		v->ray_x_step = -1;
		v->r_dist_x = (c->player_x - v->map_x) * v->r_delta_dist_x;
	}
	else
	{
		v->ray_x_step = 1;
		v->r_dist_x = (v->map_x + 1.0 - c->player_x) * v->r_delta_dist_x;
	}
	if (v->ray_dy < 0)
	{
		v->ray_y_step = -1;
		v->r_dist_y = (c->player_y - v->map_y) * v->r_delta_dist_y;
	}
	else
	{
		v->ray_y_step = 1;
		v->r_dist_y = (v->map_y + 1.0 - c->player_y) * v->r_delta_dist_y;
	}
	//printf("dist set x %f and y %f\n", v->r_dist_x, v->r_dist_y);
}

void	hit_ray_into_wall(t_data *c, t_vars *v)
{
	//printf("ray step x %d and y %d\n", v->ray_x_step, v->ray_y_step);
	(void)c;
	v->side = 0;
	while (1)
	{
		if (v->r_dist_x < v->r_dist_y)
		{
			v->r_dist_x += v->r_delta_dist_x;
			//printf("after stepx %f\n", v->r_dist_x);
			v->map_x += v->ray_x_step;
			v->side = 0;
		}
		else
		{
			v->r_dist_y += v->r_delta_dist_y;
			//printf("after step %f\n", v->r_dist_y);
			v->map_y += v->ray_y_step;
			v->side = 1;
		}
		if (worldMap[v->map_y][v->map_x] == 1)
		{
			break ;
		}
	}
}


void	render_cast(t_data *c, t_vars *v)
{
	t_draw	vars;

	//printf("map  y %d and x %d player x  %f and y %f \n", v->map_x, v->map_y, c->player_x, c->player_y);
	//printf("ray sizes %f and %f\n", v->r_dist_x, v->r_dist_y);
	if (v->side == 0)
		vars.wall_dist = (v->map_x - c->player_x + (1 - v->ray_x_step) / 2) / v->ray_dx;
	else
			vars.wall_dist = (v->map_y - c->player_y + (1 - v->ray_y_step) / 2) / v->ray_dy;
	//printf("wall dist %f and side %d\n", vars.wall_dist, v->side);
	vars.line_height = (int)(HEIGHT / vars.wall_dist);
	//printf("var line height is %d\n", vars.line_height);
	
	// Calculate start and end positions for the wall slice
	vars.draw_start = -vars.line_height / 2 + HEIGHT / 2;
	if (vars.draw_start < 0)
		vars.draw_start = 0;

	vars.draw_end = vars.line_height / 2 + HEIGHT / 2;
	if (vars.draw_end >= HEIGHT)
		vars.draw_end = HEIGHT - 1;

	// Determine color based on side
	int wall_color;
	if (v->side == 0)
		wall_color = RED; // Red for x-wall
	else
		wall_color = GREEN; // Green for y-wall

	// Draw the vertical line representing the wall slice
	for (int y = vars.draw_start; y <= vars.draw_end; y++)
	{
		ft_pixel_put(c->rx, y, &c->img, wall_color);
	}
	//exit(1);
}