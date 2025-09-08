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
	centered_x = (int)((data->player->p_x * SIZE) - (p_size / 2));
	centered_y = (int)((data->player->p_y * SIZE) - (p_size / 2));
	draw_square(data, centered_x, centered_y, p_size, 0x2768F5);
}

void	draw_vision(t_data *data)
{
	int		pxl_x;
	int		pxl_y;
	int		current_pxl_x;
	int		current_pxl_y;
	float	x_dir;
	float	y_dir;
	float	distance;
	float	current_x;
	float	current_y;

	distance = 0.0f;
	pxl_x = (int)(data->player->p_x * SIZE);
	pxl_y = (int)(data->player->p_y * SIZE);
	x_dir = data->player->x_dir;
	y_dir = data->player->y_dir;
	while (distance < MAX_DIST)
	{
		current_pxl_x = pxl_x + (int)(x_dir * distance);
		current_pxl_y = pxl_y + (int)(y_dir * distance);
		put_pixel(data, current_pxl_x, current_pxl_y, 0xDB0404);
		current_x = data->player->p_x + (x_dir * distance / SIZE);
		current_y = data->player->p_y + (y_dir * distance / SIZE);
		if (!valid_move(data, current_x, current_y))
			break ;
		distance += STEP;
	}
}

void	render_minimap(t_data *data)
{
	reset_black(data);
	draw_map(data);
	draw_player(data);
	draw_vision(data);
	mlx_put_image_to_window(data->mlx, data->wnd, data->mlx_img.img, 0, 0);
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

/* VECTEUR DIR */
/* cos -> projection sur x // sin -> projection sur y */

/* STRAFING */
/* Mouvement lateral sans tourner */
/* Permet mouvements plus libres en gardant l'orientation visuelle */
/* Axes de direction relatifs au joueur au lieu de rester fixes */
/* On dessine un rayon perpendiculaire a la direction pour definir la D et la G */
/* EXEMPLE */
/* dir_x = 1, dir_y = 0 (EST) 
perp_x = -dir_y = 0 perp_y = dir_x = 1 // (0, 1) = SUD
A (gauche) : delta -= (0, 1) = (0, -1) = NORD
D (droite) : delta += (0, 1) = (0, 1) = SUD */