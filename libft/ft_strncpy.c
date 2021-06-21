/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 04:56:56 by agirona           #+#    #+#             */
/*   Updated: 2021/06/17 15:21:22 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i != n)
	{
		dest[i] = src[i];
		i++;
	}
	i = ft_strlen(src);
	if (i < n)
	{
		while (i < n)
			dest[i++] = '\0';
	}
	return (dest);
}
