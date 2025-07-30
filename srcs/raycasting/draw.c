#include "../cub3d.h"

char	*get_direction(t_data *data, t_wall wall)
{
	char *direction;

	if (wall.orientation == NORTH)
		direction = data->north.pxl_data;
	else if (wall.orientation == SOUTH)
		direction = data->south.pxl_data;
	else if (wall.orientation == WEST)
		direction = data->west.pxl_data;
	else
		direction = data->east.pxl_data;
	return (direction);
}

void	put_pixel(t_data *data, int x, int i, int color)
{
	int	pxl_index;

	if (x >=0 && x < SCREEN_WIDTH && i >= 0 && i < SCREEN_HEIGHT)
	{
		pxl_index = (i * SCREEN_WIDTH + x) * 4;
		data->mlx_img.pxl_data[pxl_index + 0] = (color >> 0) & 0xFF;
		data->mlx_img.pxl_data[pxl_index + 1] = (color >> 8) & 0xFF;
		data->mlx_img.pxl_data[pxl_index + 2] = (color >> 16) & 0xFF;
		data->mlx_img.pxl_data[pxl_index + 3] = 255;
	}
}

int	get_text_pxl(char *texture_data, int text_width, int text_x, int text_y)
{
	int pxl_index;
	int	blue;
	int	green;
	int	red;

	if (text_x < 0 || text_x >= text_width)
		return (0);
	pxl_index = (text_y * text_width + text_x) * 4;
	blue = texture_data[pxl_index + 0] & 0xFF;
	green = texture_data[pxl_index + 1] & 0xFF;
	red = texture_data[pxl_index + 2] & 0xFF;

	return (red << 16) | (green << 8) | blue;
}

void	draw_ceiling(t_data *data, int x, int start_draw, int end_draw)
{
	int i;

	(void)start_draw;
	i = -1;
	while (++i < end_draw)
		put_pixel(data, x, i, data->ceiling_color);
}

void	draw_wall(t_data *data, t_wall wall, int x, int start_draw, int end_draw)
{
	int		i;
	int		text_x;
	int		text_y;
	int		color;
	char	*text_data;
	float	text_pos;

	i = start_draw;
	text_data = get_direction(data, wall);
	text_x = (int)(wall.texture_x * 64);
	while (i < end_draw)
	{
		text_pos = (float)(i - start_draw) / (end_draw - start_draw);
		text_y = (int)(text_pos * 64);
		color = get_text_pxl(text_data, 64, text_x, text_y);
		put_pixel(data, x, i, color);
	}
}

void	draw_floor(t_data *data, int x, int start_draw, int end_draw)
{
	int i;

	(void)start_draw;
	i = end_draw;
	while (i < SCREEN_HEIGHT)
	{
		put_pixel(data, x, i, data->floor_color);
		i++;
	}
}
