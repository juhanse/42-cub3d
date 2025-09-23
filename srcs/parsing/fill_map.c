#include "../../cub3d.h"

static void	ft_free_fill_map(t_data *data, int len)
{
	while (--len >= 0)
		free(data->map[len]);
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

static int	is_map_line(const char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '\0' || s[i] == '\n')
		return (0);
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != '0' && s[i] != '1' && s[i] != 'N'
			&& s[i] != 'S' && s[i] != 'E' && s[i] != 'W'
			&& s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_find_start(char **content, int end)
{
	int	last_map;

	last_map = -1;
	while (end >= 0)
	{
		if (is_map_line(content[end]))
		{
			last_map = end;
			end--;
		}
		else if (last_map != -1)
			break ;
		else
			end--;
	}
	if (last_map == -1)
		return (-1);
	return (end + 1);
}

int	ft_fill_map(t_data *data)
{
	int	i;
	int	start;
	int	end;
	int	height;

	end = data->content_height - 1;
	while (end >= 0 && (data->content[end][0] == '\n' || data->content[end][0] == '\0'))
		end--;
	start = ft_find_start(data->content, end);
	if (start < 0)
		return (0);
	height = end - start + 1;
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
