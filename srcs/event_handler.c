#include "cube.h"

int	close_handler(t_data *f)
{
	int	i;

	i = 4;
	mlx_destroy_image(f->mlx_connection, f->img.img_ptr);
	mlx_destroy_window(f->mlx_connection, f->mlx_window);
	mlx_destroy_display(f->mlx_connection);
	while (--i)
	{
		mlx_destroy_image(f->mlx_connection, f->wall_data[i]->wall->img_ptr);
		free(f->wall_data[i]->wall);
	}
	free(f->mlx_connection);
	exit(1);
	return (-1);
}

int	ft_keypress(int	keysym, t_data *c)
{
	if (keysym == XK_Escape)
		close_handler(c);
	if	(keysym == XK_w)
		c->keys[0] = 1;
	if	(keysym == XK_s)
		c->keys[1] = 1;
	if	(keysym == XK_a)
		c->keys[2] = 1;
	if	(keysym == XK_d)
		c->keys[3] = 1;
	if	(keysym == 65361)
		c->keys[4] = 1;
	if	(keysym == 65363)
		c->keys[5] = 1;
	return (1);
}

int	ft_keyrelease(int	keysym, t_data *c)
{
	if (keysym == XK_Escape)
		close_handler(c);
	if	(keysym == XK_w)
		c->keys[0] = 0;
	if	(keysym == XK_s)
		c->keys[1] = 0;
	if	(keysym == XK_a)
		c->keys[2] = 0;
	if	(keysym == XK_d)
		c->keys[3] = 0;
	if	(keysym == 65361)
		c->keys[4] = 0;
	if	(keysym == 65363)
		c->keys[5] = 0;
	return (1);
}

void	key_read(t_data *c)
{
	if (c->keys[0] == 1)//w key
	{
		c->player_y = w_key_y(c);
		c->player_x = w_key_x(c);
	}
	else if (c->keys[1] == 1)//s key
	{
		c->player_y = s_key_y(c);
		c->player_x = s_key_x(c);
	}
	if (c->keys[2] == 1)//A key
	{
		c->player_y = a_key_y(c);
		c->player_x = a_key_x(c);
	}
	else if (c->keys[3] == 1)//d key
	{
		c->player_y = d_key_y(c);
		c->player_x = d_key_x(c);
	}
	// Rotate left (Left arrow key)
	if (c->keys[4] == 1)
		rotation(c, -0.01);
	// Rotate right (Right arrow key)
	if (c->keys[5] == 1)
		rotation(c, 0.01);
}
