#include "../../cub3d.h"

static char	*ft_fill_line(char *s, int max_width)
{
	int		i;
	int		len;
	char	*buffer;

	buffer = malloc(sizeof(char) * (max_width + 1));
	if (!buffer)
		return (NULL);
	len = ft_strlen(s);
	if (len > max_width)
		len = max_width;
	i = -1;
	while (++i < len)
		buffer[i] = s[i];
	while (i < max_width)
	{
		buffer[i] = ' ';
		i++;
	}
	buffer[max_width] = '\0';
	return (buffer);
}

static int	ft_fill_tmp_map(t_data *data)
{
	int	i;

	data->map_tmp = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map_tmp)
		return (0);
	i = -1;
	while (++i < data->map_height)
	{
		data->map_tmp[i] = ft_fill_line(data->map[i], data->map_max_width);
		if (!data->map_tmp[i])
			return (0);
	}
	data->map_tmp[i] = NULL;
	return (1);
}

void	ft_flood_fill(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map_height || y < 0 || y >= data->map_max_width)
	{
		data->map_error = 1;
		return ;
	}
	if (x == 0 || x == data->map_height - 1 || y == 0 || \
		y == data->map_max_width - 1)
	{
		if (data->map_tmp[x][y] != '1')
			data->map_error = 1;
		return ;
	}
	if (data->map_tmp[x][y] == ' ')
	{
		data->map_error = 1;
		return ;
	}
	if (data->map_tmp[x][y] == '1' || data->map_tmp[x][y] == '2')
		return ;
	data->map_tmp[x][y] = '2';
	ft_debug(data);
	ft_flood_fill(data, x - 1, y);
	ft_flood_fill(data, x + 1, y);
	ft_flood_fill(data, x, y - 1);
	ft_flood_fill(data, x, y + 1);
}

int	ft_test_map(t_data *data)
{
	int	i;

	i = -1;
	if (!ft_fill_tmp_map(data))
		return (0);
	ft_flood_fill(data, data->player->pos_y, data->player->pos_x);
	if (data->map_error)
		return (0);
	return (1);
}
