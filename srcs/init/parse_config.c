#include "../../cub3d.h"

static int	ft_parse_rgb(char *str)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(str, ',');
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	return ((r << 16) | (g << 8) | b);
}

static void	ft_parse_texture(t_data *data, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		data->north_image = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		data->south_image = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		data->west_image = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		data->east_image = ft_strdup(line + 3);
}

static void	ft_parse_color(t_data *data, char *line)
{
	if (line[0] == 'F')
		data->floor_color = ft_parse_rgb(line + 1);
	else if (line[0] == 'C')
		data->ceiling_color = ft_parse_rgb(line + 1);
}

void	ft_parse_config(t_data *data)
{
	int	i;

	i = 0;
	while (data->content[i] && !ft_is_map_line(data->content[i]))
	{
		ft_parse_texture(data, data->content[i]);
		ft_parse_color(data, data->content[i]);
		i++;
	}
}
