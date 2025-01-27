#include "cube.h"

double	w_key_x(t_data *c)
{
	if (dist_to_wall(c, c->player_dx, 0) > 0.5)
		return (c->player_x + c->player_dx * 0.08);
	return (c->player_x);
}

double	w_key_y(t_data *c)
{
	if (dist_to_wall(c, 0, c->player_dy) > 0.5)
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

