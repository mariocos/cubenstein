
#include "cube.h"

int	close_handler(t_data *f)
{
	mlx_destroy_image(f->mlx_connection, f->img.img_ptr);
	mlx_destroy_window(f->mlx_connection, f->mlx_window);
	mlx_destroy_display(f->mlx_connection);
	free(f->mlx_connection);
	exit(1);
	return (-1);
}

int	key_handler(int keysym, t_data *f)
{
	printf("key code %d\n", keysym);
	if (keysym == XK_Escape)
		close_handler(f);
    else if (keysym == 119) // W key
		f->player_y -= 5;
    else if (keysym == 115) // S key
		f->player_y += 5;
    else if (keysym == 97) // A key
		f->player_x -= 5;
    else if (keysym == 100) // D key
		f->player_x += 5;

	floor_render(f);
	draw_circle(f, f->player_x, f->player_y, 15, RED);
	return (-1);
}