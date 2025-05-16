#include "../../cub3d.h"

int	ft_found_player(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' \
			|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
				return (perror(ERR_PLY_NOT_FOUND), 1);
	}
	return (0);
}

int	ft_check_walls(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
			if (i == 0 || i == data->height - 1 || j == 0 \
				|| j == data->width - 1)
				if (data->map[i][j] != '1')
					return (perror(ERR_WALLS), 1);
	}
	return (0);
}

int	ft_check_char(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
			if (data->map[i][j] != '0' && data->map[i][j] != '1' \
			&& data->map[i][j] != 'N' && data->map[i][j] != 'S' \
			&& data->map[i][j] != 'E' && data->map[i][j] != 'W')
				return (perror(ERR_CHAR_MAP), 0);
	}
	return (1);
}
