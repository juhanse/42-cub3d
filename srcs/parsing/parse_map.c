#include "../../cub3d.h"

int	is_map_line(char *line)
{
	while (*line)
	{
		if (*line == '1' || *line == '0' || *line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			return (1);
		line++;
	}
	return (0);
}

int	parse_rgb(char *str)
{
	char **split = ft_split(str, ',');
	int r = ft_atoi(split[0]);
	int g = ft_atoi(split[1]);
	int b = ft_atoi(split[2]);
	//free_split(split);
	return ((r << 16) | (g << 8) | b);
}

void	parse_map(t_data *data)
{
	int		i = 0;
	int		map_start;

	while (data->content[i] && !is_map_line(data->content[i]))
		i++;
	map_start = i;
	while (data->content[i])
		i++;
	int height = i - map_start;
	data->map = malloc(sizeof(char *) * (height + 1));
	for (i = 0; i < height; i++)
		data->map[i] = ft_strdup(data->content[map_start + i]);
	data->map[height] = NULL;
	data->height = height;
	data->width = ft_strlen(data->map[0]);
	//find_player(data);
}
