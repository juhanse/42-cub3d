#include "../../cub3d.h"

static void	ft_free_content(t_data *data, int len)
{
	while (--len >= 0)
		free(data->content[len]);
	free(data->content);
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
		return (free(line), close(fd), perror(ERR_EMPTY_MAP), 0);
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
		return (close(fd), perror(ERR_MALLOC), 0);
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
		if (!data->content[i])
			return (free(line), ft_free_content(data, i), \
		close(fd), perror(ERR_MALLOC), 0);
		free(line);
		line = get_next_line(fd);
	}
	data->content[i + 1] = NULL;
	free(line);
	close(fd);
	return (1);
}
