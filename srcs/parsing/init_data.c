#include "../../cub3d.h"

static int	ft_check_path(t_data *data)
{
	int	len;

	len = ft_strlen(data->path);
	if (data->path[len - 1] != 'b' || data->path[len - 2] != 'u' || \
	data->path[len - 3] != 'c' || data->path[len - 4] != '.' || \
	!ft_isalnum(data->path[len - 5]))
		return (1);
	return (0);
}

static void	ft_fill_fd(t_data *data)
{
	int		fd;
	char	*line;

	fd = open(data->path, O_RDONLY);
	if (fd < 0)
	{
		perror(ERR_BAD_PATH);
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	data->width = ft_strlen(line) - 1;
	while (line)
	{
		ft_strlcpy(data->map[data->height], line, ft_strlen(line) - 1);
		free(line);
		line = get_next_line(fd);
		data->height++;
	}
	free(line);
	close(fd);
}

void	ft_init_data(t_data *data, char *path)
{
	*data = (t_data){0};
	data->path = path;
	if (ft_check_path(data))
		ft_exit(ERR_BAD_PATH);
	ft_fill_fd(data);
	//ft_debug(data);
}
