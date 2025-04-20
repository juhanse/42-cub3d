#include "../cub3d.h"

void	ft_free_map(t_data *data)
{
	size_t	i;

	i = -1;
	while (data->width)
		free(data->map[i]);
	free(data->map);
}

int	ft_exit_game(t_data *data)
{
	ft_free_map(data);
	exit(EXIT_SUCCESS);
}
