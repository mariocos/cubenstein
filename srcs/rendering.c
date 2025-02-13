#include "cube.h"
#include <complex.h>

void	ft_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels + offset) = color;
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
                ft_pixel_put(x, y, &game->img, color);
            }
        }
    }
}


void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1) {
        mlx_pixel_put(mlx, win, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}


int	checkmap(int x, int y)
{
	int	new_x = map(x, 0, WIDTH, 0, 24);
	int	new_y = map(y, 0, HEIGHT, 0, 24);
	return(worldMap[new_x][new_y]);
}

void	draw_ray(t_data *f)
{
	float py = f->player_y;
	float px = f->player_x;
	int	r,mx,my,mp,dof;
	float rx,ry,ra,xo,yo;
	ra = f->player_angle;
	for (r = 0; r < 1; r++)
	{
		dof = 0;
		float atan = -1/tan(ra);
		if (ra > PI)//might want to swap to <
		{
			ry = (((int)py>>6)<<6) - 0.0001;
			rx = (py - ry) * atan + px;
			yo = -64;
			xo =- yo*atan;
		}
		if (ra < PI)//might want to swap to <
		{
			ry = (((int)py>>6)<<6) + 64;
			rx = (py - ry) * atan + px;
			yo = +64;
			xo = -yo*atan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof<8)
		{
			mx = map(rx, 0, WIDTH, 0, 24);
			my = map(ry, 0, HEIGHT, 0, 24);
			mp = my * WIDTH + mx;
			(void)mp;
			if (checkmap(mx, mx) == 1)
				dof = 8;
			else
			{
				rx+= xo;
				ry += yo;
				dof +=1;
			}
			draw_line(f->mlx_connection, f->mlx_window, f->player_x, f->player_y, f->player_x + rx * 50, f->player_y + ry * 50, BLUE);
		}
	}

}
