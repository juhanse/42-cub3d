#include "../cub3d.h"

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
		free(data->map[i]);
	free(data->map);
	free(data->player);
}

void	ft_print_map(t_data *data)
{
	int	i;

	i = -1;
	printf("\n------ MAP ------\n");
	while (++i < data->map_height)
		printf("[%2d] %s\n", i, data->map[i]);
	printf("-----------------\n");
}

void	ft_debug(t_data *data)
{
	int	i;

	i = -1;
	printf("MAP COPY LEN: %d\n", data->map_cpy_height);
	while (++i < data->map_cpy_height)
		printf("[%d] %s\n", i, data->map_cpy[i]);
	printf("\nNO: %s\nSO: %s\nWE: %s\nEA: %s\n", data->north_path, \
		data->south_path, data->west_path, data->east_path);
	printf("\nMAP_HEIGHT: %d", data->map_height);
	ft_print_map(data);
}
