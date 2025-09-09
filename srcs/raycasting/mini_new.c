#include "../../cub3d.h"

void	draw_square(t_data *data, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = y;
	while (i < y + size)
	{
		j = x;
		while (j < x + size)
		{
			put_mini_pixel(data, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_border(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int y;
	int	size;

	x = MINI_X - MINI_BORDER;
	y = MINI_Y - MINI_BORDER;
	i = y;
	size = MINI_SIZE + 2 * MINI_BORDER;
	while (i < y + size)
	{
		j = x;
		while (j < x + size)
		{
			put_mini_pixel(data, j, i, 0);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_data *data)
{
	draw_border(data);
	//draw_map(data);
}
