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
	while (++i < data->height)
		free(data->map[i]);
	free(data->map);
	free(data->player);
}

void	ft_print_map(t_data *data)
{
	int	i;

	i = -1;
	printf("\n------ MAP ------\n");
	while (++i < data->height)
		printf("[%2d] %s\n", i, data->map[i]);
	printf("-----------------\n");
}

void	ft_debug(t_data *data)
{
	int	i;

	i = -1;
	printf("CONTENT_LEN: %d\n", data->content_len);
	while (++i < data->content_len)
		printf("[%d] %s\n", i, data->content[i]);
	printf("\nNO: %s\nSO: %s\nWE: %s\nEA: %s\n", data->north_image, \
		data->south_image, data->west_image, data->east_image);
	printf("\nMAP_HEIGHT: %d", data->height);
	ft_print_map(data);
}
