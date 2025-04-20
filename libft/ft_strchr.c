/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:39:28 by julienhanse       #+#    #+#             */
/*   Updated: 2024/10/29 10:44:41 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	search;

	i = 0;
	search = (char) c;
	while (s[i] && s[i] != search)
		i++;
	if (s[i] == search)
		return ((char *) s + i);
	return (NULL);
}
