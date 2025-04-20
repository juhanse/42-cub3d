/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:57:23 by juhanse           #+#    #+#             */
/*   Updated: 2024/10/29 10:44:28 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int c, size_t size)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)ptr;
	while (i < size)
	{
		if (p[i] == (unsigned char)c)
			return ((void *)ptr + i);
		i++;
	}
	return (NULL);
}
