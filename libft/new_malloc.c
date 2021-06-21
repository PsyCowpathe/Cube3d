/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 15:05:49 by agirona           #+#    #+#             */
/*   Updated: 2021/06/17 15:06:36 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	new_malloc(void **dst, int type, int len)
{
	*dst = malloc(type * len);
	if (*dst == NULL)
		return (0);
	return (1);
}
