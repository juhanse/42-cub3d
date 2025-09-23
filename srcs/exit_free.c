#include "../cub3d.h"

static void	clean_img(t_data *data, t_img *img)
{
	mlx_destroy_image(data->mlx, img->img);
	img->img = NULL;
	img->data = NULL;
	img->width = 0;
	img->height = 0;
}

int	exit_game(t_data *data)
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
	exit (data->exit_code);
	return (0);
}
