#include "../../cub3d.h"

void	ft_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_free_map(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->map_height)
	{
		free(data->content[i]);
		free(data->map[i]);
	}
	free(data->content);
	free(data->map);
	free(data->player);
}

void	ft_free_split(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	ft_debug(t_data *data)
{
	int	i;

	i = -1;
	printf("MAP HEIGHT: %d\n", data->map_height);
	printf("MAP WIDTH: %d\n", data->map_max_width);
	while (++i < data->map_height)
		printf("[%d] %s\n", i, data->map[i]);
	// printf("\nNO: %s\nSO: %s\nWE: %s\nEA: %s\n", data->north_image, \
	// 	data->south_image, data->west_image, data->east_image);
	printf("\nFLOOR: [%d]\nCEILING: [%d]\n", data->floor_color, \
		data->ceiling_color);
}
