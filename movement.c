#include "cube.h"

void rotation(t_data *c, float rot)
{
	float old_dir_x;
	float old_plane_x;

	old_dir_x = c->player_dx;
	old_plane_x = c->plane_x;
	/* rotate player */
	c->player_dx = old_dir_x * cos(rot) - c->player_dy * sin(rot);
	c->player_dy = old_dir_x * sin(rot) + c->player_dy * cos(rot);//maybe normalize theese vectors!
	/* rotate plane  */
	c->plane_x = old_plane_x * cos(rot) - c->plane_y * sin(rot);
	c->plane_y = old_plane_x * sin(rot) + c->plane_y * cos(rot);
}
