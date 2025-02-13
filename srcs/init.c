#include "cube.h"

static void	free_error(void)
{
	printf("a problem in the lib has occurred\n");
	exit(1);
}

void	cube_init(t_data *cube)
{
	cube->mlx_connection = mlx_init();
	if (!cube->mlx_connection)
		free_error();
	cube->mlx_window = mlx_new_window(cube->mlx_connection,
			WIDTH, HEIGHT, cube->name);
	if (!cube->mlx_window)
	{
		mlx_destroy_display(cube->mlx_connection);
		free (cube->mlx_connection);
		free_error();
	}
	cube->img.img_ptr = mlx_new_image(cube->mlx_connection,
			WIDTH, HEIGHT);
	if (!cube->img.img_ptr)
	{
		mlx_destroy_window(cube->mlx_connection, cube->mlx_window);
		mlx_destroy_display(cube->mlx_connection);
		free (cube->mlx_connection);
		free_error();
	}
	cube->img.pixels = mlx_get_data_addr(cube->img.img_ptr,
			&cube->img.bpp, &cube->img.line_len, &cube->img.endian);
	load_texture_1(cube);
	load_texture_2(cube);
	load_texture_3(cube);
	load_texture_4(cube);
	//printf("abrir....\n");
	//cube->wall->wall_texture = mlx_xpm_file_to_image(cube->mlx_connection, "srcs/wall.xpm", &cube->wall->tex_width, &cube->wall->tex_height);
	//if (!cube->wall->wall_texture)
	//{
    //    printf("Erro ao carregar a textura!\n");
    //    exit(1);
    //}
    //cube->wall->wall_pixels = mlx_get_data_addr(cube->wall->wall_texture, &cube->img.bpp, &cube->img.line_len, &cube->img.endian);
	//events_init(cube);//trying to make it work a diferent way
}


/* void	events_init(t_data *f)
{
	mlx_hook(f->mlx_window,
		KeyPress,
		KeyPressMask,
		key_handler,
		f);
 	mlx_hook(f->mlx_window,
		ButtonPress,
		ButtonPressMask,
		mouse_handler,
		f); //unused rn
	mlx_hook(f->mlx_window,
		DestroyNotify,
		StructureNotifyMask,
		close_handler,
		f);
} */
