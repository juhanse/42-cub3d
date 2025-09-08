#include "../../cub3d.h"

int	get_color(int texture_id)
{
	int base_colors[] = {
		0xFF0000,  // NORTH - Rouge
		0x0000FF,  // SOUTH - Bleu
		0x00FF00,  // WEST - Vert
		0xFFFF00   // EAST - Jaune
	};
	int color = base_colors[texture_id];
	return (color);
}

void	reset_black(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel(data, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	int	index;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		index = y * data->mlx_img.size_line + x * (data->mlx_img.bpp / 8);
		data->mlx_img.data[index + 0] = (color >> 0) & 0xFF;
		data->mlx_img.data[index + 1] = (color >> 8) & 0xFF;
		data->mlx_img.data[index + 2] = (color >> 16) & 0xFF;
		data->mlx_img.data[index + 3] = 255;
	}
	else
		return ;
}
