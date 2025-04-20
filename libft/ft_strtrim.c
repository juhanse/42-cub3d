/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:03:57 by julienhanse       #+#    #+#             */
/*   Updated: 2024/10/29 10:45:07 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	s1_len;
	char	*buffer;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	s1_len = ft_strlen(s1);
	while (ft_is_set(s1[i], set))
		i++;
	while (i < s1_len && ft_is_set(s1[s1_len - 1], set))
		s1_len--;
	buffer = (char *)malloc((s1_len - i + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, s1 + i, s1_len - i + 1);
	return (buffer);
}
