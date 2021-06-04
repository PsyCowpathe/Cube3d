/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:21:02 by agirona           #+#    #+#             */
/*   Updated: 2021/04/29 12:58:28 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../mlx/mlx.h"
# define WIN_X 1920
# define WIN_Y 1080

void	size_set(char *ptr, int nb)
{
	ptr[0] = nb;	
	ptr[1] = nb >> 8;
	ptr[2] = nb >> 16;
	ptr[3] = nb >> 24;
}

void	ft_bzero(void *s, size_t n)
{
	size_t i;

	i = 0;
	while (i != n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

int		main(void)
{
	int				fd;
	char 			*header;
	int				len;
	char			tmp[4];
	void			*mlx;
	void			*win;
	void			*img;
	int				*addr;
	int				bits;
	int				endian;
	int				linelen;
	int				y;
	int				x;

	y = 0;
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIN_X, WIN_Y, "test");
	img = mlx_new_image(mlx, WIN_X, WIN_Y);
	addr = (int *)mlx_get_data_addr(img, &bits, &linelen, &endian);
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			if (x % 2 == 0)
				addr[y * WIN_X + x] = 0xFF0000;
			else
				addr[y * WIN_X + x] = 0x00FF00;
			x++;
		}
		y++;
	}
	len = 54 + (WIN_X * WIN_Y) * 4;
	header = malloc(sizeof(char) * len);
	ft_bzero(header, len);
	header[0] = 'B';
	header[1] = 'M';
	size_set(&header[2], len);
	header[10] = 54;
	header[14] = 40;
	size_set(&header[18], WIN_X); 
	size_set(&header[22], WIN_Y); 
	header[26] = 1;
	header[28] = 32;
	fd = open("coucou.bmp", O_RDWR | O_CREAT | O_TRUNC, 00700);
	write(fd, header, 54);
	y = WIN_Y;
	while (y >= 0)
	{
		x = 0;
		while (x < WIN_X)
		{
			size_set(tmp, addr[y * WIN_X + x]);
			write(fd, tmp, 4);
			x++;
		}
		y--;
	}
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(mlx);
	close(fd);
}
