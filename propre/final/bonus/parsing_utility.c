/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 19:15:43 by agirona           #+#    #+#             */
/*   Updated: 2021/06/05 20:58:35 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**get_file(char *str, int line)
{
	int		fd;
	int		i;
	char	**info;
	char	*tmp;

	fd = open(str, O_RDONLY);
	i = 0;
	info = malloc(sizeof(char *) * (line + 1));
	if (info == NULL)
		return (NULL);
	while (get_next_line(fd, &tmp) == 1)
		info[i++] = ft_strdup(tmp);
	info[i] = ft_strdup("\0");
	return (info);
}

char	**get_file_size(t_mlx *data, char *str)
{
	int		fd;
	char	*tmp;

	fd = open(str, O_RDONLY);
	data->infoline = 0;
	while (get_next_line(fd, &tmp) == 1)
	{
		free(tmp);
		data->infoline++;
	}
	close(fd);
	return (get_file(str, data->infoline));
}

int		hav_path(t_mlx *data)
{
	if (data->no > 0 && data->so > 0 && data->ea > 0
		&& data->we > 0 && data->f > 0 && data->c > 0)
		return (1);
	return (0);	
}

