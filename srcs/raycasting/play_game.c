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

int	key_press(int keycode, t_data *data)
{
	t_player	*player;

	player = data->player;
	if (keycode == W)
		player->moves.w_pressed = true;
	if (keycode == A)
		player->moves.a_pressed = true;
	if (keycode == S)
		player->moves.s_pressed = true;
	if (keycode == D)
		player->moves.d_pressed = true;
	if (keycode == LEFT)
		player->moves.left_rot = true;
	if (keycode == RIGHT)
		player->moves.right_rot = true;
	if (keycode == ESC)
		quit_game(data);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->moves.w_pressed = false;
	if (keycode == A)
		player->moves.a_pressed = false;
	if (keycode == S)
		player->moves.s_pressed = false;
	if (keycode == D)
		player->moves.d_pressed = false;
	if (keycode == LEFT)
		player->moves.left_rot = false;
	if (keycode == RIGHT)
		player->moves.right_rot = false;
	return (0);
}

void	set_hooks(t_data *data)
{
	mlx_hook(data->wnd, 2, 1L<<0, &key_press, data);
	mlx_hook(data->wnd, 3, 1L<<1, &key_release, data->player);
	mlx_hook(data->wnd, 17, 0, &quit_game, data);
	mlx_loop_hook(data->mlx, &render_loop, data);
}

void	init_mlx(t_data *data)
{
	data->map_width = 8; //TEMP
	data->mlx = mlx_init();
	if (!data->mlx) //proper exit TBD
		exit(EXIT_FAILURE);
	data->wnd = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, WND_NAME);
	if (!data->wnd) //proper exit TBD
		exit(EXIT_FAILURE);
	data->mlx_img.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->mlx_img.img) //proper exit TBD
		exit(EXIT_FAILURE);
	data->mlx_img.data = mlx_get_data_addr(data->mlx_img.img, &data->mlx_img.bpp, &data->mlx_img.size_line, &data->mlx_img.endian);
	mlx_put_image_to_window(data->mlx, data->wnd, data->mlx_img.img, 0, 0);
	set_hooks(data);
}

void	play_game(t_data *data)
{
	init_mlx(data);
	set_hooks(data);
	mlx_loop(data->mlx);
}