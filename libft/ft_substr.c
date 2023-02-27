/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 05:07:08 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/17 15:30:14 by cudoh            ###   ########.fr       */
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

static char	*ft_lstart_ge_strlen(void)
{
	char	*substr;

	substr = (char *)malloc(sizeof(char));
	if (substr != 0)
	{
		*substr = '\0';
		return (substr);
	}
	return (0);
}

char	*ft_lalloc_mem(size_t len_str, unsigned int *start, size_t *len)
{
	char	*substr;

	substr = (void *)0;
	if (*len >= (len_str - *start))
	{
		*len = len_str - *start;
		substr = (char *)malloc((sizeof(char) * (*len + 1)));
	}
	else if (*len < (len_str - *start))
		substr = (char *)malloc((sizeof(char) * (*len + 1)));
	if (substr != NULL)
		return (substr);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	idx;

	if (s != 0)
	{
		idx = 0;
		if (start >= ft_lstrlen(s))
			return (ft_lstart_ge_strlen());
		else
		{
			substr = ft_lalloc_mem(ft_lstrlen(s), &start, &len);
			if (substr != 0)
			{
				while ((*(s + start) != '\0') && (idx < len))
				{
					*(substr + idx) = *(s + start);
					start++;
					idx++;
				}
				*(substr + idx) = '\0';
				return (substr);
			}
		}
	}
	return (0);
}
