/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 07:34:44 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/15 02:57:01 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			idx;
	unsigned char	*src;
	unsigned char	*chr;

	idx = 0;
	chr = 0;
	src = (unsigned char *)s;
	while (idx < n)
	{
		if ((*(src + idx)) == (unsigned char)c)
		{
			chr = (src + idx);
			return ((void *)chr);
		}
		idx++;
	}
	return (0);
}
