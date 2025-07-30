#include "../../cub3d.h"

int	quit_game(t_data *data)
{
	//don't forget to destroy imgs + free maps copy, player malloc & co
	mlx_destroy_window(data->mlx, data->wnd);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	printf("Leave game\n");
	exit(EXIT_SUCCESS);
	return (0);
}

void	ft_hooks(t_data *data)
{
	mlx_hook(data->wnd, 17, 0, &quit_game, data);
	mlx_loop_hook(data->mlx, &render_loop, data);
}

void	ft_init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->wnd = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, WND_NAME);
	data->mlx_img.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->mlx_img.pxl_data = mlx_get_data_addr(data->mlx_img.img, &data->mlx_img.bpp, &data->mlx_img.size_line, &data->mlx_img.endian);
	load_textures(data);
	ft_hooks(data);
	mlx_loop(data->mlx);
}
