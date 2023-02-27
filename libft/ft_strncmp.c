/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:16:06 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/10 15:41:43 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t			idx;
	unsigned char	ch1;
	unsigned char	ch2;

	idx = 0;
	while (idx < size)
	{
		ch1 = (unsigned char)(*(s1 + idx));
		ch2 = (unsigned char)(*(s2 + idx));
		if (ch1 - ch2 != 0)
			return (ch1 - ch2);
		if (ch1 == '\0' || ch2 == '\0')
			break ;
		idx++;
	}
	return (0);
}
