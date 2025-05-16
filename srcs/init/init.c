#include "../../cub3d.h"

static int	ft_check_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (path[len - 1] != 'b' || path[len - 2] != 'u' || path[len - 3] != 'c' \
		|| path[len - 4] != '.' || !ft_isalnum(path[len - 5]))
		return (1);
	return (0);
}

static void	ft_malloc_content(t_data *data)
{
	int		fd;
	char	*line;

	fd = open(data->map_path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		data->content_len++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	data->content = malloc(sizeof(char *) * (data->content_len + 1));
	if (!data->content)
		exit(EXIT_FAILURE);
}

void	ft_fill_content(t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	ft_malloc_content(data);
	fd = open(data->map_path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
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
}

int	ft_initialize(t_data *data, char *path)
{
	*data = (t_data){0};
	if (ft_check_path(path))
		return (perror(ERR_BAD_PATH), 1);
	data->map_path = path;
	ft_fill_content(data);
	ft_get_config_texture(data);
	ft_get_config_color(data);
	ft_debug(data);
	return (0);
}
