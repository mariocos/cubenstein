#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../minilibx-linux/mlx.h"
# include "../X11/X.h"
# include "../X11/keysym.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//changeables
# define WIDTH 1200
# define HEIGHT 800
# define PI	3.1415


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

typedef struct s_wall
{
	int		text_width;
	int		text_height;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		pixel_index;
	int		color;
}	t_wall;

typedef struct s_data
{
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
	int	keys[8];
	int		rx;
	t_wall	*wall_data;
	t_img	*wall;
    float     player_x;
    float     player_y;
	float	player_dx;
	float	player_dy;
	float	plane_x;
	float	plane_y;
	float	player_angle;
    int     player_radius;

}	t_data;

typedef struct s_vars
{
	/* data */
	double	camera_x;
	double	ray_dx;
	double	ray_dy;
	double	r_dist_x;
	double	r_dist_y;
	double	r_delta_dist_x;
	double	r_delta_dist_y;
	int	ray_x_step;
	int	ray_y_step;
	int	map_x;
	int	map_y;
	int	hmap_x;
	int	hmap_y;
	int	side;
}		t_vars;

typedef	struct s_draw
{
	/* data */
	double	wall_dist;
	int	line_height;
	int	draw_start;
	int	draw_end;
}		t_draw;



/* singletons  */


/*   init    */
void	events_init(t_data *f);
void	cube_init(t_data *cube);
void	data_init(t_data *d);


/*    hooks  */
int	close_handler(t_data *f);
int	key_handler(int keysym, t_data *f);
void	key_read(t_data *c);

/*  colisions  */
double	dist_to_wall(t_data *c, double ray_dx, double ray_dy);

/*    rendering    */
void	ft_pixel_put(int x, int y, t_img *img, int color);
void	floor_render(t_data *f);
void draw_circle(t_data *game, int x_c, int y_c, int radius, int color);
int handle_input(int keycode, t_data *game);
void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color);
void	draw_ray(t_data *f);

/*  keys  */
int	ft_keyrelease(int	keysym, t_data *c);
int	ft_keypress(int	keysym, t_data *c);
void	key_read(t_data *c);
void rotation(t_data *c, float rot);

/* collision movement */
double	a_key_x(t_data *c);
double	a_key_y(t_data *c);
double	d_key_x(t_data *c);
double	d_key_y(t_data *c);
double	w_key_x(t_data *c);
double	w_key_y(t_data *c);
double	s_key_x(t_data *c);
double	s_key_y(t_data *c);

/*raycasting*/
void	set_ray_step(t_data *c, t_vars *v);
void	hit_ray_into_wall(t_data *c, t_vars *v);
void	init_ray(t_data *c, t_vars *v);
void	render_cast(t_data *c, t_vars *v);

/* movement */
void rotation(t_data *c, float rot);

/*  gnl  */
char	*get_next_line(int fd);

/* lib */
char	**ft_split(char const *s, char c);

/*     parsing    */


int map(int x, int in_min, int in_max, int out_min, int out_max);
void load_texture(t_data *c);
void	ft_bzero(void *str, size_t	num);




extern int worldMap[24][24];


#endif
