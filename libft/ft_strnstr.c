/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:35:16 by agirona           #+#    #+#             */
/*   Updated: 2021/06/21 18:42:54 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	d;

	i = 0;
	d = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[d])
		{
			while (haystack[i] == needle[d] && i < len)
			{
				if (needle[d + 1] == '\0')
					return ((char *)haystack + (i - d));
				i++;
				d++;
			}
			i = i - d;
			d = 0;
		}
		i++;
	}
	return (0);
}
