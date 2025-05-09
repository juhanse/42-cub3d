#include "../../cub3d.h"

void	parse_texture_line(t_data *data, char *line)
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

void	parse_color_line(t_data *data, char *line)
{
	if (line[0] == 'F')
		data->floor_color = parse_rgb(line + 1);
	else if (line[0] == 'C')
		data->ceiling_color = parse_rgb(line + 1);
}

void	parse_config(t_data *data)
{
	int	i = 0;

	while (data->content[i] && !is_map_line(data->content[i]))
	{
		parse_texture_line(data, data->content[i]);
		parse_color_line(data, data->content[i]);
		i++;
	}
}
