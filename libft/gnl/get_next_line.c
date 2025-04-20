/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:09:06 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/20 19:07:41 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static char	*fill_stash(int fd, char *stash)
{
	int		readed;
	char	*tmp;
	char	buff[BUFFER_SIZE + 1];

	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
		{
			free(stash);
			return (NULL);
		}
		buff[readed] = '\0';
		tmp = ft_strjoin_gnl(stash, buff);
		free(stash);
		stash = tmp;
		if (stash && ft_strchr_gnl(stash, '\n'))
			break ;
	}
	return (stash);
}

static char	*add_to_line(char *s)
{
	int		i;
	int		len_line;
	char	*line;

	if (!s || !*s)
		return (NULL);
	len_line = get_len_line(s);
	line = malloc(sizeof(char) * (len_line));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
	}
	else
		line[i] = '\0';
	return (line);
}

static char	*update_buffer(char *s)
{
	int		i;
	char	*stash;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	stash = ft_gnl_strdup(s + i + 1);
	free(s);
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (stash)
		{
			free(stash);
			stash = NULL;
		}
		return (NULL);
	}
	stash = fill_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = add_to_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = update_buffer(stash);
	return (line);
}
