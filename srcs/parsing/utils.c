#include "../../cub3d.h"

static void	ft_free_config(t_data *data)
{
	if (data->north.path)
	{
		free(data->north.path);
		data->north.path = NULL;
	}
	if (data->south.path)
	{
		free(data->south.path);
		data->south.path = NULL;
	}
	if (data->west.path)
	{
		free(data->west.path);
		data->west.path = NULL;
	}
	if (data->east.path)
	{
		free(data->east.path);
		data->east.path = NULL;
	}
}

void	ft_free_map(t_data *data, int type)
{
	int	i;

	free(data->player);
	free(data->minimap);
	ft_free_config(data);
	i = -1;
	while (data->content[++i])
		free(data->content[i]);
	free(data->content);
	if (type == 1 || type == 2)
		return ;
	i = -1;
	while (++i < data->map_height)
		free(data->map[i]);
	free(data->map);
	if (type == 3)
		return ;
	i = -1;
	while (++i < data->map_height)
		free(data->map_tmp[i]);
	free(data->map_tmp);
}

void	ft_free_split(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	ft_free_fill_map(t_data *data, int len)
{
	while (--len >= 0)
		free(data->map[len]);
	free(data->map);
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
