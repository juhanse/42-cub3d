#include "../../cub3d.h"

void	draw_background(t_data *data)
{
	int	x;
	int	y;

	x = MINI_X;
	y = MINI_Y;
	while (y < MINI_Y + MINI_SIZE)
	{
		while (x < MINI_X + MINI_SIZE)
		{
			put_pixel(data, x, y, 0);
			x++;
		}
		y++;
	}
}

// void	draw_map(t_data *data)
// {
	
// }

void	render_minimap(t_data *data)
{
	draw_background(data);
	//draw_map(data);
}
