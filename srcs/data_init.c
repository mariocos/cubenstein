#include "cube.h"
#include <stdlib.h>

void	ft_bzero(void *str, size_t	num)
{
	unsigned char	*char_str;
	size_t			i;

	i = 0;
	char_str = str;
	while (i < num)
		char_str[i++] = '\0';
}

void	data_init(t_data *d)
{
	t_vars	data;
	(void)data;
	(void)d;
	d->wall_data = malloc(sizeof(t_wall));
	if (!d->wall_data)
	{
		printf("a problem in the lib has occurred\n");
		exit(1);
	}
	ft_bzero(d->wall_data, sizeof(t_wall));
}
