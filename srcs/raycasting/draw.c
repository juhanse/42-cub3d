/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:02:50 by ade-woel          #+#    #+#             */
/*   Updated: 2025/09/25 10:45:52 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	int	index;

	if (x >= 0 && x < SCRN_WIDTH && y >= 0 && y < SCRN_HEIGHT)
	{
		index = y * data->mlx_img.s_line + x * (data->mlx_img.bpp / 8);
		data->mlx_img.data[index + 0] = (color >> 0) & 0xFF;
		data->mlx_img.data[index + 1] = (color >> 8) & 0xFF;
		data->mlx_img.data[index + 2] = (color >> 16) & 0xFF;
		data->mlx_img.data[index + 3] = (char)255;
	}
	else
		return ;
}

void	put_mini_pixel(t_data *data, int x, int y, int color)
{
	int	index;
	int	mini_x;

	mini_x = (SCRN_WIDTH - MINI_SIZE - MINI_MARGIN);
	if (x >= mini_x && x < mini_x + MINI_SIZE
		&& y >= MINI_Y && y < MINI_Y + MINI_SIZE
		&& x >= 0 && x < SCRN_WIDTH && y >= 0 && y < SCRN_HEIGHT)
	{
		index = y * data->mlx_img.s_line + x * (data->mlx_img.bpp / 8);
		data->mlx_img.data[index + 0] = (color >> 0) & 0xFF;
		data->mlx_img.data[index + 1] = (color >> 8) & 0xFF;
		data->mlx_img.data[index + 2] = (color >> 16) & 0xFF;
		data->mlx_img.data[index + 3] = (char)255;
	}
	else
		return ;
}
