/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienhanse <julienhanse@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:47:35 by julienhanse       #+#    #+#             */
/*   Updated: 2024/10/30 00:09:39 by julienhanse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_digit(int n)
{
	size_t	i;
	int		temp;

	i = 0;
	temp = n;
	if (temp == 0)
		return (1);
	while (temp != 0)
	{
		temp = temp / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	num;
	size_t	digits;
	char	*buffer;

	num = n;
	digits = ft_count_digit(n);
	if (n < 0)
	{
		num *= -1;
		digits++;
	}
	buffer = (char *)malloc((digits + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[digits] = '\0';
	while (digits--)
	{
		buffer[digits] = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		buffer[0] = '-';
	return (buffer);
}
