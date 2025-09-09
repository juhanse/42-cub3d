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

	scale_x = MINI_SIZE / data->map_width;
	scale_y = MINI_SIZE / data->map_height;
    // printf("=== CALCUL ÉCHELLE ===\n");
    // printf("MINI_SIZE: %d\n", MINI_SIZE);
    // printf("Map dimensions: %d×%d\n", data->map_width, data->map_height);
    // printf("scale_x = %d / %d = %d\n", MINI_SIZE, data->map_width, scale_x);
    // printf("scale_y = %d / %d = %d\n", MINI_SIZE, data->map_height, scale_y);
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	if (scale < 1)
		scale = 1;
	// if (scale > 12)
	// 	scale = 12;
	// printf("Échelle finale: %d pixels/case\n", scale);
    // printf("Taille finale carte: %d×%d pixels\n", 
    //        data->map_width * scale, data->map_height * scale);
    // printf("=====================\n");
	return (scale);
}

void	draw_cell(t_data *data, t_mini *mini, int m_x, int m_y)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

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
			else
				put_mini_pixel(data, x, y, 0xD1C5D9);
		}
	}
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;
	t_mini	mini;

	mini.scale = set_scale(data);
	mini.width_pxl = data->map_width * mini.scale;
	mini.height_pxl = data->map_height * mini.scale;
	mini.offset_x = (MINI_SIZE - mini.width_pxl) / 2;
	mini.offset_y = (MINI_SIZE - mini.height_pxl)/ 2;
	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			mini.pxl_x = MINI_X + mini.offset_x + x * mini.scale;
			mini.pxl_y = MINI_Y + mini.offset_y + y * mini.scale;
			//draw_cell(data, &mini, x, y);
			int color;
            if (x >= (int)strlen(data->map[y]))
                color = 0xFF00FF;  // Magenta = zone invalide
            else if (data->map[y][x] == '1')
                color = 0xFF0000;  // Rouge = mur
            else if (data->map[y][x] == '0')
                color = 0x00FF00;  // Vert = sol
            else
                color = 0x0000FF;  // Bleu = autre caractère
            
            // Dessiner la case avec la couleur debug
            for (int dy = 0; dy < mini.scale; dy++)
            {
                for (int dx = 0; dx < mini.scale; dx++)
                {
                    put_mini_pixel(data, mini.pxl_x + dx, mini.pxl_y + dy, color);
                }
			}
		}
	}
}

void	render_minimap(t_data *data)
{
	draw_background(data);
	draw_map(data);
}
