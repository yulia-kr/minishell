/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:47:51 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/15 13:04:46 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*curr;
	t_list	*new_node;
	t_list	*prev;

	if (lst != 0)
	{
		new_lst = (void *)0;
		curr = lst;
		while (curr != NULL)
		{
			new_node = ft_lstnew(f(curr->content));
			if (new_lst == NULL)
				new_lst = new_node;
			else
				ft_lstadd_back(&new_lst, new_node);
			prev = curr;
			curr = curr->next;
			if (prev == NULL)
				del(prev);
		}
		lst = NULL;
		return (new_lst);
	}
	return (0);
}
