/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:24:03 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/14 08:25:51 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		idx;
	char	*ptr_chr;

	idx = 0;
	ptr_chr = 0;
	if (c > 255)
		c = c & 0xFF;
	while (*(s + idx) != '\0')
	{
		if (*(s + idx) == c)
		{
			ptr_chr = (char *)(s + idx);
		}
		idx++;
	}
	if (c == '\0')
	{
		ptr_chr = (char *)(s + idx);
	}
	return (ptr_chr);
}
