#include "../../cub3d.h"

int	ft_init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->wnd = mlx_new_window(data->mlx, MAP_WIDTH, MAP_HEIGHT, WND_NAME);
	mlx_loop(data->mlx);
	return (0);
}
