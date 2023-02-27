/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 11:40:50 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/07 15:48:33 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = 0;
	node = (t_list *)malloc(sizeof(t_list) * 1);
	if (node != NULL)
	{
		if (!content)
			node->content = NULL;
		else
			node->content = content;
		node->next = NULL;
	}
	else
	{
		node = 0;
	}
	return (node);
}
