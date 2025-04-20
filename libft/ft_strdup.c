/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:21:52 by julienhanse       #+#    #+#             */
/*   Updated: 2024/10/29 10:44:44 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*buffer;

	len = ft_strlen(src);
	buffer = (char *)malloc((len + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, src, len + 1);
	return (buffer);
}
