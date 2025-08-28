#include "../cub3d.h"

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
			put_pixel(data, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_grid(t_data *data, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = x;
	while (i < x + size)
	{
		put_pixel(data, i, y, color);
		put_pixel(data, i, y + size - 1, color);
		i++;
	}
	j = y;
	while (j < y + size)
	{
		put_pixel(data, x, j, color);
		put_pixel(data, x + size - 1, j, color);
		j++;
	}
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == '1')
				draw_square(data, x * SIZE, y * SIZE, SIZE, 0xD327F5);
			else
				draw_square(data, x * SIZE, y * SIZE, SIZE, 0xFFFFFF);
			draw_grid(data, x * SIZE, y * SIZE, SIZE, 0x000000);
		}
	}
}

void	draw_player(t_data *data)
{
	int	centered_x;
	int	centered_y;
	int	p_size;

	p_size = 10;
	printf("Player position: x=%.2f, y=%.2f\n", data->player->p_x, data->player->p_y);
	centered_x = (int)((data->player->p_x * SIZE) + (SIZE / 2) - (p_size / 2));
	centered_y = (int)((data->player->p_y * SIZE) + (SIZE / 2) - (p_size / 2));
	printf("Drawing at: x=%d, y=%d\n", centered_x, centered_y);
	draw_square(data, centered_x, centered_y, p_size, 0x2768F5);
}

void	minimap(t_data *data)
{
	draw_map(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->wnd, data->mlx_img.img, 0, 0);
	mlx_loop(data->mlx);
}

/* MLX_GET_DATA_ADDR */
/* rend un ptr vers le debut du buffer de donnees brutes en memoire pour stocker l'image ; */
/* c'est un tableau d'octets contigus en memoire */
/* bpp = bits per pixel ; bits pour stocker un pixel (32 RGBA) */
/* size_line ; octets pour stocker une ligne de l'image ; largeur × (bpp ÷ 8) */
/* endian ; ordre des octets en memoire */

/* MLX_NEW_IMAGE*/
/* Alloue un tampon pour peindre une image */
/* Possible de creer des couches d'images */
