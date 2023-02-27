/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:10:24 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/14 08:21:42 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int		idx;
	char	*chr;

	idx = 0;
	chr = 0;
	if (c > 255)
		c = c & 0xFF;
	while (*(s + idx) != '\0')
	{
		if (*(s + idx) == (unsigned char)c)
		{
			chr = (char *)(s + idx);
			return (chr);
		}
		idx++;
	}
	if (c == '\0')
	{
		chr = (char *)(s + idx);
	}
	return (chr);
}
