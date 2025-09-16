#include "../../cub3d.h"

void	reset_black(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCRN_HEIGHT)
	{
		x = 0;
		while (x < SCRN_WIDTH)
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

	if (x >= 0 && x < SCRN_WIDTH && y >= 0 && y < SCRN_HEIGHT)
	{
		index = y * data->mlx_img.s_line + x * (data->mlx_img.bpp / 8);
		data->mlx_img.data[index + 0] = (color >> 0) & 0xFF;
		data->mlx_img.data[index + 1] = (color >> 8) & 0xFF;
		data->mlx_img.data[index + 2] = (color >> 16) & 0xFF;
		data->mlx_img.data[index + 3] = (char)255;
	}
	else
		return ;
}

void	put_mini_pixel(t_data *data, int x, int y, int color)
{
	int	index;

	if (x >= MINI_X && x < MINI_X + MINI_SIZE
		&& y >= MINI_Y && y < MINI_Y + MINI_SIZE
		&& x >= 0 && x < SCRN_WIDTH && y >= 0 && y < SCRN_HEIGHT)
	{
		index = y * data->mlx_img.s_line + x * (data->mlx_img.bpp / 8);
		data->mlx_img.data[index + 0] = (color >> 0) & 0xFF;
		data->mlx_img.data[index + 1] = (color >> 8) & 0xFF;
		data->mlx_img.data[index + 2] = (color >> 16) & 0xFF;
		data->mlx_img.data[index + 3] = (char)255;
	}
	else
		return ;
}
