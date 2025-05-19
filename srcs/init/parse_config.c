#include "../../cub3d.h"

static int	ft_parse_rgb(char *str)
{
	int		r;
	int		g;
	int		b;
	char	**split;

	split = ft_split(str, ',');
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	return ((r << 16) | (g << 8) | b);
}

void	ft_get_config_texture(t_data *data)
{
	int		i;
	char	**split;

	i = -1;
	while (++i < data->map_copy_height)
	{
		split = ft_split(data->map_copy[i], ' ');
		if (!ft_strncmp("NO", split[0], 2))
			data->north_image = ft_strdup(split[1]);
		else if (!ft_strncmp("SO", split[0], 2))
			data->south_image = ft_strdup(split[1]);
		else if (!ft_strncmp("WE", split[0], 2))
			data->west_image = ft_strdup(split[1]);
		else if (!ft_strncmp("EA", split[0], 2))
			data->east_image = ft_strdup(split[1]);
	}
}

void	ft_get_config_color(t_data *data)
{
	int		i;
	char	**split;

	i = -1;
	while (++i < data->map_copy_height)
	{
		split = ft_split(data->map_copy[i], ' ');
		if (!ft_strncmp("F", split[0], 1))
			data->floor_color = ft_parse_rgb(split[1]);
		else if (!ft_strncmp("C", split[0], 1))
			data->ceiling_color = ft_parse_rgb(split[1]);
	}
}
