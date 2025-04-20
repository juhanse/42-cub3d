/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:14:11 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/20 19:07:48 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

int	ft_strchr_gnl(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] || c == '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_gnl_strdup(const char *src)
{
	int		i;
	int		len;
	char	*dest;

	if (!src)
		return (NULL);
	i = -1;
	len = ft_strlen_gnl(src);
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	while (++i < len)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	int		i;
	int		len_s1;
	int		len_s2;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_gnl_strdup(s2));
	if (!s2)
		return (ft_gnl_strdup(s1));
	len_s1 = ft_strlen_gnl(s1);
	len_s2 = ft_strlen_gnl(s2);
	str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		str[i] = s1[i];
	i--;
	while (++i < len_s1 + len_s2)
		str[i] = s2[i - len_s1];
	str[i] = '\0';
	return (str);
}

int	get_len_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (i + 2);
	return (i + 1);
}
