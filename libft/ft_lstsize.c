/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 12:52:42 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/07 15:49:05 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		cnt;
	t_list	*adr_node;

	cnt = 0;
	adr_node = lst;
	while (adr_node != 0)
	{
		adr_node = adr_node->next;
		cnt++;
	}
	return (cnt);
}
