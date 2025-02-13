#include "cube.h"

int worldMap[24][24]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,3,0,3,0,3,0,0,0,1},
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

	mlx_clear_window(c->mlx_connection, c->mlx_window);
	key_read(c);
	floor_render(c);
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
		c->rx++;
	}
	mlx_put_image_to_window(c->mlx_connection, c->mlx_window, c->img.img_ptr, 0, 0);
	return (1);

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


	data_init(&cube);
	cube_init(&cube);

	mlx_hook(cube.mlx_window, KeyPress, KeyPressMask, ft_keypress, &cube);
	mlx_hook(cube.mlx_window, KeyRelease, KeyReleaseMask, ft_keyrelease, &cube);
	mlx_loop_hook(cube.mlx_connection, hook_loop, &cube);
	//mlx_key_hook(cube.mlx_window, key_read, &cube);
	mlx_loop(cube.mlx_connection);

//	mlx_destroy_image(cube.mlx_connection, cube.wall);
	return (0);
}
