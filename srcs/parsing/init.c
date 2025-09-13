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
	data->player = ft_calloc(1, sizeof(t_player));
	if (!data->player)
		return (perror(ERR_MALLOC), 1);
	data->minimap = ft_calloc(1, sizeof(t_mini));
	if (!data->minimap)
		return (perror(ERR_MALLOC), 1);
	if (!ft_fill_content(data)) // STEP #1
		return (ft_free_map(data), 1);
	ft_get_config_texture(data); // STEP #2
	ft_get_config_color(data); // STEP #2
	if (!ft_get_map(data)) // STEP #3
		return (perror(ERR_MAP), 1);
	ft_debug(data);
	/* if (!ft_check_char(data))
		return (1); */
	if (!ft_found_player(data))
		return (1);
	if (!ft_test_map(data))
		return (perror(ERR_MAP), 1);
	//ft_debug(data);
	return (0);
}
