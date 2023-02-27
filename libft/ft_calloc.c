/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 06:04:06 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/17 15:20:21 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	idx;

	if (nmemb >= 65535 || size >= 65535)
		return (0);
	idx = 0;
	ptr = (char *)malloc(nmemb * size);
	if (ptr != NULL)
	{
		while (idx < (nmemb * size))
		{	
			*(char *)(ptr + idx) = 0;
			idx++;
		}
		return ((void *)ptr);
	}
	return (0);
}
