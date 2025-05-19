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
	if (ft_check_path(path))
		return (perror(ERR_BAD_PATH), 1);
	data->map_path = path;
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (perror(ERR_MALLOC), 1);
	ft_fill_content(data);
	ft_get_config_texture(data);
	ft_get_config_color(data);
	ft_get_map(data);
	ft_debug(data);
	if (!ft_check_char(data) || !ft_found_player(data) \
	|| !ft_check_walls(data))
		ft_free_map(data);
	ft_init_mlx(data);
	return (0);
}
