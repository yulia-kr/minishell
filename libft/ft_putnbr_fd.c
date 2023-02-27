/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:14:21 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/07 10:30:48 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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

static void	ft_print_nbr(int fd, int cnt, int n)
{
	int		divisor;
	char	ch_digit;

	cnt--;
	while (cnt >= 0)
	{
		divisor = (n / ft_lpow(10, (cnt)));
		if (divisor < 0)
			divisor *= -1;
		ch_digit = divisor + 0x30;
		write(fd, &ch_digit, 1);
		n = n % ft_lpow(10, cnt);
		cnt--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		cnt;
	int		flag_sign;

	cnt = 0;
	flag_sign = 0;
	if (n < 0)
		flag_sign = 1;
	cnt = ft_count_digits(n);
	if (flag_sign)
		write(fd, "-", 1);
	ft_print_nbr(fd, cnt, n);
}
