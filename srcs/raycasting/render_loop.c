#include "../../cub3d.h"

void	update_player(t_data *data, float dx, float dy)
{
	float	new_x;
	float	new_y;

	new_x = data->player->p_x + (dx * SPEED);
	new_y = data->player->p_y + (dy * SPEED);

	if (valid_move(data, new_x, new_y))
	{
		data->player->p_x = new_x;
		data->player->p_y = new_y;
	}
}

int	render_loop(t_data *data)
{
	t_player	*player;
	float		d_x;
	float		d_y;

	player = data->player;
	d_x = 0;
	d_y = 0;
	if (player->moves.left_rot)
		player->p_angle -= ROT_SPEED;
	if (player->moves.right_rot)
		player->p_angle += ROT_SPEED;
	normalize_angle(player);
	update_player_dir(player);
	player->x_perp = -player->y_dir;
	player->y_perp = player->x_dir;
	if (player->moves.w_pressed)
	{
		d_x += player->x_dir;
		d_y += player->y_dir;
	}
	if (player->moves.a_pressed)
	{
		d_x -= player->x_perp;
		d_y -= player->y_perp;
	}
		
	if (player->moves.s_pressed)
	{
		d_x -= player->x_dir;
		d_y -= player->y_dir;
	}
	if (player->moves.d_pressed)
	{
		d_x += player->x_perp;
		d_y += player->y_perp;
	}
	update_player(data, d_x, d_y);
	render_screen(data);
	return (0);
}
