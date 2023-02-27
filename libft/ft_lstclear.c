/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:07:10 by cudoh             #+#    #+#             */
/*   Updated: 2022/11/19 07:37:33 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*curr;
	t_list	*prev;

	if (*lst != NULL)
	{
		curr = *lst;
		while (curr != 0)
		{
			prev = curr;
			curr = curr->next;
			del((void *)(prev->content));
			free(prev);
			prev = NULL;
		}
	}
	*lst = NULL;
}
