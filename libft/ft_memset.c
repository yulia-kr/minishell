/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:18:45 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/15 13:01:56 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			idx;
	unsigned char	*mem_adr;

	idx = 0;
	mem_adr = (unsigned char *)s;
	while (idx < n)
	{
		*(mem_adr + idx) = c;
		idx++;
	}
	return ((void *)s);
}
