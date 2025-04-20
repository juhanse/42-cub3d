#include "../../cub3d.h"

static int	ft_check_path(t_data *data)
{
	int	len;

	len = ft_strlen(data->path);
	if (data->path[len - 1] != 'b' || data->path[len - 2] != 'u' || \
	data->path[len - 3] != 'c' || data->path[len - 4] != '.')
		return (1);
	if (!ft_isalnum(data->path[len - 5]))
		return (1);
	return (0);
}

void	ft_init_map(t_data *data, char *path)
{
	*data = (t_data){0};
	data->path = path;
	if (ft_check_path(data))
	{
		perror(ERR_BAD_PATH);
		exit(EXIT_FAILURE);
	}
}
