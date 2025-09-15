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
