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

int map(int x, int in_min, int in_max, int out_min, int out_max)
{
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//void	render_cast(t_data *c, t_vars *v)
//{
//	t_draw	vars;
//	t_img    wall;
//
//	wall.img_ptr = mlx_xpm_file_to_image(c->mlx_connection, "srcs/wall.xpm", &wall.line_len, &wall.endian);
//	if (!wall.img_ptr)
//	{
//        printf("Erro ao carregar a textura!\n");
//        exit(1);
//    }
//	wall.pixels = mlx_get_data_addr(wall.img_ptr, &wall.bpp, &wall.line_len, &wall.endian);
//	//mlx_put_image_to_window (c->mlx_connection, c->mlx_window, wall.img_ptr, 0, 0);
//	//printf("map  y %d and x %d player x  %f and y %f \n", v->map_x, v->map_y, c->player_x, c->player_y);
//	//printf("ray sizes %f and %f\n", v->r_dist_x, v->r_dist_y);
//	if (v->side == 0)
//		vars.wall_dist = (v->map_x - c->player_x + (1 - v->ray_x_step) / 2) / v->ray_dx;
//	else
//		vars.wall_dist = (v->map_y - c->player_y + (1 - v->ray_y_step) / 2) / v->ray_dy;
//	//printf("wall dist %f and side %d\n", vars.wall_dist, v->side);
//	vars.line_height = (int)(HEIGHT / vars.wall_dist);
//	//printf("var line height is %d\n", vars.line_height);
//
//	// Calculate start and end positions for the wall slice
//	vars.draw_start = -vars.line_height / 2 + HEIGHT / 2;
//	if (vars.draw_start < 0)
//		vars.draw_start = 0;
//
//	vars.draw_end = vars.line_height / 2 + HEIGHT / 2;
//	if (vars.draw_end >= HEIGHT)
//		vars.draw_end = HEIGHT - 1;
//
//	// Determine color based on side
//	int wall_color;
//	if (v->side == 0)
//		wall_color = RED; // Red for x-wall
//	else
//		wall_color = GREEN; // Green for y-wall
//	//wall_color = mlx_xpm_to_image(c->mlx_connection, "wall.xmp", vars.draw_start, vars.draw_end);
//
//	//mlx_xpm_file_to_image(c->mlx_connection, "wall.xmp", &vars.draw_start, &vars.draw_end);
//	//mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian)
//	// Draw the vertical line representing the wall slice
//	for (int y = vars.draw_start; y <= vars.draw_end; y++)
//	{
//		ft_pixel_put(c->rx, y, &c->img, wall_color);
//	}
//	//exit(1);
//}

void clear_screen(t_data *c)
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            int color = (y < HEIGHT / 2) ? 0x87CEEB : 0x654321; // Céu azul e chão marrom
            ft_pixel_put(x, y, &c->img, color);
        }
    }
}

void load_texture(t_data *c)
{
    t_img *wall;

    wall = malloc(sizeof(t_img));
    c->wall = wall;
    c->wall->img_ptr = mlx_xpm_file_to_image(c->mlx_connection, "srcs/wall.xpm", &c->wall->line_len, &c->wall->endian);
    if (!c->wall->img_ptr)
    {
        printf("Erro ao carregar a textura!\n");
        exit(1);
    }
    c->wall->pixels = mlx_get_data_addr(c->wall->img_ptr, &c->wall->bpp, &c->wall->line_len, &c->wall->endian);
}

void render_cast(t_data *c, t_vars *v)
{
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
    c->wall_data->text_width = 256;
    c->wall_data->text_height = 256;
    if (v->side == 0 && v->ray_dx > 0)
        c->wall_data->wall_x = c->player_y + vars.wall_dist * v->ray_dy;
    else if (v->side == 1 && v->ray_dy < 0)
        c->wall_data->wall_x = c->player_x + vars.wall_dist * v->ray_dx;
    else if (v->side == 0 && v->ray_dx < 0)
        c->wall_data->wall_x = c->player_y + vars.wall_dist * v->ray_dy;
    else if (v->side == 1 && v->ray_dy > 0)
        c->wall_data->wall_x = c->player_x + vars.wall_dist * v->ray_dx;
    c->wall_data->wall_x -= floor(c->wall_data->wall_x);

    c->wall_data->tex_x = (int)(c->wall_data->wall_x * (double)c->wall_data->text_width);
    if ((v->side == 0 && v->ray_dx > 0) || (v->side == 1 && v->ray_dy < 0))
        c->wall_data->tex_x = c->wall_data->text_width - c->wall_data->tex_x - 1;
    else if ((v->side == 1 && v->ray_dy < 0) || (v->side == 0 && v->ray_dx > 0))
    	c->wall_data->tex_x = c->wall_data->text_width - c->wall_data->tex_x - 1;
    c->wall_data->step = (double)c->wall_data->text_height / vars.line_height;
    c->wall_data->tex_pos = (vars.draw_start - HEIGHT / 2 + vars.line_height / 2) * c->wall_data->step;
    for (int y = vars.draw_start; y <= vars.draw_end; y++)
    {
        c->wall_data->tex_y = (int)c->wall_data->tex_pos & (c->wall_data->text_height - 1);
        c->wall_data->tex_pos += c->wall_data->step;

        c->wall_data->pixel_index = (c->wall_data->tex_y * c->wall->line_len) + (c->wall_data->tex_x * (c->wall->bpp / 8));
        c->wall_data->color = *(int *)(c->wall->pixels + c->wall_data->pixel_index);

        ft_pixel_put(c->rx, y, &c->img, c->wall_data->color);
    }
}
