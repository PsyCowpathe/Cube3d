/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:19:28 by agirona           #+#    #+#             */
/*   Updated: 2021/04/29 17:36:31 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		read_map(char *str, t_mlx *data)
{
	char	*tmp;
	int		fd;
	int		i;

	i = 0;
	data->mapy = 0;
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &tmp) == 1 && ++data->mapy)
		free(tmp);
	free(tmp);
	close(fd);
	data->map = malloc(sizeof(char *) * data->mapy + 1);
	if (data->map == NULL)
		return (0);
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &tmp) == 1)
	{
		data->map[i++] = ft_strdup(tmp);
		free(tmp);
	}
	free(tmp);
	close(fd);
	return (1);
}
