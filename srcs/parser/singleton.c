#include "../cube.h"

t_parse	*p_call(void)
{
	static t_parse	parse;

	return (&parse);
}

void	parse_init(void)
{
	t_parse *parse;

	parse = p_call();
	parse->c_color = 0;
	parse->f_color = 0;
	parse->scene_colors = NULL;
	parse->wall_textures = NULL;
	parse->height = 0;
	parse->max_len = 0;
}