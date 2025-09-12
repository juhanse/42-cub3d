#include "../../cub3d.h"

void	ft_flood_fill(t_data *data, int x, int y)
{
	int	col;

	col = ft_strlen(data->map[x]);
	if (x < 0 || x >= data->map_height || y < 0 || y >= col)
		return ;
	if (data->map[x][y] == '1')
		return ;
	data->map[x][y] = '.';
	ft_flood_fill(data, x - 1, y);
	ft_flood_fill(data, x + 1, y);
	ft_flood_fill(data, x, y - 1);
	ft_flood_fill(data, x, y + 1);
}
