/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 07:05:07 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/13 16:03:03 by cudoh            ###   ########.fr       */
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

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len_str;
	size_t	idx;
	char	*ns;

	if (s != 0)
	{
		len_str = ft_lstrlen(s);
		idx = 0;
		ns = (char *)malloc(len_str + 1);
		if (ns != 0)
		{
			while (*(s + idx) != '\0')
			{
				*(ns + idx) = f(idx, *(s + idx));
				idx++;
			}
			*(ns + idx) = '\0';
			return (ns);
		}
	}
	return (0);
}
