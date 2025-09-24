/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:03:14 by ade-woel          #+#    #+#             */
/*   Updated: 2025/09/24 14:03:15 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	out_of_map(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map_max_width || y < 0 || y >= data->map_height)
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

void	init_ray(t_ray *ray, t_player *player, float ray_angle)
{
	ray->start_x = player->p_x;
	ray->start_y = player->p_y;
	ray->map_x = (int)ray->start_x;
	ray->map_y = (int)ray->start_y;
	ray->dir_x = cos(ray_angle);
	ray->dir_y = sin(ray_angle);
}
