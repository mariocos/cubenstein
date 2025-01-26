
#include "cube.h"
#include <math.h>


int	close_handler(t_data *f)
{
	mlx_destroy_image(f->mlx_connection, f->img.img_ptr);
	mlx_destroy_window(f->mlx_connection, f->mlx_window);
	mlx_destroy_display(f->mlx_connection);
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

double	w_key_x(t_data *c)
{
	double	new_x_value;
	int		map_x, map_y;

	new_x_value = c->player_x + c->player_dx * 0.08;
	map_x = (int)(new_x_value + 0.1);
	map_y = (int)c->player_y;
	if (worldMap[map_y][map_x] == 1)
		return (c->player_x);
	return (new_x_value);
}

double	w_key_y(t_data *c)
{
	double	new_y_value;
	int		map_x, map_y;

	new_y_value = c->player_y + c->player_dy * 0.08;
	map_y = (int)(new_y_value + 0.1);
	map_x = (int)c->player_x;
	if (worldMap[map_y][map_x] == 1)
		return (c->player_y);
	return (new_y_value);
}

double	s_key_x(t_data *c)
{
	double	new_x_value;
	int		map_x, map_y;

	new_x_value = c->player_x - c->player_dx * 0.08;
	map_x = (int)(new_x_value - 0.1);
	map_y = (int)c->player_y;
	if (worldMap[map_y][map_x] == 1)
		return (c->player_x);
	return (new_x_value);
}

double	s_key_y(t_data *c)
{
	double	new_y_value;
	int		map_x, map_y;

	new_y_value = c->player_y - c->player_dy * 0.08;
	map_y = (int)(new_y_value - 0.1);
	map_x = (int)c->player_x;
	if (worldMap[map_y][map_x] == 1)
		return (c->player_y);
	return (new_y_value);
}

double	d_key_x(t_data *c)
{
	double	new_x_value;
	double	strafe_x;
	int		map_x, map_y;

	strafe_x = c->player_dy;
	new_x_value = c->player_x - strafe_x * 0.08;
	map_x = (int)(new_x_value - 0.1);
	map_y = (int)c->player_y;
	if (worldMap[map_y][map_x] == 1)
		return (c->player_x);
	return (new_x_value);
}

double	d_key_y(t_data *c)
{
	double	new_y_value;
	double	strafe_y;
	int		map_x, map_y;

	strafe_y = -c->player_dx;
	new_y_value = c->player_y - strafe_y * 0.08;
	map_y = (int)(new_y_value - 0.1);
	map_x = (int)c->player_x;
	if (worldMap[map_y][map_x] == 1)
		return (c->player_y);
	return (new_y_value);
}

double	a_key_x(t_data *c)
{
	double	new_x_value;
	double	strafe_x;
	int		map_x, map_y;

	strafe_x = c->player_dy;
	new_x_value = c->player_x + strafe_x * 0.08;
	map_x = (int)(new_x_value + 0.1);
	map_y = (int)c->player_y;
	if (worldMap[map_y][map_x] == 1)
		return (c->player_x);
	return (new_x_value);
}

double	a_key_y(t_data *c)
{
	double	new_y_value;
	double	strafe_y;
	int		map_x, map_y;

	strafe_y = -c->player_dx;
	new_y_value = c->player_y + strafe_y * 0.08;
	map_y = (int)(new_y_value + 0.1);
	map_x = (int)c->player_x;
	if (worldMap[map_y][map_x] == 1)
		return (c->player_y);
	return (new_y_value);
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
		rotation(c, -0.009);
	// Rotate right (Right arrow key)
	if (c->keys[5] == 1)
		rotation(c, 0.009);
}

