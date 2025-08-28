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
			put_pixel(data, x + i, y, color);
			j++;
		}
		i++;
	}
}

// void	render(t_data *data)
// {
// 	//draw_square(data, 0, 0, )
// }

void	minimap(t_data *data)
{
	//render(&data);
	draw_square(data, data->player->p_x, data->player->p_y, 5, 0x2768F5);
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
