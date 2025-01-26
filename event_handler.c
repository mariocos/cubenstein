
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
	if (dist_to_wall(c, c->player_dx, 0) > 0.5)
		return (c->player_x + c->player_dx * 0.08);
	return (c->player_x);
}

double	w_key_y(t_data *c)
{
	if (dist_to_wall(c, 0, c->player_y) > 0.5)
		return (c->player_y + c->player_dy * 0.08);
	return (c->player_y);
}

double	s_key_x(t_data *c)
{
	if (dist_to_wall(c, -c->player_dx, 0) > 0.5)
		return (c->player_x - c->player_dx * 0.08);
	return (c->player_x);
}

double	s_key_y(t_data *c)
{
	if (dist_to_wall(c, 0, -c->player_dy) > 0.5)
		return (c->player_y - c->player_dy * 0.08);
	return (c->player_y);
}

double a_key_x(t_data *c)
{
    if (dist_to_wall(c, c->player_dy, 0) > 0.5) // Check distance in strafe direction
        return (c->player_x + c->player_dy * 0.08); // Prevent movement if too close
    return (c->player_x);
}

double a_key_y(t_data *c)
{
    if (dist_to_wall(c, 0, -c->player_dx) > 0.5) // Check distance in strafe direction
        return (c->player_y - c->player_dx * 0.08); // Prevent movement if too close
    return (c->player_y);
}

double d_key_x(t_data *c)
{
    if (dist_to_wall(c, -c->player_dy, 0) > 0.5) // Check distance in strafe direction
        return (c->player_x - c->player_dy * 0.08); // Prevent movement if too close
    return (c->player_x);
}

double d_key_y(t_data *c)
{
    if (dist_to_wall(c, 0, c->player_dx) > 0.5) // Check distance in strafe direction
        return (c->player_y + c->player_dx * 0.08); // Prevent movement if too close
    return (c->player_y);
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

