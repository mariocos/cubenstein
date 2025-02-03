#include "../cube.h"

int	call_error(void)
{
	write(2, "please call this program with a valid map name only\n", 52);
	return (-1);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

int	check_file_name(char *str)//not tested yet since i dont have the texture files
{
	int	len;

	len = ft_strlen(str);
	if (len < 5)//so it has the ".cub" (4 chars) and a valid filename (atleast one character).
		return (-1);
	if (str[len - 1] != 'b' || str[len - 2] != 'u' || str[len -3] != 'c' || str[len - 4] != '.')
		return (-1);
	return (1);
}

int	bad_map_perms(char *str)
{
	(void)str;//could be used to print the file name if not just remove it from params
	write(2, "please use a map i can open\n", 28);
	return (-1);
}

int	parse_texture_paths(t_parse *p)//this function leaks because im not sure where im gonna free yet
{
	char	*str[5];//for the 4 lines and null
	int	i = -1;

	str[0] = get_next_line(p->fd);//put this in a separet function
	str[1] = get_next_line(p->fd);
	str[2] = get_next_line(p->fd);
	str[3] = get_next_line(p->fd);
	str[4] = NULL;
	/* basic length check and .xpm check */
	print_double_array(str);
	while (++i < 4)
	{
		if (ft_strlen(str[i]) < 4)//needs to have the direction 2 chars a space 1 char the / for the path atleast
		{
			return (-1);//change to return with free or put this all in a struct and free at the end
		}
	}
	i = -1;
	/* checking perms so xpm_to_image works *///still need the textures to do this part
//	while (++i < 4)
//	{
//		if (check_file_name(str[i] + 3) < 0)// add check for the beggining letters too
//			return (-1);
//	}
	return(1);//i dont know what else to check about the xpm files
}

/* helper function */

int	ft_isdigit_string(char *str)
{
	int	i;

	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	small_atoi(char *nptr)
{
	long	result;
	int		i;
	int		hold;

	result = 0;
	i = 0;
	if (!ft_isdigit_string(nptr))
		return (-1);//change to exit protocoll
	while (nptr[i] <= '9' && nptr[i] >= '0' && result < 256)
	{
		hold = nptr[i] - 48;
		result = (result * 10) + hold;
		i++;
	}
	if (result > 255)
		return (-1);//change to exit protocoll
	return (result);
}

int get_hex(char **strs)// i love bitshitting
{
    unsigned int ret = 0;

	if (!strs || !strs[0] || !strs[1] || !strs[2])
		return (-1);
	ret += small_atoi(strs[0]) << 16;//Red
	ret += small_atoi(strs[1]) << 8;//Green
	ret += small_atoi(strs[2]);//Blue
	return ret;
}

int parse_ceiling_and_floor(t_parse *p)
{
	char *space_check;
	char *str[3];//to be added to struct with value of the color
	char	**c_values;
	char	**f_values;

	space_check = get_next_line(p->fd);
	if (ft_strcmp(space_check, "\n") != 0)//remember to check if strcmp is prepped for nulls
		return (-1);
	str[0] = get_next_line(p->fd);
	str[1] = get_next_line(p->fd);
	str[2] = NULL;
	/* check the F and C and space */
	if (ft_strlen(str[0]) < 8 && str[0][0] != 'F' && str[0][1] != ' ')//needs to be checked if 8 or 7 cus of newline
		return(-1);
	if (ft_strlen(str[1]) < 8 && str[1][0] != 'C' && str[1][1] != ' ')//needs to be checked if 8 or 7 cus of newline
		return (-1);
	/* split "," to get 3 ints 0-255 add them in hex */
	c_values = ft_split(str[0] + 2, ',');
	f_values = ft_split(str[1] + 2, ',');
	p->c_color = get_hex(c_values);
	p->f_color = get_hex(f_values);
	if (p->c_color < 0 || p->f_color < 0)
		return (-1);
	return(1);
}

int get_map_dimensions(t_parse *p)
{
	char	*space_check;
	char	*line;
	int		help;

	space_check = get_next_line(p->fd);//separate this into a function that receives fd and checks and frees the string
	if (ft_strcmp(space_check, "\n") != 0)//remember to check if strcmp is prepped for nulls
		return (-1);
	line = get_next_line(p->fd);
	while (line != NULL)
	{
		p->height++;
		help = ft_strlen(line);
		if (help > p->max_len)
			p->max_len = help;
		free(line);
		line = get_next_line(p->fd);
	}
	if (p->height < 3)//has to have space for player
		return (-1);//exit protocolll
	return (1);
}

int	advance_fd_to_map(t_parse *p)
{
	char *str;
	int	i;

	i = -1;
	str = get_next_line(p->fd);
	while (++i < 7)
	{
		if (!str)
			return (-1);
		free(str);
		str = get_next_line(p->fd);
	}
	return (1);
}

void	alocate_map(t_parse *p)
{
	int	i;

	i = 0;
	p->map = malloc(sizeof(void*) * (p->height + 1));
	while (i < p->height)
	{
		p->map[i] = malloc(p->max_len + 2);//change to safe malloc
		ft_memset(p->map[i], '9', p->max_len);
		p->map[i][p->max_len + 1] = '\0';
		put_str_check(p->map[i]);
		i++;
	}
	p->map[i] = NULL;
}

void	copy_map_to_struct(t_parse *p)
{
	char *str;
	int	i;

	i = 0;
	str = get_next_line(p->fd);
	ft_strlcpy(p->map[i], str, ft_strlen(str));//puts the map line onto the pre alocated map
	while(str)
	{
		free(str);
		i++;
		str = get_next_line(p->fd);
		if (!str)
			break ;
		ft_strlcpy(p->map[i], str, ft_strlen(str));
	}
}


int	get_map(t_parse *parse)
{
	get_map_dimensions(parse);
	close(parse->fd);
	parse->fd = open(parse->map_file, O_RDONLY);
	advance_fd_to_map(parse);
	alocate_map(parse);
	copy_map_to_struct(parse);
	return (1);
}

int	parse_input(int argc, char **argv)
{
	t_parse	*p;

	p = p_call();
	if (argc != 2)
		return(call_error());
	if (check_file_name(argv[1]) < 0)
		return(bad_map_perms(argv[1]));
	p->map_file = ft_strdup(argv[1]);
	p->fd = open(p->map_file, O_RDONLY);
	if (p->fd < 0)
		return (bad_map_perms(argv[1]));
	if (parse_texture_paths(p)  < 0)
		return (-1);
	if (parse_ceiling_and_floor(p) < 0)
		return (-1);
	if (get_map(p) < 0)
		return (-1);
	return (1);
}