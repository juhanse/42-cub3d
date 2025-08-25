#include "../../cub3d.h"

int	quit_game(t_data *data)
{
	mlx_destroy_window(data->mlx, data->wnd);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	printf("Leave game\n");
	exit(EXIT_SUCCESS);
	return (0);
}

void	ft_init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->wnd = mlx_new_window(data->mlx, MAP_WIDTH, MAP_HEIGHT, WND_NAME);
	mlx_loop(data->mlx);
	mlx_hook(data->wnd, 17, 0, &quit_game, data);
}
