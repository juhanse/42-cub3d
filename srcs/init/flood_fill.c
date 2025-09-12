#include "../../cub3d.h"

void	ft_flood_fill(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map_height || y < 0 || y >= data->map_max_width || data->map[x][y] == '.')
	{
		if (data->map[x][y] == ' ')
			return (ft_exit_error(3));
		return (ft_exit_error(1));
	}
	if (data->map[x][y] == '1' || data->map[x][y] == '2')
		return ;
	data->map[x][y] = '2';
	ft_flood_fill(data, x - 1, y);
	ft_flood_fill(data, x + 1, y);
	ft_flood_fill(data, x, y - 1);
	ft_flood_fill(data, x, y + 1);
}
