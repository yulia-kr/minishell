/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:21:01 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/02 17:59:21 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static size_t	ft_lstrlen(const char *s)
{
	size_t	idx;

	idx = 0;
	while (*(s + idx) != '\0')
	{
		idx++;
	}
	return (idx);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	idx;
	size_t	src_len;

	idx = 0;
	src_len = ft_lstrlen(src);
	if (size == 0)
		return (src_len);
	while (*(src + idx) != '\0' && (idx < (size - 1)))
	{
		(*(dst + idx)) = (*(src + idx));
		idx++;
	}
	(*(dst + idx)) = '\0';
	return (src_len);
}
