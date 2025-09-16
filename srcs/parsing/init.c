#include "../../cub3d.h"

static int	ft_check_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (access(path, R_OK))
		return (1);
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
	data->player = ft_calloc(1, sizeof(t_player));
	if (!data->player)
		return (perror(ERR_MALLOC), 1);
	data->minimap = ft_calloc(1, sizeof(t_mini));
	if (!data->minimap)
		return (perror(ERR_MALLOC), 1);
	if (!ft_fill_content(data))
		return (free(data->player), free(data->minimap), 1);
	ft_get_config_texture(data);
	ft_get_config_color(data);
	if (data->floor_color == -1 || data->ceiling_color == -1)
		return (ft_free_map(data, 1), perror(ERR_CONFIG), 1);
	if (!ft_fill_map(data))
		return (ft_free_map(data, 2), perror(ERR_MAP), 1);
	if (!ft_found_player(data))
		return (ft_free_map(data, 3), perror(ERR_PLY_NOT_FOUND), 1);
	if (!ft_test_map(data))
		return (ft_free_map(data, 3), perror(ERR_MAP), 1);
	ft_debug(data);
	return (0);
}
