#include "../../cub3d.h"

int	ft_found_player(t_data *data)
{
	int		i;
	size_t	j;
	int		found;

	i = -1;
	found = 0;
	while (++i < data->height)
	{
		j = -1;
		while (++j < ft_strlen(data->map[i]))
		{
			if (ft_strchr("NSEW", data->map[i][j]))
			{
				data->player->x = j;
				data->player->y = i;
				data->player->angle = data->map[i][j];
				found = 1;
			}
		}
	}
	if (!found)
		return (perror(ERR_PLY_NOT_FOUND), 1);
	return (0);
}

int	ft_check_walls(t_data *data)
{
	int		i;
	size_t	j;
	size_t	len;

	i = -1;
	while (++i < data->height)
	{
		len = ft_strlen(data->map[i]);
		j = -1;
		while (++j < len)
			if (i == 0 || i == data->height - 1 || j == 0 \
				|| j == len - 1)
				if (data->map[i][j] != '1')
					return (perror(ERR_WALLS), 1);
	}
	return (0);
}

int	ft_check_char(t_data *data)
{
	int		i;
	size_t	j;

	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < ft_strlen(data->map[i]))
			if (data->map[i][j] != '0' && data->map[i][j] != '1' \
			&& data->map[i][j] != 'N' && data->map[i][j] != 'S' \
			&& data->map[i][j] != 'E' && data->map[i][j] != 'W')
				return (perror(ERR_CHAR_MAP), 0);
	}
	return (1);
}
