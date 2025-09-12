#include "../../cub3d.h"

/* enlever ou retirer des tours complets */
void	normalize_angle(t_player *player)
{
	while (player->p_angle < 0)
		player->p_angle += 2 * M_PI;
	while (player->p_angle >= 2 * M_PI)
		player->p_angle -= 2 * M_PI;
	return ;
}

void	update_player_dir(t_player *player)
{
	player->x_dir = cos(player->p_angle);
    player->y_dir = sin(player->p_angle);
}

int	out_of_map(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map_max_width || y < 0 || y >= data->map_height)
		return (1);
	else
		return (0);
}

int	is_wall(t_data *data, int x, int y)
{
	if (data->map[y][x] == '1')
		return (1);
	else
		return (0);
}

int	valid_move(t_data *data, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (out_of_map(data, map_x, map_y) || is_wall(data, map_x, map_y))
		return (0);
	else
		return (1);
}
