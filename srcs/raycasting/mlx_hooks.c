#include "../../cub3d.h"

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
		exit_game(data);
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
/*mlx_loop_hook continuous call through the mlx_loop vs mlx_hook triggers on events*/
void	set_hooks(t_data *data)
{
	mlx_hook(data->wnd, 2, 1L << 0, &key_press, data);
	mlx_hook(data->wnd, 3, 1L << 1, &key_release, data->player);
	mlx_hook(data->wnd, 17, 0, &exit_game, data);
	mlx_loop_hook(data->mlx, &render_loop, data);
}
