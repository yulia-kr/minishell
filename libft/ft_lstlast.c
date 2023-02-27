/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:47:18 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/07 16:18:33 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*adr_node;

	adr_node = lst;
	if (adr_node == 0)
		return (0);
	while (adr_node->next != 0)
	{
		adr_node = adr_node->next;
	}
	return (adr_node);
}
