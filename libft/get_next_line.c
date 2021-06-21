/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 12:43:53 by agirona           #+#    #+#             */
/*   Updated: 2021/06/21 16:40:55 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	newline(char **str, char **save, int *ret)
{
	int		i;

	i = 0;
	*ret = -1;
	while (*str && str[0][i])
	{
		if (str[0][i] == '\n')
		{
			str[0][i] = '\0';
			i++;
			*save = ft_strdup_leaks(str[0] + i, 0);
			if (*save == NULL)
				return (-1);
			str[0] = ft_strdup_leaks(str[0], 1);
			if (str[0] == NULL)
				return (-1);
			*ret = 1;
			return (1);
		}
		i++;
	}
	*ret = 0;
	return (0);
}

int	freevar(char **var1, char **var2, int ret)
{
	if (var1 != NULL && *var1 != NULL)
	{
		free(*var1);
		*var1 = NULL;
	}
	if (var2 != NULL && *var2 != NULL)
	{
		free(*var2);
		*var2 = NULL;
	}
	return (ret);
}

int	do_shit(int *ret, char **line, int fd)
{
	*ret = -1;
	*line = NULL;
	if (fd < 0 || fd > 30)
		return (-1);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int				ret;
	char			*buff;
	static char		*save[30] = {NULL};

	if (do_shit(&ret, line, fd) == -1)
		return (-1);
	if (new_malloc((void *)&buff, sizeof(char), BUFFER_SIZE + 1) == 0)
		return (freevar(&save[fd], NULL, -1));
	if (save[fd] && dup_norm(&line[0], save[fd], 0) == NULL)
		return (freevar(&buff, &save[fd], -1));
	else if (save[fd])
		freevar(&save[fd], NULL, 0);
	while (ret != 0 && newline(line, &save[fd], &ret) == 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0)
			return (freevar(&buff, &save[fd], -1));
		buff[ret] = '\0';
		line [0] = gnl_strjoin(line[0], buff);
		if (line[0] == NULL)
			return (-1);
	}
	if (save[fd] && ret != -1)
		return (freevar(&buff, NULL, 1));
	return (freevar(&save[fd], &buff, ret));
}
