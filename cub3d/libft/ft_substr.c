/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:42:35 by agirona           #+#    #+#             */
/*   Updated: 2020/12/04 00:47:06 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*res;

	i = 0;
	if (!s)
		return (NULL);
	if (start == 0 && len > ft_strlen(s))
		return (ft_strdup(s));
	if (start > ft_strlen(s))
	{
		if ((res = malloc(sizeof(char) * 1)) == NULL)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	if ((res = malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
