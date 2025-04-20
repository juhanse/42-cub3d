#include "../../cub3d.h"

void	ft_set_size(t_data *data)
{
	int		fd;
	char	*line;

	fd = open(data->path, O_RDONLY);
	if (fd < 0)
	{
		perror(ERR_BAD_PATH);
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	data->width = ft_strlen(line) - 1;
	while (line)
	{
		data->height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	ft_allocate_map(t_data *data)
{
	int	i;

	i = -1;
	data->map = (char **)malloc(data->height * sizeof(char *));
	if (!data->map)
		exit(EXIT_FAILURE);
	while (++i < data->height)
	{
		data->map[i] = (char *)malloc((data->width) * sizeof(char));
		if (!data->map[i])
		{
			ft_free_map(data);
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_fill_map(t_data *data)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(data->path, O_RDONLY);
	if (fd < 0)
	{
		ft_free_map(data);
		exit(EXIT_FAILURE);
	}
	i = -1;
	line = get_next_line(fd);
	while (line)
	{
		ft_memcpy(data->map[++i], line, data->width);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
