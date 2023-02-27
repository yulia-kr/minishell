/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:06:11 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/11 14:44:52 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static long long unsigned int	ft_pw(int base, int idx)
{	
	long long int	value;

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

static size_t	ft_check_space(const char *s)
{
	size_t	idx;

	idx = 0;
	while (*(s + idx) != '\0')
	{
		if (*(s + idx) != ' ' && !(*(s + idx) >= 9 && *(s + idx) <= 13))
		{
			return (idx);
		}
		idx++;
	}
	return (0);
}

static size_t	ft_check_sn(const char *str, size_t idx, int *sn)
{
	*sn = 0;
	while (*(str + idx) != '\0')
	{
		if (*(str + idx) == '+')
		{
			return (idx + 1);
		}
		else if (*(str + idx) == '-')
		{
			*sn = 1;
			return (idx + 1);
		}
		else
			return (idx);
		idx++;
	}
	return (0);
}

static int	ft_check_digit(const char *str, size_t idx, char *b)
{
	int	idx_digit;
	int	int_idx_size;

	idx_digit = 0;
	int_idx_size = 29;
	while (*(str + idx) != '\0')
	{
		if ((*(str + idx) >= '0') && (*(str + idx) <= '9'))
		{
			if (idx_digit > int_idx_size)
				return (idx_digit - 1);
			b[idx_digit] = *(str + idx) - 0x30;
			idx_digit++;
		}
		else
			return (idx_digit);
		idx++;
	}
	return (idx_digit);
}

int	ft_atoi(const char *str)
{
	size_t					idx;
	int						sn;
	size_t					pwr;
	char					b[30];
	long long unsigned int	out;

	pwr = 0;
	out = 0;
	idx = ft_check_space(str);
	idx = ft_check_sn(str, idx, &sn);
	idx = ft_check_digit(str, idx, b);
	while (idx > 0)
	{
		if (sn == 0 && ((out + (b[idx - 1] * ft_pw(10, pwr))) < out))
			return (-1);
		if (sn && (out + (b[idx - 1] * ft_pw(10, pwr))) > 9223372036854775807LL)
			return (0);
		out += (b[idx - 1] * ft_pw(10, pwr));
		pwr++;
		idx--;
	}
	if (sn)
		out *= -1;
	return ((int)out);
}
