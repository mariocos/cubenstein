
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


void	key_read(t_data *c)
{
	double strafe_x, strafe_y, help;

	(void)help;
	if (c->keys[0] == 1)//w key
	{
		c->player_y += c->player_dy * 0.01;
		c->player_x += c->player_dx * 0.01; 
	}
	else if (c->keys[1] == 1)//s key
	{
		c->player_y -= c->player_dy * 0.01;
		c->player_x -= c->player_dx * 0.01; 
	}
	if (c->keys[2] == 1)//A key
	{
		strafe_x = c->player_dy; // Perpendicular to player_dx/player_dy
		strafe_y = -c->player_dx;
		c->player_y += strafe_y * 0.01;
		c->player_x += strafe_x * 0.01; 
	}
	else if (c->keys[3] == 1)//d key
	{
		strafe_x = -c->player_dy; // Perpendicular to player_dx/player_dy
		strafe_y = c->player_dx;
		c->player_y += strafe_y * 0.01;
		c->player_x += strafe_x * 0.01; 
	}
	// Rotate left (Left arrow key)
	if (c->keys[4] == 1)
		rotation(c, -0.009);
	// Rotate right (Right arrow key)
	if (c->keys[5] == 1)
		rotation(c, 0.009);
}

