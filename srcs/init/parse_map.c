#include "../../cub3d.h"

int	ft_found_player(t_data *data)
{
	int		i;
	size_t	j;

	i = -1;
	while (++i < data->map_height)
	{
		j = -1;
		while (++j < ft_strlen(data->map[i]))
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || \
				data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				data->player->x = j;
				data->player->y = i;
				data->player->angle = data->map[i][j];
				return (1);
			}
		}
	}
	return (perror(ERR_PLY_NOT_FOUND), 0);
}

int	ft_check_walls(t_data *data)
{
	int		i;
	size_t	j;
	size_t	len;

	i = -1;
	while (++i < data->map_height)
	{
		len = ft_strlen(data->map[i]);
		j = -1;
		while (++j < len)
			if (i == 0 || i == data->map_height - 1 || \
				j == 0 || j == len - 1)
				if (data->map[i][j] != '1')
					return (perror(ERR_WALLS), 0);
	}
	return (1);
}

int	ft_check_char(t_data *data)
{
	int		i;
	size_t	j;

	i = -1;
	while (++i < data->map_height)
	{
		j = -1;
		while (++j < ft_strlen(data->map[i]))
		{
			if (data->map[i][j] != '0' && data->map[i][j] != '1' \
			&& data->map[i][j] != 'N' && data->map[i][j] != 'S' \
			&& data->map[i][j] != 'E' && data->map[i][j] != 'W')
				return (perror(ERR_CHAR_MAP), 0);
		}
	}
	return (1);
}
