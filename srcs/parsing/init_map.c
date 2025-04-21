#include "../../cub3d.h"

static int	ft_check_path(t_data *data)
{
	int	len;

	len = ft_strlen(data->path);
	if (data->path[len - 1] != 'b' || data->path[len - 2] != 'u' || \
	data->path[len - 3] != 'c' || data->path[len - 4] != '.')
		return (1);
	if (!ft_isalnum(data->path[len - 5]))
		return (1);
	return (0);
}

static int	ft_check_square(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->width)
	{
		if (ft_strlen(data->map[i]) != data->width)
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

void	ft_init_map(t_data *data, char *path)
{
	*data = (t_data){0};
	data->path = path;
	if (ft_check_path(data))
	{
		perror(ERR_BAD_PATH);
		exit(EXIT_FAILURE);
	}
	ft_set_size(data);
	ft_allocate_map(data);
	ft_fill_map(data);
	ft_debug(data);
	if (ft_check_char(data) || ft_check_square(data) || ft_check_walls(data))
	{
		ft_free_map(data);
		exit(EXIT_FAILURE);
	}
}
