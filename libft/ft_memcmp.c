/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:41:29 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/17 15:00:35 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			idx;
	unsigned char	*arg1;
	unsigned char	*arg2;
	int				diff;

	idx = 0;
	arg1 = (unsigned char *)s1;
	arg2 = (unsigned char *)s2;
	while (idx < n)
	{
		diff = *(arg1 + idx) - *(arg2 + idx);
		if (diff != 0)
		{
			return (diff);
		}
		idx++;
	}
	return (0);
}
