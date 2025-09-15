#include "../../cub3d.h"

float	set_delta_dist(float ray_dir)
{
	if (ray_dir == 0)
		return (1e30f);
	else
		return (fabs(1.0f / ray_dir));
}

void	init_ray(t_ray *ray, t_player *player, float ray_angle)
{
	ray->start_x = player->p_x;
	ray->start_y = player->p_y;
	ray->map_x = (int)ray->start_x;
	ray->map_y = (int)ray->start_y;
	ray->dir_x = cos(ray_angle);
	ray->dir_y = sin(ray_angle);
}

void	set_next_dist(t_ray *ray, float *next_x, float *next_y)
{
	if (ray->dir_x < 0)
	{
		ray->x_side = -1;
		*next_x = (ray->start_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->x_side = 1;
		*next_x = (ray->map_x + 1.0f - ray->start_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->y_side = -1;
		*next_y = (ray->start_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->y_side = 1;
		*next_y = (ray->map_y + 1.0f - ray->start_y) * ray->delta_y;
	}
}

int	get_texture_id(int wall_side, int axis_side)
{
	if (wall_side == 0)
	{
		if (axis_side > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (axis_side > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

void	get_wall_data(t_ray *ray, t_wall *wall)
{
	if (ray->wall_side == 0)
	{
		wall->wall_dist = (ray->map_x - ray->start_x + (1 - ray->x_side) / 2) / ray->dir_x;
		wall->wall_col = ray->start_y + wall->wall_dist * ray->dir_y;
		wall->texture_id = get_texture_id(0, ray->x_side);
	}
	else
	{
		wall->wall_dist = (ray->map_y - ray->start_y + (1 - ray->y_side) / 2) / ray->dir_y;	
		wall->wall_col = ray->start_x + wall->wall_dist * ray->dir_x;
		wall->texture_id = get_texture_id(1, ray->y_side);
	}
	wall->wall_col -= floor(wall->wall_col);
}

t_ray	cast_ray(t_data *data, float ray_angle)
{
	float		next_x_dist;
	float		next_y_dist;
	t_ray		ray;
	t_player	*player;

	ray = (t_ray){0};
	player = data->player;
	init_ray(&ray, player, ray_angle);
	ray.delta_x = set_delta_dist(ray.dir_x);
	ray.delta_y = set_delta_dist(ray.dir_y);
	set_next_dist(&ray, &next_x_dist, &next_y_dist);
	while (ray.hit == 0)
	{
		if (next_x_dist < next_y_dist)
		{
			next_x_dist += ray.delta_x;
			ray.map_x += ray.x_side;
			ray.wall_side = 0;
		}
		else 
		{
			next_y_dist += ray.delta_y;
			ray.map_y += ray.y_side;
			ray.wall_side = 1;
		}
		if (!valid_move(data, ray.map_x, ray.map_y))
			ray.hit	= 1;
	}
	get_wall_data(&ray, &ray.wall);
	return (ray);
}

int	get_texture_color(t_img *texture, int tex_x, int tex_y)
{
	int	index;
	int	color;

	if (tex_x < 0 || tex_x >= texture->width || tex_y < 0 || tex_y >= texture->height)
		return (0);
	index = tex_y * texture->size_line + tex_x * (texture->bpp / 8);
	color = (texture->data[index + 2] << 16) |
			(texture->data[index + 1] << 8) |
			(texture->data[index + 0]);
	return (color);
}

t_img	*get_texture(t_data *data, int texture_id)
{
	if (texture_id == NORTH)
		return (&data->north);
	else if (texture_id == SOUTH)
		return (&data->south);
	else if (texture_id == WEST)
		return (&data->west);
	else if (texture_id == EAST)
		return (&data->east);
	return (&data->north);
}

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

	wall_height = (int)(SCREEN_HEIGHT / ray->wall.fixed_dist);
	wall_start = SCREEN_CENTER - wall_height / 2;
	wall_end = SCREEN_CENTER + wall_height / 2;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end >= SCREEN_HEIGHT)
		wall_end = SCREEN_HEIGHT - 1;
	//wall_color = get_color(ray->wall.texture_id);
	text = get_texture(data, ray->wall.texture_id);
	text_x = (int)(ray->wall.wall_col * text->width);
	if (text_x >= text->width)
		text_x = text->width - 1;
	text_step = (float)text->height / wall_height;
	text_yf = (wall_start - SCREEN_CENTER + wall_height / 2) * text_step;
	y = -1;
	while (++y < SCREEN_HEIGHT)
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
			wall_color = get_text_color(text, text_x, text_y);
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
	while (++x < SCREEN_WIDTH)
	{
		center_offset = 2 * x / (float)SCREEN_WIDTH - 1;
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
