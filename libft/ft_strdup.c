/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 05:35:22 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/02 19:05:14 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

char	*ft_strdup(const char *s)
{
	size_t	len_str;
	char	*str_dup;
	size_t	idx;

	idx = 0;
	len_str = ft_lstrlen(s);
	str_dup = (char *)malloc(len_str + 1);
	if (str_dup != 0)
	{
		while (*(s + idx) != '\0')
		{
			*(str_dup + idx) = *(s + idx);
			idx++;
		}
		*(str_dup + idx) = '\0';
		return (str_dup);
	}
	return (0);
}
