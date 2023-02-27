/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:08:20 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/14 07:57:43 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_lpow(int base, int idx)
{	
	int	value;

	value = 1;
	if (base == 0)
		return (0);
	if (idx == 0)
		return (1);
	while (idx >= 1)
	{
		value *= base;
		idx--;
	}
	return (value);
}

static int	ft_count_digits(int nbr)
{
	int	cnt;

	cnt = 0;
	if (nbr == 0)
	{
		cnt = 1;
		return (cnt);
	}
	while (nbr)
	{
		nbr = nbr / 10;
		cnt++;
	}
	return (cnt);
}

static void	ft_fill_buffer(char *buf, int cnt, int idx, int n)
{
	int	divisor;

	cnt--;
	while (cnt >= 0)
	{
		divisor = (n / ft_lpow(10, (cnt)));
		if (divisor < 0)
			divisor *= -1;
		buf[idx] = divisor + 0x30;
		n = n % ft_lpow(10, cnt);
		cnt--;
		idx++;
	}
	buf[idx] = '\0';
}

char	*ft_itoa(int n)
{
	char	*nb_buf;
	int		cnt;
	int		idx;
	int		flag_sign;

	cnt = 0;
	idx = 0;
	flag_sign = 0;
	if (n < 0)
		flag_sign = 1;
	cnt = ft_count_digits(n);
	nb_buf = (char *)malloc(cnt + 1 + flag_sign);
	if (nb_buf != 0)
	{
		if (flag_sign)
		{
			*nb_buf = '-';
			idx = 1;
		}
		ft_fill_buffer(nb_buf, cnt, idx, n);
		return (nb_buf);
	}
	return (0);
}
