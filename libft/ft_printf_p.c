/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 09:10:40 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/29 09:10:40 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_p(void *p)
{
	int	len;

	len = 0;
	if (p == 0 || p == NULL)
	{
		len += write(1, "(nil)", 5);
		return (len);
	}
	len += write(1, "0x", 2);
	len += ft_printf_nbr_base((long long unsigned int)p, 16, 0);
	return (len);
}
