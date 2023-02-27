/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 10:39:51 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/29 10:39:51 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_nbr_base(long long unsigned int n, size_t base, int c)
{
	char	*ptr;
	int		len;
	char	nbr_ch;

	len = 0;
	ptr = "0123456789abcdef";
	if (n >= base)
		len += ft_printf_nbr_base(n / base, base, c);
	nbr_ch = ptr[n % base];
	if (c == 0 && (nbr_ch >= 97 && nbr_ch <= 102))
		len += write(1, &nbr_ch, sizeof(char));
	else if (c && (nbr_ch >= 97 && nbr_ch <= 102))
	{
		nbr_ch -= 32;
		len += write(1, &nbr_ch, sizeof(char));
	}
	else
		len += write(1, &nbr_ch, sizeof(char));
	return (len);
}
