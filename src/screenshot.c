/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:09:37 by agirona           #+#    #+#             */
/*   Updated: 2021/06/10 20:49:31 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	size_set(char *ptr, int nb)
{
	ptr[0] = nb;
	ptr[1] = nb >> 8;
	ptr[2] = nb >> 16;
	ptr[3] = nb >> 24;
}

int	bmp_header(t_mlx *data, char **header)
{
	int		len;

	len = 54 + (WIN_X * WIN_Y) * 4;
	header[0] = malloc(sizeof(char) * len);
	if (header[0] == NULL)
		return (0);
	ft_bzero(header[0], len);
	header[0][0] = 'B';
	header[0][1] = 'M';
	size_set(&header[0][2], len);
	header[0][10] = 54;
	header[0][14] = 40;
	size_set(&header[0][18], WIN_X);
	size_set(&header[0][22], WIN_Y);
	header[0][26] = 1;
	header[0][28] = 32;
	data->fd = open("coucou.bmp", O_RDWR | O_CREAT | O_TRUNC, 00700);
	write(data->fd, header[0], 54);
	return (1);
}

void	take_screenshot(t_mlx *data)
{
	int		y;
	int		x;
	char	tmp[4];

	y = WIN_Y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < WIN_X)
		{
			size_set(tmp, data->addr[y * WIN_X + x]);
			write(data->fd, tmp, 4);
			x++;
		}
		y--;
	}
	close(data->fd);
}
