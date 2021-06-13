/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 19:15:43 by agirona           #+#    #+#             */
/*   Updated: 2021/06/13 19:10:06 by agirona          ###   ########lyon.fr   */
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
	{
		info[i++] = ft_strdup(tmp);
		free(tmp);
	}
	free(tmp);
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
	free(tmp);
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
			return (error(data, 5 + invalid, -1, 1));
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
		return (error(data, 11, -1, 1));
	if (count < 1)
		return (error(data, 12, -1, 1));
	return (1);
}

int	check_path(t_mlx *data)
{
	int		print;
	int		count;

	print = 2;
	count = 0;
	if (data->north[0] != ' ' && print-- <= 2 && ++count)
		error(data, 16, 0, print);
	if (data->south[0] != ' ' && print-- <= 2 && ++count)
		error(data, 16, 1, print);
	if (data->east[0] != ' ' && print-- <= 2 && ++count)
		error(data, 16, 2, print);
	if (data->west[0] != ' ' && print-- <= 2 && ++count)
		error(data, 16, 3, print);
	if (data->floor[0] != ' ' && print-- <= 2 && ++count)
	 	error(data, 16, 4, print);
	if (data->ceiling[0] != ' ' && print-- <= 2 && ++count)
		error(data, 16, 5, print);
	if (count > 0)
		return (0);
	return (1);
}
