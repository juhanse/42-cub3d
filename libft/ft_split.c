/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:31:31 by julienhanse       #+#    #+#             */
/*   Updated: 2025/04/16 21:52:15 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_total(char const *s, char c)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c))
			i++;
		if (s[i])
			count++;
		while (s[i] && !(s[i] == c))
			i++;
	}
	return (count);
}

static int	ft_separator_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && !(s[i] == c))
		i++;
	return (i);
}

static char	*ft_word(char const *s, char c)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = ft_separator_len(s, c);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (NULL);
	while (i < len_word)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	*ft_free(char **strings, int i)
{
	while (i-- > 0)
		free(strings[i]);
	free(strings);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**buffer;

	if (!s)
		return (NULL);
	i = 0;
	buffer = (char **)malloc(sizeof(char *) * (ft_count_total(s, c) + 1));
	if (!buffer)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			buffer[i] = ft_word(s, c);
			if (buffer[i++] == NULL)
				return (ft_free(buffer, i));
			s += ft_separator_len(s, c);
		}
		if (*s)
			s++;
	}
	buffer[i] = NULL;
	return (buffer);
}
