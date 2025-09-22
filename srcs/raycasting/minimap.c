#include "../../cub3d.h"

void	draw_background(t_data *data, t_mini *mini)
{
	int	x;
	int	y;

	y = MINI_Y;
	while (y < MINI_Y + MINI_SIZE)
	{
		x = mini->mini_x;
		while (x < mini->mini_x + MINI_SIZE)
		{
			put_pixel(data, x, y, 0x333333);
			x++;
		}
		y++;
	}
}
/*set the real size of the map with the scale of the mini
then the empty spaces to center the map*/
void	draw_map(t_data *data, t_mini *mini)
{
	int		x;
	int		y;

	mini->scale = set_scale(data);
	mini->width_pxl = data->map_max_width * mini->scale;
	mini->height_pxl = data->map_height * mini->scale;
	mini->offset_x = (MINI_SIZE - mini->width_pxl) / 2;
	mini->offset_y = (MINI_SIZE - mini->height_pxl) / 2;
	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_max_width)
		{
			mini->pxl_x = mini->mini_x + mini->offset_x + x * mini->scale;
			mini->pxl_y = MINI_Y + mini->offset_y + y * mini->scale;
			draw_cell(data, x, y);
		}
	}
}

void	draw_player(t_data *data, t_mini *mini)
{
	int		x;
	int		y;
	int		dx;
	int		dy;

	mini->px = mini->mini_x + mini->offset_x
		+ (int)(data->player->p_x * mini->scale);
	mini->py = MINI_Y + mini->offset_y + (int)(data->player->p_y * mini->scale);
	dy = -P_SIZE;
	while (dy <= P_SIZE)
	{
		dx = -P_SIZE;
		while (dx <= P_SIZE)
		{
			x = mini->px + dx;
			y = mini->py + dy;
			put_mini_pixel(data, x, y, 0xDB0D0D);
			dx++;
		}
		dy++;
	}
	draw_vision_ray(data, mini);
}

void	render_minimap(t_data *data)
{
	t_mini	*mini;

	mini = data->minimap;
	mini->mini_x = (SCRN_WIDTH - MINI_SIZE - MINI_MARGIN);
	draw_background(data, mini);
	draw_map(data, mini);
	draw_player(data, mini);
}
