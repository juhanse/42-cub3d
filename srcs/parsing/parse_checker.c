/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:06:14 by juhanse           #+#    #+#             */
/*   Updated: 2025/09/24 14:06:16 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_check_textures(t_data *data, char *s)
{
	if (data->north.path && !ft_strncmp("NO", s, 2))
		return (0);
	else if (data->south.path && !ft_strncmp("SO", s, 2))
		return (0);
	else if (data->west.path && !ft_strncmp("WE", s, 2))
		return (0);
	else if (data->east.path && !ft_strncmp("EA", s, 2))
		return (0);
	return (1);
}

int	ft_check_colors(t_data *data, char *s)
{
	if (data->floor_color != -1 && !ft_strncmp("F", s, 1))
		return (0);
	else if (data->ceiling_color != -1 && !ft_strncmp("C", s, 1))
		return (0);
	return (1);
}

int	ft_parse_rgb(char *str)
{
	int		r;
	int		g;
	int		b;
	char	**split;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		return (ft_free_split(split), -1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	ft_free_split(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}
