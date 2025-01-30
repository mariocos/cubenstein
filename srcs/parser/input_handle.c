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

int	check_file_name(char *str)
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

int	parse_texture_maps(int	fd)//this function leaks because im not sure where im gonna free yet
{
	char	*str[4];//for the 4 lines and null
	int	i = -1;

	str[0] = get_next_line(fd);//put this in a separet function
	str[1] = get_next_line(fd);
	str[2] = get_next_line(fd);
	str[3] = get_next_line(fd);
	str[4] = NULL;
	/* basic length check and .xpm check */
	while (++i < 5)
	{
		if (ft_strlen(str[i] < 5))//needs to have the direction 2 chars a space 1 char the / for the path atleast
			return (-1);//change to return with free or put this all in a struct and free at the end
	}
	i = -1;
	/* checking perms so xpm_to_image works */
	while (++i < 5)
	{
		if (check_file_perms(str[i] + 3) < 0)// add check for the beggining letters too
			return (-1);
	}
	return(1);//i dont know what else to check about the xpm files
}

int parse_ceiling_and_floor(int fd)
{
	char *space_check;
	char *str[2];//to be added to struct with value of the color

	space_check = get_next_line(fd);
	if (ft_strcmp(space_check, "\n") != 0)//remember to check if strcmp is prepped for nulls
		return (-1);
	str[0] = get_next_line(fd);
	str[1] = get_next_line(fd);
	str[2] = NULL;


}

int	input_handle(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return(call_error());
	if (check_file_name(argv[1]) < 0)
		return(bad_map_file());
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (bad_map_perms(argv[1]));
	if (parse_texture_paths(fd)  < 0)
		return (-1);
	if (parse_ceiling_and_floor(fd) < 0)
		return (-1);
	if (get_map(fd) < 0)
		return (-1);
	return (1);
}