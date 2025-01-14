#include "cube.h"

void	ft_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels + offset) = color;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void	handle_pixel(int x, int y, t_data *s)
{
	int	new_x;
	int new_y;

	new_x = map(x, 0, WIDTH, 0, 24);
	new_y = map(y, 0, HEIGHT, 0, 24);
	if (worldMap[new_x][new_y] == 1)
		ft_pixel_put(x, y, &s->img, RED);
	else if (worldMap[new_x % 24][new_y % 24] == 2)
		ft_pixel_put(x, y, &s->img, GREEN);
	else
		ft_pixel_put(x, y, &s->img, BLUE);



/* 
	if (y < HEIGHT / 2)
		ft_pixel_put(x, y, &s->img, BLACK);
	else
		ft_pixel_put(x, y, &s->img, GREEN); */
}

void draw_circle(t_data *game, int x_c, int y_c, int radius, int color) {
    for (int y = y_c - radius; y <= y_c + radius; y++) {
        for (int x = x_c - radius; x <= x_c + radius; x++) {
            if ((x - x_c) * (x - x_c) + (y - y_c) * (y - y_c) <= radius * radius) {
                mlx_pixel_put(game->mlx_connection, game->mlx_window, x, y, color);
            }
        }
    }
}

void	floor_render(t_data *f)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			handle_pixel(x, y, f);
	}
//    draw_circle(f, f->player_x, f->player_y, f->player_radius, 0x00FF00);
	mlx_put_image_to_window(f->mlx_connection,
		f->mlx_window, f->img.img_ptr, 0, 0);
}