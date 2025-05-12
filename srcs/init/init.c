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

int	ft_initialize(t_data *data, char *path)
{
	*data = (t_data){0};
	if (ft_check_path(path))
		return (perror(ERR_BAD_PATH), 1);
	data->path = path;
	printf("PATH: %s\n", data->path);
	return (0);
}
