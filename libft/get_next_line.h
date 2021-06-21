/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 12:45:28 by agirona           #+#    #+#             */
/*   Updated: 2021/06/21 16:41:12 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define BUFFER_SIZE 32

int		get_next_line(int fd, char **line);
int		len(const char *str);
char	*clear(char *str);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*ft_strdup_leaks(const char *s1, int leaks);
char	*dup_norm(char **line, const char *s1, int leaks);
int		new_read(int *ret, int fd, char *buff, int buffer_size);

#endif
