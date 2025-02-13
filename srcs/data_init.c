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

void	init_wall_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		data->wall_data[i] = malloc(sizeof(t_wall));
		if (!data->wall_data[i])
		{
			printf("a problem in the lib has occurred\n");
			exit(1);
		}
		data->wall_data[i]->wall = malloc(sizeof(t_img));
		if (!data->wall_data[i]->wall)
		{
			printf("Erro ao alocar wall_data[%d]->wall\n", i);
			exit(1);
		}
		ft_bzero(data->wall_data[i], sizeof(t_wall));
  		data->wall_data[i]->text_width = 256;
  		data->wall_data[i]->text_height = 256;
	}
}

void	data_init(t_data *d)
{
	t_vars	data;
	(void)data;
	(void)d;
	init_wall_data(d);
}
