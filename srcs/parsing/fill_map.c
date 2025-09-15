#include "../../cub3d.h"

static void	ft_free_fill_map(t_data *data, int len)
{
	int	i;

	i = -1;
	while (++i < len - 1)
		free(data->map[i]);
	free(data->map);
}

static char	*ft_malloc_line(char *s)
{
	int		i;
	int		len;
	char	*buffer;

	len = ft_strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		len--;
	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		if (s[i] != '0' && s[i] != '1' && s[i] != 'N' \
			&& s[i] != 'S' && s[i] != 'E' && s[i] != 'W' \
			&& s[i] != 32 && s[i] != 9)
			return (free(buffer), NULL);
		buffer[i] = s[i];
	}
	buffer[i] = '\0';
	return (buffer);
}

static void	ft_get_max_width(t_data *data)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	data->map_max_width = (int)ft_strlen(data->map[0]);
	while (data->map[++i])
	{
		len = (int)ft_strlen(data->map[i]);
		if (len > data->map_max_width)
			data->map_max_width = len;
	}
}

static int	ft_find_start(char **content, int end)
{
	int		start;
	int		k;

	start = end;
	while (start >= 0)
	{
		k = 0;
		while (content[start][k] == ' ' || content[start][k] == '\t')
			k++;
		if (content[start][k] == '\0' || content[start][k] == '\n')
			start--;
		else if (ft_strchr("01NSEW", content[start][k]))
			start--;
		else
			break ;
	}
	return (start + 2);
}

int	ft_fill_map(t_data *data)
{
	int		i;
	int		start;
	int		height;

	i = data->content_height - 1;
	while (i >= 0 && data->content[i][0] == '\n')
		i--;
	start = ft_find_start(data->content, i);
	height = i - start + 1;
	data->map = malloc(sizeof(char *) * (height + 1));
	if (!data->map)
		return (0);
	i = -1;
	while (++i < height)
	{
		data->map[i] = ft_malloc_line(data->content[start + i]);
		if (!data->map[i])
			return (ft_free_fill_map(data, i), 0);
	}
	data->map[i] = NULL;
	data->map_height = height;
	ft_get_max_width(data);
	return (1);
}
