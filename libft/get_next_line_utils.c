/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 12:15:37 by agirona           #+#    #+#             */
/*   Updated: 2021/06/21 16:27:13 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	len(const char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		c;
	char	*res;

	i = 0;
	c = 0;
	res = NULL;
	if (!s1 && !s2)
		return (NULL);
	res = (char *)malloc(sizeof(char) * len(s1) + len(s2) + 1);
	if (res == NULL)
		free((char *)s2);
	if (res == NULL)
		return (NULL);
	res[0] = '\0';
	while (s1 && s1[c])
		res[i++] = s1[c++];
	c = 0;
	while (s2 && s2[c])
		res[i++] = s2[c++];
	res[i] = '\0';
	if (s1 != NULL)
		free((char *)s1);
	s1 = NULL;
	return (res);
}

char	*ft_strdup_leaks(const char *s1, int leaks)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	str = (char *)malloc(sizeof(char) * len(s1) + 1);
	if (str == NULL)
	{
		if (leaks == 1)
			free((char *)s1);
		return (NULL);
	}
	str[0] = '\0';
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	if (leaks == 1)
	{
		free((char *)s1);
		s1 = NULL;
	}
	return (str);
}

char	*dup_norm(char **line, const char *s1, int leaks)
{
	char	*str;
	int		i;

	i = -1;
	str = (char *)malloc(sizeof(char) * len(s1) + 1);
	if (str == NULL)
	{
		if (leaks == 1)
			free((char *)s1);
		line[0] = NULL;
		return (NULL);
	}
	str[0] = '\0';
	while (s1[++i])
		str[i] = s1[i];
	str[i] = '\0';
	if (leaks == 1)
	{
		free((char *)s1);
		s1 = NULL;
	}
	line[0] = str;
	return (str);
}

int	new_read(int *ret, int fd, char *buff, int buffer_size)
{
	*ret = read(fd, buff, buffer_size);
	return (*ret);
}
