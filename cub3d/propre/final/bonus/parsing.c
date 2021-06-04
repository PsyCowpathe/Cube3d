/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:02:00 by agirona           #+#    #+#             */
/*   Updated: 2021/05/26 16:54:56 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*int	read_map(t_mlx *data, char *str)
{
	char	*tmp;
	int		fd;
	int		i;

	i = 0;
	data->mapy = 0;
	data->mapx = 0;
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &tmp) == 1 && ++data->mapy)
	{
		if (data->mapx < (int)ft_strlen(tmp))
			data->mapx = ft_strlen(tmp);
		free(tmp);
	}
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
}*/

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

#include <errno.h>
#include <string.h>

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

int		error(t_mlx *data, int nb, int line)
{
	if (nb == 1)
		ft_putstr("Error empty line at start of file");
	if (nb == 2)
	{
		ft_putstr("Space at start of line : ");
		ft_putnbr(line);
	}
	if (nb == 3)
	{
		ft_putstr("Space at end of line : ");
		ft_putnbr(line);
	}
	if (nb == 4)
		ft_putstr("Empty line at end of file");
	if (nb == 5)
	{
		ft_putstr("Empty line in map at line : ");
		ft_putnbr(line);
	}
	if (nb == 6)
	{
		if (data->no == 0)
			ft_putstr("Missing north texture.\n");
		if (data->so == 0)
			ft_putstr("Missing south texture.\n");
		if (data->ea == 0)
			ft_putstr("Missing east texture.\n");
		if (data->we == 0)
			ft_putstr("Missing west texture.\n");
		if (data->f == 0)
			ft_putstr("Missing floor color.\n");
		if (data->c == 0)
			ft_putstr("Missing ceiling color.\n");
	}
	if (nb == 7)
	{
		ft_putstr("Incorrect information at line : ");
		ft_putnbr(line);
		ft_putstr("\nThe map need to be at bottom of the file.");
	}
	if (nb == 8)
	{
		if (nb == 0)
			ft_putstr("Invalid caractere in floor color.");
		else
			ft_putstr("Invalid caractere in ceiling color.");
	}
	if (nb == 9)
		ft_putstr("Color of floor and ceiling must be between 0 and 255");
	return (0);
}

int		is_map(t_mlx *data, char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == 'N' && str[i + 1] == 'O')
	{
		data->no = 1;
		data->north = ft_strdup(str + i + 2);
		return (0);
	}
	if (str[i] == 'S' && str[i + 1] == 'O')
	{
		data->so = 1;
		data->south = ft_strdup(str + i + 1);
		return (0);
	}
	if (str[i] == 'W' && str[i + 1] == 'E')
	{
		data->we = 1;
		data->west = ft_strdup(str + i + 1);
		return (0);
	}
	if (str[i] == 'E' && str[i + 1] == 'A')
	{
		data->ea = 1;
		data->east = ft_strdup(str + i + 1);
		return (0);
	}
	if (str[i] == 'F')
	{
		data->f = 1;
		data->floor = ft_strdup(str + i + 1);
		return (0);
	}
	if (str[i] == 'C')
	{
		data->c = 1;
		data->ceiling = ft_strdup(str + i + 1);
		return (0);
	}
	return (1);
}

int		hav_path(t_mlx *data)
{
	if (data->no == 1 && data->so == 1 && data->ea == 1
		&& data->we == 1 && data->f == 1 && data->c == 1)
		return (1);
	return (0);	
}

int		verif_form(char **info, t_mlx *data)
{
	int		i;
	int		c;

	i = -1;
	if (info[i + 1][0] == '\0')
		return (error(data, 1, -1));
	while (++i <= data->infoline)
	{
		if (info[i][0] == ' ' && hav_path(data) == 0)
			return (error(data, 2, i + 1));
		if (is_map(data, info[i]) == 1 && info[i][0] != '\0' && hav_path(data) == 0)
			return (error(data, 7, i + 1));
		if (i == data->infoline - 1 && info[i][0] == '\0')
			return (error(data, 4, -1));
				if (info[i][0] == '\0' && hav_path(data) == 1 && i != data->infoline)
			return (error(data, 5, i + 1));
		c = -1;
		while (info[i][++c] != '\0')
		{
			ft_putchar(info[i][c]);
			if (info[i][c + 1] == '\0' && info[i][c] == ' ')
				return (error(data, 3, i + 1));
		}
		ft_putchar('\n');
	}
	if (hav_path(data) == 0)
		return (error(data, 6, -1));
	return (1);
}

int		verif_info(t_mlx *data, char *str, int invalid)
{
	int	i;
	int	c;
	int	rgb;
	char	tmp[4];

	i = 0;
	rgb = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (ft_ischar("0123456789", str[i]) == 0)
			return (error(data, 8, invalid));
		c = 0;
		while (str[i] && ft_ischar("0123456789", str[i]) == 1)
		{
			tmp[c] = str[i];
			i++;
			c++;
		}
		tmp[c] = '\0';
		data->frgb[rgb] = ft_atoi(tmp);
		if (!(data->frgb[rgb] >= 0 && data->frgb[rgb] <= 255))
			return (error(data, 9, -1));
		if (rgb != 2 && !(str[i] == ',' && (str[i + 1] == ' '
		|| ft_ischar("0123456789", str[i + 1]))))
			return (error(data, 8, invalid));
		while (str[i] && ft_ischar("0123456789", str[i]) == 0)
			i++;
		rgb++;
	}
	return (1);
}

int		parsing(t_mlx *data, char *str)
{
	(void)data;
	char	**info;

	data->north = 0;
	data->south = 0;
	data->east = 0;
	data->west = 0;
	data->floor = 0;
	data->ceiling = 0;
	info = get_file_size(data, str);
	if (info == NULL)
		return (0);
	if (verif_form(info, data) == 0)
		return (0);
	if (verif_info(data, data->floor, 0) == 0)
		return (0);
	if (verif_info(data, data->ceiling, 1) == 0)
		return (0);
	return (1);
}
