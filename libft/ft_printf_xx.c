/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 01:03:03 by cudoh             #+#    #+#             */
/*   Updated: 2022/06/02 01:03:03 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_xx(char x_chr, unsigned int x)
{
	int	len;

	len = 0;
	if (x_chr == 'X')
	{
		len += ft_printf_nbr_base(x, 16, 1);
	}
	else if (x_chr == 'x')
	{
		len += ft_printf_nbr_base(x, 16, 0);
	}
	return (len);
}
