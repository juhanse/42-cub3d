/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:06:07 by juhanse           #+#    #+#             */
/*   Updated: 2025/09/24 14:06:10 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	ft_free_tmp_map(t_data *data, int len)
{
	while (--len >= 0)
		free(data->map_tmp[len]);
	free(data->map_tmp);
}

static char	*ft_fill_line(char *s, int max_width)
{
	int		i;
	int		len;
	char	*buffer;

	buffer = malloc(sizeof(char) * (max_width + 1));
	if (!buffer)
		return (NULL);
	len = ft_strlen(s);
	if (len > max_width)
		len = max_width;
	i = -1;
	while (++i < len)
		buffer[i] = s[i];
	while (i < max_width)
	{
		buffer[i] = ' ';
		i++;
	}
	buffer[max_width] = '\0';
	return (buffer);
}

static int	ft_fill_tmp_map(t_data *data)
{
	int	i;

	data->map_tmp = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map_tmp)
		return (0);
	i = -1;
	while (++i < data->map_height)
	{
		data->map_tmp[i] = ft_fill_line(data->map[i], data->map_max_width);
		if (!data->map_tmp[i])
			return (ft_free_tmp_map(data, i), 0);
	}
	data->map_tmp[i] = NULL;
	return (1);
}

void	ft_flood_fill(t_data *data, int x, int y)
{
	char	c;

	c = data->map_tmp[x][y];
	if (x < 0 || x >= data->map_height || y < 0 || y >= data->map_max_width)
		return (data->map_error = 1, (void)0);
	if (c != '0' && c != '1' && c != 'N' && c != 'S' \
		&& c != 'E' && c != 'W' && c != '2')
		return (data->map_error = 1, (void)0);
	if (x == 0 || x == data->map_height - 1 || y == 0 || \
		y == data->map_max_width - 1)
	{
		if (c != '1')
			data->map_error = 1;
		return ;
	}
	if (c == '1' || c == '2')
		return ;
	data->map_tmp[x][y] = '2';
	ft_flood_fill(data, x - 1, y);
	ft_flood_fill(data, x + 1, y);
	ft_flood_fill(data, x, y - 1);
	ft_flood_fill(data, x, y + 1);
}

int	ft_test_map(t_data *data)
{
	if (!ft_fill_tmp_map(data))
		return (0);
	ft_flood_fill(data, data->player->pos_y, data->player->pos_x);
	if (data->map_error)
		return (ft_free_tmp_map(data, data->map_height), 0);
	return (1);
}
