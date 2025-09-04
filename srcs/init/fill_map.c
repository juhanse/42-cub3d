#include "../../cub3d.h"

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

static int	ft_malloc_content(t_data *data)
{
	int		fd;
	char	*line;

	fd = open(data->map_path, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		perror(ERR_EMPTY_MAP);
		return (0);
	}
	while (line)
	{
		data->content_height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	data->content = malloc(sizeof(char *) * (data->content_height + 1));
	if (!data->content)
		return (0);
	return (1);
}

int	ft_fill_content(t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	if (!ft_malloc_content(data))
		return (0);
	fd = open(data->map_path, O_RDONLY);
	if (fd < 0)
		return (0);
	i = -1;
	line = get_next_line(fd);
	while (line)
	{
		data->content[++i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	data->content[i + 1] = NULL;
	free(line);
	close(fd);
	return (1);
}

static char	*ft_trim_map_line(char *line)
{
	int		i;
	int		j;
	char	*buffer;
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	buffer = malloc(ft_strlen(line) + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\r' && line[i] != '\t')
			buffer[j++] = line[i];
		i++;
	}
	buffer[j] = '\0';
	return (buffer);
}

static int	ft_find_map_start(char **content, int end)
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

void	ft_get_map(t_data *data)
{
	int		i;
	int		j;
	int		start;
	int		map_lines;
	char	**map;

	i = data->content_height - 1;
	while (i >= 0 && data->content[i][0] == '\n')
		i--;
	start = ft_find_map_start(data->content, i);
	map_lines = i - start + 1;
	map = malloc(sizeof(char *) * (map_lines + 1));
	if (!map)
		exit(EXIT_FAILURE);
	j = -1;
	while (++j < map_lines)
	{
		map[j] = ft_trim_map_line(data->content[start + j]);
		if (!map[j])
			exit(EXIT_FAILURE);
	}
	map[j] = NULL;
	data->map = map;
	data->map_height = map_lines;
	ft_get_max_width(data);
}
