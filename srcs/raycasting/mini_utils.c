#include "../../cub3d.h"

int	set_scale(t_data *data)
{
	int	scale;
	int	scale_x;
	int	scale_y;

	scale_x = MINI_SIZE / data->map_max_width;
	scale_y = MINI_SIZE / data->map_height;
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	if (scale < 1)
		scale = 1;
	return (scale);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	draw_cell(t_data *data, int m_x, int m_y)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	t_mini	*mini;

	mini = data->minimap;
	dy = -1;
	while (++dy < mini->scale)
	{
		dx = -1;
		while (++dx < mini->scale)
		{
			x = mini->pxl_x + dx;
			y = mini->pxl_y + dy;
			if (data->map[m_y][m_x] == '1')
				put_mini_pixel(data, x, y, 0x8431D6);
			else if (data->map[m_y][m_x] == '0'
				|| is_player(data->map[m_y][m_x]))
				put_mini_pixel(data, x, y, 0xD1C5D9);
		}
	}
}

void	draw_vision_ray(t_data *data, t_mini *mini)
{
	int		i;
	int		x;
	int		y;
	int		end_x;
	int		end_y;

	mini->vision_length = P_SIZE * 10;
	end_x = mini->px + (int)(cos(data->player->p_angle) * mini->vision_length);
	end_y = mini->py + (int)(sin(data->player->p_angle) * mini->vision_length);
	i = -1;
	while (++i <= mini->vision_length)
	{
		x = mini->px + (end_x - mini->px) * i / mini->vision_length;
		y = mini->py + (end_y - mini->py) * i / mini->vision_length;
		put_mini_pixel(data, x, y, 0x2BA13C);
	}
}
