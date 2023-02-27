/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:04:48 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/15 02:53:28 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			idx;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	idx = 0;
	if (d > (s + (n - 1)))
	{
		while (idx < n)
		{
			*(d + idx) = *(s + idx);
			idx++;
		}
	}
	else if (s > (d + (n - 1)))
	{
		while (idx < n)
		{
			*(d + idx) = *(s + idx);
			idx++;
		}
	}
	return ((void *)dest);
}
