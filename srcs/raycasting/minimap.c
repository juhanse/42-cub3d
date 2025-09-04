#include "../../cub3d.h"

void	render_screen(t_data *data);

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

int	out_of_map(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height)
		return (1);
	else
		return (0);
}

int	is_wall(t_data *data, int x, int y)
{
	if (data->map[y][x] == '1')
		return (1);
	else
		return (0);
}

int	valid_move(t_data *data, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (out_of_map(data, map_x, map_y) || is_wall(data, map_x, map_y))
		return (0);
	else
		return (1);
}

void	update_player(t_data *data, float dx, float dy)
{
	float	new_x;
	float	new_y;

	new_x = data->player->p_x + (dx * SPEED);
	new_y = data->player->p_y + (dy * SPEED);

	if (valid_move(data, new_x, new_y))
	{
		data->player->p_x = new_x;
		data->player->p_y = new_y;
	}
}

void	reset_black_img(t_data *data)
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
/* enlever ou retirer des tours complets */
void	normalize_angle(t_player *player)
{
	while (player->p_angle < 0)
		player->p_angle += 2 * M_PI;
	while (player->p_angle >= 2 * M_PI)
		player->p_angle -= 2 * M_PI;
	return ;
}

void	update_player_dir(t_player *player)
{
	player->x_dir = cos(player->p_angle);
    player->y_dir = sin(player->p_angle);
}

int	render_loop(t_data *data)
{
	t_player	*player;
	float		d_x;
	float		d_y;

	player = data->player;
	d_x = 0;
	d_y = 0;
	if (player->moves.left_rot)
		player->p_angle -= ROT_SPEED;
	if (player->moves.right_rot)
		player->p_angle += ROT_SPEED;
	normalize_angle(player);
	update_player_dir(player);
	player->x_perp = -player->y_dir;
	player->y_perp = player->x_dir;
	if (player->moves.w_pressed)
	{
		d_x += player->x_dir;
		d_y += player->y_dir;
	}
	if (player->moves.a_pressed)
	{
		d_x -= player->x_perp;
		d_y -= player->y_perp;
	}
		
	if (player->moves.s_pressed)
	{
		d_x -= player->x_dir;
		d_y -= player->y_dir;
	}
	if (player->moves.d_pressed)
	{
		d_x += player->x_perp;
		d_y += player->y_perp;
	}
	update_player(data, d_x, d_y);
	render_screen(data);
	return (0);
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
	centered_x = (int)((data->player->p_x * SIZE) - (p_size / 2));
	centered_y = (int)((data->player->p_y * SIZE) - (p_size / 2));
	draw_square(data, centered_x, centered_y, p_size, 0x2768F5);
}

// void	draw_vision(t_data *data)
// {
// 	int		pxl_start_x;
// 	int		pxl_start_y;
// 	int		pxl_end_x;
// 	int		pxl_end_y;
// 	float	x_dir;
// 	float	y_dir;
// 	float	distance;
// 	float	current_x;
// 	float	current_y;

// 	distance = 0.0f;
// 	pxl_start_x = (int)data->player->p_x * SIZE;
// 	pxl_start_y = (int)data->player->p_y * SIZE;
// 	x_dir = data->player->x_dir;
// 	y_dir = data->player->y_dir;
// 	while (distance < MAX_DIST)
// 	{
// 		current_x = data->player->p_x + (x_dir * distance / SIZE);
// 		current_y = data->player->p_y + (y_dir * distance / SIZE);
// 		if (!valid_move(data, current_x, current_y))
// 		{
// 			pxl_end_x = pxl_start_x + (int)(x_dir * distance);
// 			pxl_end_y = pxl_start_y + (int)(y_dir * distance);
// 			draw_line(data, pxl_start_x, pxl_start_y, pxl_end_x, pxl_end_y);
// 			return ;
// 		}
// 		distance += STEP;
// 	}
// }

void	draw_vision(t_data *data)
{
	int		pxl_x;
	int		pxl_y;
	float	x_dir;
	float	y_dir;
	float	distance;
	float	current_x;
	float	current_y;
	float	current_pxl_x;
	float	current_pxl_y;

	distance = 0.0f;
	pxl_x = (int)data->player->p_x * SIZE;
	pxl_y = (int)data->player->p_y * SIZE;
	x_dir = data->player->x_dir;
	y_dir = data->player->y_dir;
	while (distance < MAX_DIST)
	{
		current_pxl_x = pxl_x + ((int)x_dir * distance);
		current_pxl_y = pxl_y + ((int)y_dir * distance);
		put_pixel(data, current_pxl_x, current_pxl_y, 0x00FF00);
		current_x = data->player->p_x + (x_dir * distance / SIZE);
		current_y = data->player->p_y + (y_dir * distance / SIZE);
		if (!valid_move(data, current_x, current_y))
			break ;
		distance += STEP;
	}
}

void	render_screen(t_data *data)
{
	reset_black_img(data);
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