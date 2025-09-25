/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:03:03 by ade-woel          #+#    #+#             */
/*   Updated: 2025/09/24 14:03:04 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	handle_text(t_data *data, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(data->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Texture load failed: %s\n", path);
		return (1);
	}
	tex->data = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->s_line, &tex->endian);
	if (!tex->data)
		return (1);
	return (0);
}

static int	upload_textures(t_data *data)
{
	if (handle_text(data, &data->north, data->north.path))
		return (1);
	if (handle_text(data, &data->south, data->south.path))
		return (1);
	if (handle_text(data, &data->west, data->west.path))
		return (1);
	if (handle_text(data, &data->east, data->east.path))
		return (1);
	return (0);
}

static int	init_mouse(t_data *data)
{
	if (mlx_mouse_get_pos(data->mlx, data->wnd,
			&data->player->moves.mouse_x, &data->player->moves.mouse_y) == -1)
		return (1);
	data->player->moves.last_mouse_x = data->player->moves.mouse_x;
	return (0);
}

static int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->wnd = mlx_new_window(data->mlx, SCRN_WIDTH, SCRN_HEIGHT, WND_NAME);
	if (!data->wnd)
		return (1);
	data->mlx_img.img = mlx_new_image(data->mlx, SCRN_WIDTH, SCRN_HEIGHT);
	if (!data->mlx_img.img)
		return (1);
	data->mlx_img.data = mlx_get_data_addr(data->mlx_img.img,
			&data->mlx_img.bpp, &data->mlx_img.s_line, &data->mlx_img.endian);
	if (!data->mlx_img.data)
		return (1);
	if (init_mouse(data))
		return (1);
	mlx_put_image_to_window(data->mlx, data->wnd, data->mlx_img.img, 0, 0);
	return (0);
}

void	play_game(t_data *data)
{
	if (init_mlx(data) || upload_textures(data))
	{
		data->exit_code = 1;
		exit_game(data);
	}
	set_hooks(data);
	mlx_loop(data->mlx);
}
