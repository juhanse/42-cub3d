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

void	ft_parse_map(t_data *data)
{
	int		fd;
	char	*line;
	char	**split;

	fd = open(data->map_path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		split = ft_split(line, ' ');
		//printf("[1] %s \n[2] %s\n", split[0], split[1]);
		if (ft_strncmp("NO", split[0], 2))
			data->north_image = split[1];
		else if (ft_strncmp("SO", split[0], 2))
			data->south_image = split[1];
		else if (ft_strncmp("WE", split[0], 2))
			data->west_image = split[1];
		else if (ft_strncmp("EA", split[0], 2))
			data->east_image = split[1];
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", data->north_image, data->south_image, data->west_image, data->east_image);
}
