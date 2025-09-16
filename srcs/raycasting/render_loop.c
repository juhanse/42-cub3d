#include "../../cub3d.h"

static void	apply_movement(float *d_x, float *d_y, t_player *player)
{
	if (player->moves.w_pressed)
	{
		*d_x += player->x_dir;
		*d_y += player->y_dir;
	}
	if (player->moves.a_pressed)
	{
		*d_x -= player->x_perp;
		*d_y -= player->y_perp;
	}
	if (player->moves.s_pressed)
	{
		*d_x -= player->x_dir;
		*d_y -= player->y_dir;
	}
	if (player->moves.d_pressed)
	{
		*d_x += player->x_perp;
		*d_y += player->y_perp;
	}
}

void	update_player_dir(t_player *player)
{
	player->x_dir = cos(player->p_angle);
	player->y_dir = sin(player->p_angle);
}

static void	update_player(t_data *data, float dx, float dy)
{
	float	new_x;
	float	new_y;

	new_x = data->player->p_x + (dx * SPEED);
	new_y = data->player->p_y + (dy * SPEED);
	if (valid_move(data, new_x, data->player->p_y))
		data->player->p_x = new_x;
	if (valid_move(data, data->player->p_x, new_y))
		data->player->p_y = new_y;
}

/* add or substract full circles */
static void	normalize_angle(t_player *player)
{
	while (player->p_angle < 0)
		player->p_angle += 2 * M_PI;
	while (player->p_angle >= 2 * M_PI)
		player->p_angle -= 2 * M_PI;
	return ;
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
	apply_movement(&d_x, &d_y, player);
	update_player(data, d_x, d_y);
	render_screen(data);
	return (0);
}
