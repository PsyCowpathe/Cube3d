/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 12:52:54 by agirona           #+#    #+#             */
/*   Updated: 2021/04/12 16:08:56 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_map(char *str, t_mlx *data)
{
	char	*tmp;
	int		fd;
	int		i;

	i = 0;
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
