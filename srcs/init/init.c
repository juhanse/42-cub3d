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
	if (ft_check_path(path)) //check .cub file
		return (perror(ERR_BAD_PATH), 1);
	data->map_path = path;
	data->player = ft_calloc(1, sizeof(t_player));
	if (!data->player)
		return (perror(ERR_MALLOC), 1);
	ft_fill_content(data); //malloc le char** copy du fichier et rempli
	ft_get_config_texture(data); //recup des path vers les textures NO SO WE EA
	ft_get_config_color(data); //recup les couleurs du F&C avec application du bitshift
	ft_get_map(data); //recup seulement la map de jeu nettoyee
	if (!ft_check_char(data) || !ft_found_player(data) \
	|| !ft_check_walls(data)) //verif les char, presence du player et les murs qui entourent
		ft_free_map(data);
	ft_debug(data);
	//ft_init_mlx(data);
	return (0);
}
