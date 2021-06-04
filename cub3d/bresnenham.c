/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresnenham.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 15:10:23 by agirona           #+#    #+#             */
/*   Updated: 2021/04/14 19:23:10 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bresenham2(int *tab, int *size, t_mlx *data)
{
	int		i;

	i = 1;
	size[4] = size[1] / 2;
	while (i++ <= size[1])
	{
		tab[1] += size[3];
		size[4] += size[0];
		if (size[4] >= size[1])
		{
			size[4] -= size[1];
			tab[0] += size[2];
		}
		set_pixel(data ,tab[0], tab[1], WHITE);
	}
}

void	bresenham(int *tab, int *size, t_mlx *data)
{
	int		i;

	i = 1;
	set_pixel(data ,tab[0], tab[1], WHITE);
	if (size[0] > size[1])
	{
		size[4] = size[0] / 2;
		while (i++ <= size[0])
		{
			tab[0] += size[2];
			size[4] += size[1];
			if (size[4] >= size[0])
			{
				size[4] -= size[0];
				tab[1] += size[3];
			}
			set_pixel(data ,tab[0], tab[1], WHITE);
		}
	}
	else
		bresenham2(tab, size, data);
}

void	draw_utility(int *tab, t_mlx *data)
{
	int		*size;

	size = malloc(sizeof(int) * 5);
	size[0] = tab[2] - tab[0];
	size[1] = tab[3] - tab[1];
	size[2] = (size[0] > 0) ? 1 : -1;
	size[3] = (size[1] > 0) ? 1 : -1;
	size[0] = abs(size[0]);
	size[1] = abs(size[1]);
	bresenham(tab, size, data);
	free(size);
}
