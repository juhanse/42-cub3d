#include "../cub3d.h"

void	ft_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_debug(t_data *data)
{
	printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", data->north_image, data->south_image, data->west_image, data->east_image);
	printf("FLOOR: %d\nCEIL: %d\n", data->floor_color, data->ceiling_color);
}
