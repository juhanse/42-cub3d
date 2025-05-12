#include "../cub3d.h"

void	ft_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_debug(t_data *data)
{
	int	i;

	i = -1;
	printf("width [%d] | height [%d]", data->width, data->height);
	while (++i < data->width)
		printf("\n[%d] %s", i, data->map[i]);
}
