#include "cube.h"

int worldMap[24][24]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,1,1,1,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

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

void	floor_render(t_data	*c)
{
	int	x = -1;
	int y = -1;

	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			if (y < (HEIGHT / 2))
				ft_pixel_put(x, y, &c->img, BLACK);
			else
				ft_pixel_put(x, y, &c->img, BLUE);
		}
	}
}


int	hook_loop(t_data *c)
{
	t_vars	vars;

	printf("pos x %f and y %f\n", c->player_x, c->player_y);
	mlx_clear_window(c->mlx_connection, c->mlx_window);
	key_read(c);
	floor_render(c);
	//printf("player x %f and y %f\n", c->player_x, c->player_y);
//	draw_circle(c, c->player_x, c->player_y, 10, RED);
//	draw_circle(c, c->player_x + c->player_dx * 4, c->player_y + c->player_dy * 4, 5, BLUE);
	/* ray casterrrrr*/
	c->rx = 0;//changed this to start on 1 to
	while (c->rx < WIDTH)
	{
		/*set ray out*/
		init_ray(c, &vars);
		/* get ray dist */
		set_ray_step(c, &vars);
		/*   hit??   */
		hit_ray_into_wall(c, &vars);
		/*  draw ray text?*/
		render_cast(c, &vars);
		/*  repeat?  */
		c->rx++;
	}
	mlx_put_image_to_window(c->mlx_connection, c->mlx_window, c->img.img_ptr, 0, 0);
	return (1);

}

void rotation(t_data *c, float rot)
{
	float old_dir_x;
	float old_plane_x;

	old_dir_x = c->player_dx;
	old_plane_x = c->plane_x;
	/* rotate player */
	c->player_dx = old_dir_x * cos(rot) - c->player_dy * sin(rot);
	c->player_dy = old_dir_x * sin(rot) + c->player_dy * cos(rot);//maybe normalize theese vectors!
	/* rotate plane  */
	c->plane_x = old_plane_x * cos(rot) - c->plane_y * sin(rot);
	c->plane_y = old_plane_x * sin(rot) + c->plane_y * cos(rot);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_data	cube;



	cube.keys[0] = 0;
	cube.keys[1] = 0;
	cube.keys[2] = 0;
	cube.keys[3] = 0;
	cube.keys[4] = 0;
	cube.keys[5] = 0;
	cube.keys[6] = 0;
	cube.player_x = 12;
	cube.player_y = 12;
	cube.player_radius = 30;
	cube.player_dx = 1;
	cube.player_dy = 0;
	cube.plane_x = 0;
	cube.plane_y = 0.66;
	cube.name = "cubo";


	//data_init(&cube);
	cube_init(&cube);

	mlx_hook(cube.mlx_window, KeyPress, KeyPressMask, ft_keypress, &cube);
	mlx_hook(cube.mlx_window, KeyRelease, KeyReleaseMask, ft_keyrelease, &cube);
	mlx_loop_hook(cube.mlx_connection, hook_loop, &cube);
	//mlx_key_hook(cube.mlx_window, key_read, &cube);
	mlx_loop(cube.mlx_connection);
	return (0);
}
