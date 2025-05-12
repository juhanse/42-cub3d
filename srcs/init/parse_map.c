#include "../../cub3d.h"

bool	ft_is_map_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] != '1' || line[i] != '0' || line[i] != 'N' || \
			line[i] != 'S' || line[i] != 'E' || line[i] != 'W')
			return (false);
	return (true);
}

int	ft_check_square(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->width)
	{
		if (ft_strlen(data->map[i]) != (size_t) data->width)
		{
			perror(ERR_SQUARE);
			return (1);
		}
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
		{
			if (data->map[i][j] != '0' && data->map[i][j] != '1' && \
			data->map[i][j] != 'N' && data->map[i][j] != 'S' && \
			data->map[i][j] != 'E' && data->map[i][j] != 'W')
			{
				perror(ERR_ARGS);
				return (1);
			}
		}
	}
	return (0);
}

void	ft_parse_map(t_data *data)
{
	(void)data;
	printf("PARSE MAP\n");
}
