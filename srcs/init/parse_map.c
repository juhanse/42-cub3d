#include "../../cub3d.h"

/* static int	ft_check_walls(t_data *data)
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

static int	ft_check_line_config(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] != '1' || line[i] != '0' || line[i] != 'N' || \
			line[i] != 'S' || line[i] != 'E' || line[i] != 'W')
			return (perror(ERR_CHAR_MAP), 1);
	return (0);
}

static int	ft_check_line_map(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] != '1' || line[i] != '0' || line[i] != 'N' || \
			line[i] != 'S' || line[i] != 'E' || line[i] != 'W')
			return (perror(ERR_CHAR_MAP), 1);
	return (0);
} */
