/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:21:09 by cudoh             #+#    #+#             */
/*   Updated: 2022/06/18 04:42:30 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*adr_start;

	if (*lst == 0 && new == 0)
		return ;
	adr_start = *lst;
	if (adr_start == 0)
	{
		*lst = new;
		return ;
	}	
	while (adr_start-> next != 0)
	{
		adr_start = adr_start->next;
	}
	adr_start->next = new;
	new->next = NULL;
}
