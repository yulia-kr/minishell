/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:12:00 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/17 15:42:49 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_lstrlen(char const *s)
{
	size_t	idx;

	idx = 0;
	while (*(s + idx) != '\0')
	{
		idx++;
	}
	return (idx);
}

static char	*ft_make_copy(char const *s, size_t start, size_t end, size_t idx)
{
	char	*str_trim;

	if (start > end)
	{
		str_trim = (char *)malloc(1);
		if (str_trim != 0)
			*str_trim = '\0';
		return (str_trim);
	}
	else
	{
		str_trim = (char *)malloc(end - start + 2);
		if (str_trim != 0)
		{
			while (start < (end + 1))
			{
				*(str_trim + idx) = *(s + start);
				start++;
				idx++;
			}
			*(str_trim + idx) = '\0';
			return (str_trim);
		}
	}
	return (0);
}

static size_t	ft_upd_idx_start(char const *s, char const *set, size_t start)
{
	int	idx;

	idx = 0;
	while (*(s + start) != '\0')
	{
		while (*(set + idx) != '\0')
		{
			if (*(s + start) == *(set + idx))
				break ;
			idx++;
		}
		if (*(set + idx) == '\0')
			return (start);
		start++;
		idx = 0;
	}
	return (start);
}

static size_t	ft_upd_idx_end(char const *s, char const *set, size_t end)
{
	int	idx;

	idx = 0;
	while (end > 0)
	{
		while (*(set + idx) != '\0')
		{
			if (*(s + end) == *(set + idx))
				break ;
			idx++;
		}
		if (*(set + idx) == '\0')
			return (end);
		end--;
		idx = 0;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	idx_start;
	size_t	idx_end;
	char	*str_trim;
	size_t	idx;

	if (s1 != 0)
	{
		idx = 0;
		idx_end = ft_lstrlen(s1) - 1;
		idx_start = 0;
		idx_start = ft_upd_idx_start(s1, set, idx_start);
		idx_end = ft_upd_idx_end(s1, set, idx_end);
		str_trim = ft_make_copy(s1, idx_start, idx_end, idx);
		return (str_trim);
	}
	return (0);
}
