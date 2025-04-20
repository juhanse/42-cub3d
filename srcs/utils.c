#include "../cub3d.h"

void	ft_free_map(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->width)
		free(data->map[i]);
	free(data->map);
	data->map = NULL;
}

int	ft_exit_game(t_data *data)
{
	ft_free_map(data);
	exit(EXIT_SUCCESS);
}

void	ft_debug(t_data *data)
{
	int	i;

	i = -1;
	printf("[%d] - [%d]", data->width, data->height);
	while (++i < data->width - 1)
		printf("\n[%d] %s", i, data->map[i]);
}
