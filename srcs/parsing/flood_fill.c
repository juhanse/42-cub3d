#include "../../cub3d.h"

static int	ft_get_tmp_map(t_data *data)
{
	int		i;
	int		j;

	data->map_tmp = malloc(sizeof(char *) * (data->map_height));
	if (!data->map_tmp)
		return (0);
	i = -1;
	while (++i < data->map_height)
	{
		data->map_tmp[i] = malloc(data->map_max_width);
		if (!data->map_tmp[i])
			return (0);
		j = -1;
		while (data->map[i][++j])
			data->map_tmp[i][j] = data->map[i][j];
	}
	return (1);
}

static void	ft_fill_line(t_data *data)
{
	int	i;
	int	len;
	int	start;

	i = -1;
	while (data->map_tmp[++i])
	{
		len = ft_strlen(&data->map_path[i]);
		start = data->map_max_width - len;
		while (start < data->map_max_width)
			data->map_tmp[i][start++] = '.';
	}
}

void	ft_flood_fill(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map_height || y < 0 || y >= data->map_max_width || data->map[x][y] == '.')
	{
		if (data->map[x][y] == ' ')
			perror("TEST");
		perror(ERR_MAP);
	}
	if (data->map[x][y] == '1' || data->map[x][y] == '2')
		return ;
	data->map[x][y] = '2';
	ft_flood_fill(data, x - 1, y);
	ft_flood_fill(data, x + 1, y);
	ft_flood_fill(data, x, y - 1);
	ft_flood_fill(data, x, y + 1);
}

int	ft_test_map(t_data *data)
{
	int	i;

	i = -1;
	if (!ft_get_tmp_map(data))
		return (1);
	ft_fill_line(data);
	ft_flood_fill(data, data->player->pos_x, data->player->pos_y);
	while (++i < data->map_height)
		printf("%s\n", data->map_tmp[i]);
	i = -1;
	while (++i < data->map_height)
		free(data->map_tmp[i]);
	free(data->map_tmp);
	return (0);
}
