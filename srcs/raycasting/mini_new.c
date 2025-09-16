#include "../../cub3d.h"

void	draw_background(t_data *data)
{
	int	x;
	int	y;

	y = MINI_Y;
	while (y < MINI_Y + MINI_SIZE)
	{
		x = MINI_X;
		while (x < MINI_X + MINI_SIZE)
		{
			put_pixel(data, x, y, 0x333333);
			x++;
		}
		y++;
	}
}

int	set_scale(t_data *data)
{
	int scale;
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
	if (c == 'N' || c == 'S' || c == ' W' || c == 'E')
		return (1);
	return (0);
}

void	draw_cell(t_data *data, int m_x, int m_y)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
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
			else if (data->map[m_y][m_x] == '0' || is_player(data->map[m_y][m_x]))
				put_mini_pixel(data, x, y, 0xD1C5D9);
		}
	}
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;
	t_mini	*mini;

	mini = data->minimap;
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
			mini->pxl_x = MINI_X + mini->offset_x + x * mini->scale;
            mini->pxl_y = MINI_Y + mini->offset_y + y * mini->scale;
			draw_cell(data, x, y);
		}
	}
}

void	draw_vision_ray(t_data *data)
{
	int	i;
	int	x;
	int	y;
	int	length;
	int	end_x;
	int	end_y;
	t_mini	*mini;

	mini = data->minimap;
	length = P_SIZE * 10;
	end_x = mini->px + (int)(cos(data->player->p_angle) * length); 
	end_y = mini->py + (int)(sin(data->player->p_angle) * length);
	i = -1;
	while (++i <= length)
	{
		x = mini->px + (end_x - mini->px) * i / length;
		y = mini->py + (end_y - mini->py) * i / length;
		put_mini_pixel(data, x, y, 0x2BA13C);
	}
}

void	draw_player(t_data *data)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	t_mini	*mini;

	mini = data->minimap;
	mini->px = MINI_X + mini->offset_x + (int)(data->player->p_x * mini->scale);
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
	draw_vision_ray(data);
}

void	render_minimap(t_data *data)
{
	draw_background(data);
	draw_map(data);
	draw_player(data);
}
