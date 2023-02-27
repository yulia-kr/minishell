/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:20:36 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/15 13:03:42 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			idx;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	idx = 0;
	if (d > s)
	{
		while (n != 0)
		{
			n--;
			*(d + n) = *(s + n);
		}
	}
	else if (s > d)
	{
		while (idx < n)
		{
			*(d + idx) = *(s + idx);
			idx++;
		}
	}
	return ((void *)dest);
}
