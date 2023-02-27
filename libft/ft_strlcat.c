/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:26:39 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/08 13:37:55 by cudoh            ###   ########.fr       */
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

static size_t	ft_dest_null_len_check(const char *s, size_t size)
{
	size_t	idx;

	idx = 0;
	while (*(s + idx) != '\0')
	{
		if (idx == size)
			return (size);
		idx++;
	}
	return (idx);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	idx;
	size_t	dst_len;

	idx = 0;
	dst_len = ft_dest_null_len_check(dst, size);
	if (size <= dst_len)
		return (size + ft_lstrlen(src));
	while (idx < (size - dst_len - 1))
	{
		if (*(src + idx) == '\0')
		{
			(*(dst + dst_len + idx)) = (*(src + idx));
			return (ft_lstrlen(dst));
		}
		(*(dst + dst_len + idx)) = (*(src + idx));
		idx++;
	}
	(*(dst + dst_len + idx)) = '\0';
	return (dst_len + ft_lstrlen(src));
}
