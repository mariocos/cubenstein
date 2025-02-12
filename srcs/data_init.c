#include "cube.h"
#include <stdlib.h>

static void	ft_bzero(void *str, size_t	num)
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
	d->wall = malloc(sizeof(t_wall));
	if (!d->wall)
	{
        printf("malloc error wall struct\n");
        exit(1);
    }
	ft_bzero(d->wall, sizeof(t_wall));
}
