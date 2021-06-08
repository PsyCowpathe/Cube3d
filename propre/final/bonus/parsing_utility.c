/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 19:15:43 by agirona           #+#    #+#             */
/*   Updated: 2021/06/08 15:34:37 by agirona          ###   ########lyon.fr   */
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
	while (get_next_line(fd, &tmp) == 1)
	{
		free(tmp);
		data->infoline++;
	}
	close(fd);
	return (get_file(str, data->infoline));
}

int	check_color(t_mlx *data, int *rgb, int invalid)
{
	int		nb;

	nb = 0;
	while (nb < 3)
	{
		if (rgb[nb] < 0 || rgb[nb] > 255)
			return (error(data, 5 + invalid, -1));
		nb++;
	}
	return (1);
}

int	verif_player(t_mlx *data)
{
	int		i;
	int		c;
	int		count;

	i = 0;
	count = 0;
	while (i < data->mapy)
	{
		c = 0;
		while (c < data->mapx)
		{
			if (ft_ischar("NEWS", data->map[i][c]) == 1)
				count++;
			c++;
		}
		i++;
	}
	if (count > 1)
		return (error(data, 11, -1));
	if (count < 1)
		return (error(data, 12, -1));
	return (1);
}

int	check_path(t_mlx *data)
{
	if (data->north[0] != ' ')
		return (error(data, 14, 0));
	if (data->south[0] != ' ')
		return (error(data, 14, 1));
	if (data->east[0] != ' ')
		return (error(data, 14, 2));
	if (data->west[0] != ' ')
		return (error(data, 14, 3));
	if (data->floor[0] != ' ')
		return (error(data, 14, 4));
	if (data->ceiling[0] != ' ')
		return (error(data, 14, 5));
	return (1);
}
