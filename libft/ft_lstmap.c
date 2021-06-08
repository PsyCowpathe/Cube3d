/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:01:25 by agirona           #+#    #+#             */
/*   Updated: 2020/12/01 17:53:57 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*new;
	t_list	*plist;

	list = NULL;
	plist = lst;
	while (lst)
	{
		if (!(new = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&plist, (*del));
			return (0);
		}
		ft_lstadd_back(&list, new);
		lst = lst->next;
	}
	return (list);
}
