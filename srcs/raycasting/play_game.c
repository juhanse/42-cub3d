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

static int	key_press(int keycode, t_data *data)
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

static int	key_release(int keycode, t_player *player)
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

static void	set_hooks(t_data *data)
{
	mlx_hook(data->wnd, 2, 1L<<0, &key_press, data);
	mlx_hook(data->wnd, 3, 1L<<1, &key_release, data->player);
	mlx_hook(data->wnd, 17, 0, &quit_game, data);
	mlx_loop_hook(data->mlx, &render_loop, data);
}

int	handle_text(t_data *data, t_img *text, char *path)
{
	text->img = mlx_xpm_file_to_image(data->mlx, path, &text->width, &text->height);
	if (!text->img)
	{
		printf("Texture load failed\n");
		printf("Texture received : %s - len %zu\n", path, ft_strlen(path));
		return (1);
	}
	text->data = mlx_get_data_addr(text->img, &text->bpp, &text->size_line, &text->endian);
	if (!text->data)
	{
		write(2, "Data addr failed\n", 17);
		return (1);
	}
	return (0);
}

int	upload_textures(t_data *data)
{
	if (handle_text(data, &data->north, data->north.path))
		return (1);
	if (handle_text(data, &data->south, data->south.path))
		return (1);
	if (handle_text(data, &data->west, data->west.path))
		return (1);
	if (handle_text(data, &data->east, data->east.path))
		return (1);
	return (0);
}

static void	init_mlx(t_data *data)
{
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
}

void	play_game(t_data *data)
{
	init_mlx(data);
	if (upload_textures(data))
		quit_game(data); //TO DO 
	set_hooks(data);
	mlx_loop(data->mlx);
}
