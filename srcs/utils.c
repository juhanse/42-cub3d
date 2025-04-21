#include "../cub3d.h"

void	ft_free(t_data *data)
{
	free(data->path);
	if (data->map)
		ft_free_map(data);
	if (data->north_image)
		free(data->north_image);
	if (data->south_image)
		free(data->south_image);
	if (data->west_image)
		free(data->west_image);
	if (data->east_image)
		free(data->east_image);
	if (data->player)
		free(data->player);
}

void	ft_free_map(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->width)
		free(data->map[i]);
	free(data->map);
	data->map = NULL;
}

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
