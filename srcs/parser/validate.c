#include "../cube.h"

int	count_chars(char **str)
{
	t_chars	c;
	int	i;
	int j;

	/*change to init */
	c.e_count = 0;
	c.n_count = 0;
	c.s_count = 0;
	c.w_count = 0;

	i = -1;
	j = -1;
	while (str[++i] != NULL)
	{
		j = -1;
		while (str[i][++j] != '\0')
		{
			if (str[i][j] == 'E')
				c.e_count++;
			if (str[i][j] == 'W')
				c.w_count++;
			if (str[i][j] == 'S')
				c.s_count++;
			if (str[i][j] == 'N')
				c.n_count++;
			if (!is_map_char(str[i][j]))
				return (-1);
		}
	}
	if (c.e_count + c.s_count + c.w_count + c.n_count != 1)
		return (-1);
	return (1);
}

void	get_map_dupe(t_parse *p)
{
	int	i;

	i = 0;
	p->map_fl = malloc((p->height + 1) * sizeof(void*));
	while (i < p->height)
	{
		p->map_fl[i] = malloc(p->max_len + 1);
		ft_memset(p->map_fl[i], 'n', p->max_len);
		p->map_fl[i][p->max_len] = '\0';
		i++;
	}
	print_double_array(p->map_fl);
}

int	index_out_of_range(t_parse *p, int x, int y)
{
	if (y < 0 || x < 0)
		return (1);
	if (!p->map[y] || !p->map[y][x])
		return (1);
	return (0);
}

/* recursive part*/
int	flood_fill(t_parse *p, int x, int y)
{
	printf("checking [%c]\n", p->map[y][x]);
	/* check if out of range */
	if (index_out_of_range(p, x, y) || p->map[y][x] == '9')
		return (0);
	if (!flood_fill(p, x + 1, y))
		return (0);
	if (!flood_fill(p, x - 1, y))
		return (0);
	if (!flood_fill(p, x, y + 1))
		return (0);
	if (!flood_fill(p, x, y - 1))
		return (0);
	return (1);
}

int	flood_loop(t_parse *p)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (p->map[i] != NULL)
	{
		j = 0;
		while (p->map[i][j] != '\0')
		{
			if (p->map[i][j] == '0' && flood_fill(p, j, i) == 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_parse *p)
{
	if (count_chars(p->map) < 0)
		return (-1); // change to exit protocoll
	/* flood fill ??????? */
	if (flood_loop(p) < 0)
	{
		printf("floodable map\n");
		return (-1);
	}
	printf("made it out of flooder\n");
	return (1);
}