/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:44:16 by julienhanse       #+#    #+#             */
/*   Updated: 2024/10/29 10:44:48 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buffer;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	buffer = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, s1, s1_len + 1);
	ft_strlcat(buffer, s2, s1_len + s2_len + 1);
	return (buffer);
}
