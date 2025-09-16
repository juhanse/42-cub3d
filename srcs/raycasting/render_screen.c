#include "../../cub3d.h"

void	draw_wall_col(t_data *data, t_ray *ray, int x)
{
	int	wall_start;
	int	wall_end;
	int wall_height;
	int wall_color;
	int	y;
	int	text_x;
	int	text_y;
	float	text_step;
	float	text_yf;
	t_img	*text;

	wall_height = (int)(SCRN_HEIGHT / ray->wall.fixed_dist);
	wall_start = SCRN_CENTER - wall_height / 2;
	wall_end = SCRN_CENTER + wall_height / 2;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end >= SCRN_HEIGHT)
		wall_end = SCRN_HEIGHT - 1;
	text = get_texture(data, ray->wall.texture_id);
	text_x = (int)(ray->wall.wall_col * text->width);
	if (text_x >= text->width)
		text_x = text->width - 1;
	text_step = (float)text->height / wall_height;
	text_yf = (wall_start - SCRN_CENTER + wall_height / 2) * text_step;
	y = -1;
	while (++y < SCRN_HEIGHT)
	{
		if (y < wall_start)
			put_pixel(data, x, y, data->ceiling_color);
		else if (y >= wall_start && y <= wall_end)
		{
			text_y = (int)text_yf;
			if (text_y >= text->height)
				text_y = text->height - 1;
			if (text_y < 0)
				text_y = 0;
			wall_color = get_texture_color(text, text_x, text_y);
			put_pixel(data, x, y, wall_color);
			text_yf += text_step;
		}
		else
			put_pixel(data, x, y, data->floor_color);
	}
}

static void	render_3d(t_data *data)
{
	int			x;
	float		center_offset;
	float		ray_angle;
	t_ray		ray;
	t_player	*player;

	x = -1;
	player = data->player;
	while (++x < SCRN_WIDTH)
	{
		center_offset = 2 * x / (float)SCRN_WIDTH - 1;
		ray_angle = player->p_angle + atan(center_offset * tan(RAD_FOV / 2));
		ray = cast_ray(data, ray_angle);
		ray.wall.fixed_dist = ray.wall.wall_dist * cos(ray_angle - player->p_angle);
		draw_wall_col(data, &ray, x);
	}
}

void	render_screen(t_data *data)
{
	reset_black(data);
	render_3d(data);
	render_minimap(data);
	mlx_put_image_to_window(data->mlx, data->wnd, data->mlx_img.img, 0, 0);
}
