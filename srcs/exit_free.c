#include "../../cub3d.h"

// void	free_data(t_data *data, int type) //TBD - voir fct init
// {
// 	int	i;

// 	free(data->player);
// 	free(data->minimap);
// 	free(data->north.path);
// 	free(data->south.path);
// 	free(data->west.path);
// 	free(data->east.path);
// 	i = -1;
// 	while (data->content[++i])
// 		free(data->content[i]);
// 	free(data->content);
// 	if (type == 1 || type == 2)
// 		return ;
// 	i = -1;
// 	while (++i < data->map_height)
// 		free(data->map[i]);
// 	free(data->map);
// 	if (type == 3)
// 		return ;
// 	i = -1;
// 	while (++i < data->map_height)
// 		free(data->map_tmp[i]);
// 	free(data->map_tmp);
// }

// void	free_split(char **s)
// {
// 	int	i;

// 	i = -1;
// 	while (s[++i])
// 		free(s[i]);
// 	free(s);
// }

static void	clean_img(t_data *data, t_img *img)
{
	mlx_destroy_image(data->mlx, img->img);
	img->img = NULL;
	img->data = NULL;
	img->width = 0;
	img->height = 0;
}

void	exit_game(t_data *data)
{
	if (data->north.img)
		clean_img(data, &data->north);
	if (data->south.img)
		clean_img(data, &data->south);
	if (data->west.img)
		clean_img(data, &data->west);
	if (data->east.img)
		clean_img(data, &data->east);
	if (data->mlx_img.img)
		clean_img(data, &data->mlx_img);
	if (data->wnd)
	{
		mlx_destroy_window(data->mlx, data->wnd);
		data->wnd = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
	ft_free_map(data, 4);
	printf("Leave game\n");
	exit; //SUCCESS or FAILURE?
}
