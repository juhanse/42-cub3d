#include "../../cub3d.h"

void	ft_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_free_map(t_data *data, int type)
{
	int	i;

	free(data->player);
	free(data->minimap);
	free(data->north.path);
	free(data->south.path);
	free(data->west.path);
	free(data->east.path);
	i = -1;
	while (++i < data->map_height)
		free(data->content[i]);
	free(data->content);
	if (type == 1 || type == 2)
		return ;
	i = -1;
	while (++i < data->map_height)
		free(data->map[i]);
	free(data->map);
}

void	ft_free_split(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	ft_debug(t_data *data)
{
	int	i;

	i = -1;
	printf("MAP HEIGHT: %d\n", data->map_height);
	printf("MAP WIDTH: %d\n", data->map_max_width);
	printf("MAP :\n");
	while (++i < data->map_height)
		printf("[%d] %s - %zu\n", i, data->map[i], ft_strlen(data->map[i]));
	i = -1;
	printf("\nFLOOD MAP :\n");
	while (++i < data->map_height)
		printf("[%d] %s - %zu\n", i, data->map_tmp[i], \
	ft_strlen(data->map_tmp[i]));
	printf("\nFLOOR: [%d]\nCEILING: [%d]\n", data->floor_color, \
		data->ceiling_color);
	printf("\nN: [%s]\nS: [%s]\nW: [%s]\nE: [%s]\n", data->north.path, \
		data->south.path, data->west.path, data->east.path);
}
