#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "minilibx-linux/mlx.h"
# include "X11/X.h"
# include "X11/keysym.h"

//changeables
# define WIDTH 800
# define HEIGHT 800


# define BLACK       0x000000  // RGB(0, 0, 0)
# define WHITE       0xFFFFFF  // RGB(255, 255, 255)
# define RED         0xFF0000  // RGB(255, 0, 0)
# define GREEN       0x00FF00  // RGB(0, 255, 0)
# define BLUE        0x0000FF  // RGB(0, 0, 255)

typedef struct s_img
{
	void	*img_ptr;
	void	*pixels;
	int		bpp;
	int		endian;
	int		line_len;
}				t_img;

typedef struct s_data
{
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
    int     player_x;
    int     player_y;
    int     player_radius;
}	t_data;

/*   init    */
void	events_init(t_data *f);
void	cube_init(t_data *cube);
void	data_init(t_data *d);


/*    hooks  */
int	close_handler(t_data *f);
int	key_handler(int keysym, t_data *f);


/*    rendering    */
void	ft_pixel_put(int x, int y, t_img *img, int color);
void	floor_render(t_data *f);
void draw_circle(t_data *game, int x_c, int y_c, int radius, int color);
int handle_input(int keycode, t_data *game);

extern int worldMap[24][24];


#endif