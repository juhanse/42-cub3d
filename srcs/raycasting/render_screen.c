/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:03:09 by ade-woel          #+#    #+#             */
/*   Updated: 2025/09/24 14:03:10 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	measure_wall(t_ray *ray)
{
	ray->wall.wall_height = (int)(SCRN_HEIGHT / ray->wall.fixed_dist);
	ray->wall.wall_start = SCRN_CENTER - ray->wall.wall_height / 2;
	ray->wall.wall_end = SCRN_CENTER + ray->wall.wall_height / 2;
	if (ray->wall.wall_start < 0)
		ray->wall.wall_start = 0;
	if (ray->wall.wall_end >= SCRN_HEIGHT)
		ray->wall.wall_end = SCRN_HEIGHT - 1;
}

static void	draw_wall_col(t_data *data, t_ray *ray, int x)
{
	int		y;
	t_img	*text;

	measure_wall(ray);
	text = get_texture(data, ray->wall.texture_id);
	prep_texture(text, ray);
	y = -1;
	while (++y < SCRN_HEIGHT)
	{
		if (y < ray->wall.wall_start)
			put_pixel(data, x, y, data->ceiling_color);
		else if (y >= ray->wall.wall_start && y <= ray->wall.wall_end)
		{
			update_text_y(text);
			ray->wall.wall_color = get_color(text, text->text_x, text->text_y);
			put_pixel(data, x, y, ray->wall.wall_color);
			text->text_yf += text->text_step;
		}
		else
			put_pixel(data, x, y, data->floor_color);
	}
}

static void	render_3d(t_data *data)
{
	int			x;
	float		rad_fov;
	float		center_offset;
	float		ray_angle;
	t_ray		ray;

	x = -1;
	rad_fov = (FOV * M_PI / 180.0f);
	while (++x < SCRN_WIDTH)
	{
		center_offset = 2 * x / (float)SCRN_WIDTH - 1;
		ray_angle = data->player->p_angle
			+ atan(center_offset * tan(rad_fov / 2));
		ray = cast_ray(data, ray_angle);
		ray.wall.fixed_dist = ray.wall.wall_dist
			* cos(ray_angle - data->player->p_angle);
		draw_wall_col(data, &ray, x);
	}
}

void	render_screen(t_data *data)
{
	//reset_black(data);
	render_3d(data);
	render_minimap(data);
	mlx_put_image_to_window(data->mlx, data->wnd, data->mlx_img.img, 0, 0);
}
