/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:53:14 by juhanse           #+#    #+#             */
/*   Updated: 2024/10/26 18:47:22 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int val, size_t count)
{
	size_t			i;
	unsigned char	*buffer;

	i = 0;
	buffer = (unsigned char *)ptr;
	while (i < count)
	{
		buffer[i] = (unsigned char)val;
		i++;
	}
	return (ptr);
}
