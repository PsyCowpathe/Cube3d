/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:42:35 by agirona           #+#    #+#             */
/*   Updated: 2021/06/21 16:30:12 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*res;

	i = 0;
	res = NULL;
	if (!s)
		return (NULL);
	if (start == 0 && len > ft_strlen(s))
		return (ft_strdup(s));
	if (start > ft_strlen(s))
	{
		if (new_malloc((void *)&res, sizeof(char), 1) == 0)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	if (new_malloc((void *)res, sizeof(char), len + 1) == 0)
		return (NULL);
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
