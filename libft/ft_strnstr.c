/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:06:54 by juhanse           #+#    #+#             */
/*   Updated: 2024/10/27 13:19:13 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;
	size_t	len_haystack;

	if (!*needle)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	len_needle = ft_strlen(needle);
	len_haystack = ft_strlen(haystack);
	if (len > len_haystack)
		len = len_haystack;
	while (len >= len_needle)
	{
		if (ft_strncmp(haystack, needle, len_needle) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
