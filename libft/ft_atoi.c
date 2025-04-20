/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:20:59 by julienhanse       #+#    #+#             */
/*   Updated: 2024/10/29 10:43:30 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_overflow(long sign)
{
	if (sign > 0)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	sign;
	long	tmp;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = result;
		result = (result * 10) + (str[i] - 48);
		if (tmp > result)
			return (ft_overflow(sign));
		i++;
	}
	return ((int) result * sign);
}
