/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:06:11 by juhanse           #+#    #+#             */
/*   Updated: 2025/09/25 11:49:03 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	ft_check_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (access(path, R_OK))
		return (1);
	if (path[len - 1] != 'b' || path[len - 2] != 'u' || path[len - 3] != 'c' \
		|| path[len - 4] != '.' || !ft_isalnum(path[len - 5]))
		return (1);
	return (0);
}

static void	ft_get_max_width(t_data *data)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	data->map_max_width = (int)ft_strlen(data->map[0]);
	while (data->map[++i])
	{
		len = (int)ft_strlen(data->map[i]);
		if (len > data->map_max_width)
			data->map_max_width = len;
	}
}

int	ft_initialize(t_data *data, char *path)
{
	if (ft_check_path(path))
		return (perror(ERR_BAD_PATH), 1);
	data->map_path = path;
	data->player = ft_calloc(1, sizeof(t_player));
	if (!data->player)
		return (perror(ERR_MALLOC), 1);
	data->minimap = ft_calloc(1, sizeof(t_mini));
	if (!data->minimap)
		return (free(data->player), perror(ERR_MALLOC), 1);
	if (!ft_fill_content(data))
		return (free(data->player), free(data->minimap), 1);
	data->ceiling_color = -1;
	data->floor_color = -1;
	if (!ft_get_config_texture(data) || !ft_get_config_color(data))
		return (ft_free_map(data, 1), perror(ERR_CONFIG), 1);
	if (!ft_fill_map(data))
		return (ft_free_map(data, 2), perror(ERR_MAP), 1);
	ft_get_max_width(data);
	if (!ft_found_player(data))
		return (ft_free_map(data, 3), perror(ERR_PLY_NOT_FOUND), 1);
	if (!ft_test_map(data))
		return (ft_free_map(data, 3), perror(ERR_MAP), 1);
	return (0);
}
