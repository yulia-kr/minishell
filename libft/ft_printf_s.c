/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 09:06:12 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/29 09:06:12 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_printf_s(char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL || s == 0)
		len += write(1, "(null)", 6);
	else
		len += write(1, s, ft_strlen(s));
	return (len);
}
