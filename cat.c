#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "cube.h" // Include your MLX header

#define WIDTH 640
#define HEIGHT 480
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define YELLOW 0xFFFF00
#define WHITE 0xFFFFFF

int worldMap[24][24] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void init_ray(t_data *c, t_vars *v) {
	v->camera_x = (2.0 * c->rx / (double)WIDTH) - 1.0;
	v->ray_dx = c->player_dx + c->plane_x * v->camera_x;
	v->ray_dy = c->player_dy + c->plane_y * v->camera_x;
	v->map_x = (int)(c->player_x) >> 6; // Divide by 64 (logical shift)
	v->map_y = (int)(c->player_y) >> 6;
	v->r_delta_dist_x = fabs(1 / (v->ray_dx + 1e-6)); // Avoid division by zero
	v->r_delta_dist_y = fabs(1 / (v->ray_dy + 1e-6));
}

void set_ray_step(t_data *c, t_vars *v) {
	if (v->ray_dx < 0) {
		v->ray_x_step = -1;
		v->r_dist_x = (c->player_x - (v->map_x << 6)) * v->r_delta_dist_x;
	} else {
		v->ray_x_step = 1;
		v->r_dist_x = ((v->map_x + 1) << 6 - c->player_x) * v->r_delta_dist_x;
	}
	if (v->ray_dy < 0) {
		v->ray_y_step = -1;
		v->r_dist_y = (c->player_y - (v->map_y << 6)) * v->r_delta_dist_y;
	} else {
		v->ray_y_step = 1;
		v->r_dist_y = ((v->map_y + 1) << 6 - c->player_y) * v->r_delta_dist_y;
	}
}

void hit_ray_into_wall(t_data *c, t_vars *v) {
	while (v->map_x >= 0 && v->map_x < 24 && v->map_y >= 0 && v->map_y < 24) {
		if (v->r_dist_x < v->r_dist_y) {
			v->r_dist_x += v->r_delta_dist_x;
			v->map_x += v->ray_x_step;
			v->side = 0;
		} else {
			v->r_dist_y += v->r_delta_dist_y;
			v->map_y += v->ray_y_step;
			v->side = 1;
		}
		if (worldMap[v->map_x][v->map_y] > 0)
			break;
	}
}

void render_cast(t_data *c, t_vars *v) {
	t_draw vars;
	if (v->side == 0)
		vars.wall_dist = (v->map_x - c->player_x + (1 - v->ray_x_step) / 2) / v->ray_dx;
	else
		vars.wall_dist = (v->map_y - c->player_y + (1 - v->ray_y_step) / 2) / v->ray_dy;

	vars.line_height = (int)(HEIGHT / vars.wall_dist);
	vars.draw_start = -vars.line_height / 2 + HEIGHT / 2;
	if (vars.draw_start < 0)
		vars.draw_start = 0;
	vars.draw_end = vars.line_height / 2 + HEIGHT / 2;
	if (vars.draw_end >= HEIGHT)
		vars.draw_end = HEIGHT - 1;

	int colors[] = {RED, GREEN, BLUE, YELLOW, WHITE};
	int wall_color = colors[worldMap[v->map_x][v->map_y] % 5];

	for (int y = vars.draw_start; y <= vars.draw_end; y++) {
		ft_pixel_put(c->rx, y, &c->img, wall_color);
	}
}

int hook_loop(t_data *cube) {
	t_vars v;

	for (cube->rx = 0; cube->rx < WIDTH; cube->rx++) {
		init_ray(cube, &v);
		set_ray_step(cube, &v);
		hit_ray_into_wall(cube, &v);
		render_cast(cube, &v);
	}
	mlx_put_image_to_window(cube->mlx_connection, cube->mlx_window, cube->img.ptr, 0, 0);
	return (0);
}

int main() {
	t_data cube;

	// Initialize player position and direction
	cube.player_x = 12 * 64; // Initial position (22, 12)
	cube.player_y = 12 * 64;
	cube.player_dx = -1.0;   // Initial direction vector
	cube.player_dy = 0.0;
	cube.plane_x = 0.0;      // Camera plane perpendicular to direction
	cube.plane_y = 0.66;

	// Hook loop and start rendering
	mlx_loop_hook(cube.mlx_connection, hook_loop, &cube);
	mlx_loop(cube.mlx_connection);

	// Cleanup on exit
	return (EXIT_SUCCESS);
}
