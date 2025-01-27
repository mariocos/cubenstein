#include "cube.h"

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

