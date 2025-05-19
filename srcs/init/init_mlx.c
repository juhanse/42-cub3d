#include "../../cub3d.h"

int	ft_init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->wnd = mlx_new_window(data->mlx, MAP_WIDTH * IMG_PXL, MAP_HEIGHT * IMG_PXL, WND_NAME);
	return (0);
}
