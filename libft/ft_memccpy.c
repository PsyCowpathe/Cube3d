/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:15:26 by agirona           #+#    #+#             */
/*   Updated: 2021/06/17 14:30:32 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i != n)
	{
		((unsigned char *)dst)[i] = ((const char *)src)[i];
		if (((unsigned char *)dst)[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (0);
}
