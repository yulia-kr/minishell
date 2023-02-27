/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 13:02:18 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/17 15:31:38 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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

static size_t	ft_lmemcpy(char *buff, char const *s, size_t idx)
{
	size_t	idx_part;

	idx_part = 0;
	while (*(s + idx_part) != '\0')
	{
		*(buff + idx) = *(s + idx_part);
		idx++;
		idx_part++;
	}
	return (idx);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	len_new_str;
	size_t	idx;

	if (s1 != 0 && s2 != 0)
	{
		len_new_str = ft_lstrlen(s1) + ft_lstrlen(s2) + 1;
		idx = 0;
		new_str = (char *)malloc(len_new_str);
		if (new_str != 0)
		{
			idx = ft_lmemcpy(new_str, s1, idx);
			idx = ft_lmemcpy(new_str, s2, idx);
			*(new_str + idx) = '\0';
			return (new_str);
		}
	}
	return (0);
}
