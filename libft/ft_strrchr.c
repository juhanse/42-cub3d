/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:46:31 by juhanse           #+#    #+#             */
/*   Updated: 2024/10/26 18:12:10 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	search;

	i = ft_strlen(s);
	search = (char) c;
	while (i >= 0)
	{
		if (s[i] == search)
			return ((char *) s + i);
		i--;
	}
	return (NULL);
}
