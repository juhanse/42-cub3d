#include "../../cub3d.h"

static char	*ft_malloc_textures(char *s)
{
	int		i;
	int		j;
	int		space;
	char	*buffer;

	i = -1;
	space = 0;
	while (s[++i])
		if (s[i] == ' ' || s[i] == '\t')
			space++;
	buffer = malloc((ft_strlen(s) - space) * sizeof(char));
	if (!buffer)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\r')
			buffer[j++] = s[i];
	buffer[j] = '\0';
	return (buffer);
}

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
	ft_free_split(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

static char	*ft_join_color(char **split)
{
	char	*buffer;

	buffer = ft_strjoin(split[1], split[2]);
	if (split[3])
		buffer = ft_strjoin(buffer, split[3]);
	return (buffer);
}

int	ft_get_config_color(t_data *data)
{
	int		i;
	char	**split;

	i = -1;
	while (++i < data->content_height)
	{
		split = ft_split(data->content[i], ' ');
		if (split[0] && !ft_strncmp("F", split[0], 1) && split[1])
		{
			if (split[2])
				split[1] = ft_join_color(split);
			data->floor_color = ft_parse_rgb(split[1]);
		}
		else if (split[0] && !ft_strncmp("C", split[0], 1) && split[1])
		{
			if (split[2])
				split[1] = ft_join_color(split);
			data->ceiling_color = ft_parse_rgb(split[1]);
		}
		ft_free_split(split);
	}
	if (data->floor_color == -1 || data->ceiling_color == -1)
		return (0);
	return (1);
}

int	ft_get_config_texture(t_data *data)
{
	int		i;
	char	**split;

	i = -1;
	while (++i < data->content_height)
	{
		split = ft_split(data->content[i], ' ');
		if (split[0] && !ft_strncmp("NO", split[0], 2) && split[1])
			data->north.path = ft_malloc_textures(split[1]);
		else if (split[0] && !ft_strncmp("SO", split[0], 2) && split[1])
			data->south.path = ft_malloc_textures(split[1]);
		else if (split[0] && !ft_strncmp("WE", split[0], 2) && split[1])
			data->west.path = ft_malloc_textures(split[1]);
		else if (split[0] && !ft_strncmp("EA", split[0], 2) && split[1])
			data->east.path = ft_malloc_textures(split[1]);
		ft_free_split(split);
	}
	if (!data->north.path || !data->south.path || !data->west.path \
		|| !data->east.path)
		return (0);
	return (1);
}
