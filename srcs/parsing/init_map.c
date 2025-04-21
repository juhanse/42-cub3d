#include "../../cub3d.h"

static int	ft_check_square(t_data *data)
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

static int	ft_check_walls(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			if (i == 0 || i == data->height - 1 || j == 0 || j == data->width - 1)
			{
				if (data->map[i][j] != '1')
				{
					perror(ERR_WALLS);
					return (1);
				}
			}
		}
	}
	return (0);
}

static int	ft_check_char(t_data *data)
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

void	ft_init_map(t_data *data)
{
	ft_set_size(data);
	ft_allocate_map(data);
	ft_fill_map(data);
	ft_debug(data);
	if (ft_check_char(data) || ft_check_square(data) || ft_check_walls(data))
	{
		ft_free(data);
		exit(EXIT_FAILURE);
	}
}
