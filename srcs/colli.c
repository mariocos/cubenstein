#include "cube.h"

void	init_wall_ray(t_data *c, double ray_dx, double ray_dy, t_vars *v)
{
	v->ray_dx = ray_dx;
	v->ray_dy = ray_dy;
	v->map_x = (int)c->player_x;
	v->map_y = (int)c->player_y;
	v->r_delta_dist_x = fabs(1 / v->ray_dx);
	v->r_delta_dist_y = fabs(1 / v->ray_dy);
}

double	dist_to_wall(t_data *c, double ray_dx, double ray_dy)
{
	t_vars	ray;
	double	wall_dist;

	/* should be the same as the renderer */
	init_wall_ray(c, ray_dx, ray_dy, &ray);
		/* get ray dist */
	set_ray_step(c, &ray);
		/*   hit??   */
	hit_ray_into_wall(c, &ray);
	if (ray.side == 0)
		wall_dist = ray.r_dist_x - ray.r_delta_dist_x;
	else
		wall_dist = ray.r_dist_y - ray.r_delta_dist_y;
	return (wall_dist);
}