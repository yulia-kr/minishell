/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:15:24 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/14 14:17:56 by cudoh            ###   ########.fr       */
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

static int	ft_lsearch_little(const char *big, const char *little)
{
	int		no_match_status;
	int		flag;
	size_t	idx;

	idx = 0;
	flag = 1;
	no_match_status = 0;
	while (*(little + idx) != '\0')
	{
		no_match_status = (*(big + idx)) - (*(little + idx));
		if (no_match_status != 0)
		{
			flag = 0;
			break ;
		}
		idx++;
	}
	return (flag);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int			flag;
	const char	*big_srch_lim_adr1;
	const char	*big_srch_lim_adr2;

	big_srch_lim_adr1 = big + ft_lstrlen(big) - ft_lstrlen(little);
	if (len > ft_lstrlen(big))
		big_srch_lim_adr2 = big_srch_lim_adr1;
	else
		big_srch_lim_adr2 = big + len - ft_lstrlen(little);
	if (*little == '\0')
	{
		return ((char *)big);
	}
	while ((big <= big_srch_lim_adr1) && (big <= big_srch_lim_adr2))
	{
		flag = ft_lsearch_little(big, little);
		if (flag)
			return ((char *)big);
		big++;
	}
	return (0);
}
