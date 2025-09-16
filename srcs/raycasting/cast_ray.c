#include "../../cub3d.h"

static void	get_wall_data(t_ray *ray, t_wall *wall)
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

static void	set_next_dist(t_ray *ray, float *next_x, float *next_y)
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

static float	set_delta_dist(float ray_dir)
{
	if (ray_dir == 0)
		return (1e30f);
	else
		return (fabs(1.0f / ray_dir));
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
