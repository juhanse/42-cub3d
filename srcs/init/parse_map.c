#include "../../cub3d.h"

static float	find_angle(char cardinal)
{
	float	angle;

	angle = 0;
	if (cardinal == 'N')
		angle = (3.0f * M_PI) / 2.0f;
	else if (cardinal == 'S')
		angle = M_PI / 2.0f;
	else if (cardinal == 'W')
		angle = M_PI;
	else if (cardinal == 'E')
		angle = 0;
	return (angle);
}

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
				data->player->pos_x = j;
				data->player->pos_y = i;
				data->player->p_x = j + 0.5f;
				data->player->p_y = i + 0.5f;
				data->player->p_angle = find_angle(data->map[i][j]);
				update_player_dir(data->player);
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
			&& data->map[i][j] != 'E' && data->map[i][j] != 'W' \
			&& data->map[i][j] != ' ' && data->map[i][j] != '\t')
				return (perror(ERR_CHAR_MAP), 0);
		}
	}
	return (1);
}
