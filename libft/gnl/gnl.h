/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 23:26:05 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/20 19:07:51 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		ft_strchr_gnl(const char *s, char c);
char	*ft_gnl_strdup(const char *src);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
int		get_len_line(char *s);

char	*get_next_line(int fd);

#endif
