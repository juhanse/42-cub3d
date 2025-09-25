/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:06:18 by juhanse           #+#    #+#             */
/*   Updated: 2025/09/25 11:59:57 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static char	*ft_malloc_textures(char *s)
{
	int		i;
	int		j;
	int		space;
	char	*buffer;

	i = -1;
	space = 0;
	while (s[++i])
		if (s[i] == ' ' || s[i] == '\t')
			space++;
	buffer = malloc((ft_strlen(s) - space + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\r')
			buffer[j++] = s[i];
	buffer[j] = '\0';
	return (buffer);
}

static char	*ft_merge_split(char **split)
{
	char	*tmp;
	char	*joined;

	tmp = split[1];
	joined = ft_strjoin(split[1], split[2]);
	free(tmp);
	if (split[3])
	{
		tmp = joined;
		joined = ft_strjoin(joined, split[3]);
		free(tmp);
	}
	return (joined);
}

int	ft_get_config_color(t_data *data)
{
	int		i;
	char	**split;

	i = -1;
	while (++i < data->content_height)
	{
		split = ft_split(data->content[i], ' ');
		if (!ft_check_colors(data, split[0]))
			return (perror(ERR_DUP), ft_free_split(split), 0);
		if (split[0] && !ft_strncmp("F", split[0], 1) && split[1])
		{
			if (split[2])
				split[1] = ft_merge_split(split);
			data->floor_color = ft_parse_rgb(split[1]);
		}
		else if (split[0] && !ft_strncmp("C", split[0], 1) && split[1])
		{
			if (split[2])
				split[1] = ft_merge_split(split);
			data->ceiling_color = ft_parse_rgb(split[1]);
		}
		ft_free_split(split);
	}
	return (data->floor_color != -1 && data->ceiling_color != -1);
}

int	ft_get_config_texture(t_data *data)
{
	int		i;
	char	**split;

	i = -1;
	while (++i < data->content_height)
	{
		split = ft_split(data->content[i], ' ');
		if (!ft_check_textures(data, split[0]))
			return (perror(ERR_DUP), ft_free_split(split), 0);
		if (split[0] && !ft_strncmp("NO", split[0], 2) && split[1])
			data->north.path = ft_malloc_textures(split[1]);
		else if (split[0] && !ft_strncmp("SO", split[0], 2) && split[1])
			data->south.path = ft_malloc_textures(split[1]);
		else if (split[0] && !ft_strncmp("WE", split[0], 2) && split[1])
			data->west.path = ft_malloc_textures(split[1]);
		else if (split[0] && !ft_strncmp("EA", split[0], 2) && split[1])
			data->east.path = ft_malloc_textures(split[1]);
		ft_free_split(split);
	}
	if (!data->north.path || !data->south.path || !data->west.path \
		|| !data->east.path)
		return (0);
	return (1);
}
