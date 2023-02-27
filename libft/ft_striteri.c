/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 08:18:20 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/10 13:43:11 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	idx;

	if (s != 0)
	{
		idx = 0;
		while (*(s + idx) != '\0')
		{
			f(idx, (s + idx));
			idx++;
		}
	}
}
