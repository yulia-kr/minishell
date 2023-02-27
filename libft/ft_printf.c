/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:20:27 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/28 12:20:27 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_specifier(const char **s, va_list list)
{
	int	len;

	len = 0;
	if (*(*s + 1) == 'c')
		len += ft_printf_c((char)va_arg(list, int));
	else if (*(*s + 1) == 's')
		len += ft_printf_s(va_arg(list, char *));
	else if (*(*s + 1) == 'p')
		len += ft_printf_p(va_arg(list, void *));
	else if (*(*s + 1) == 'd' || (*(*s + 1) == 'i'))
		len += ft_printf_d(va_arg(list, int));
	else if (*(*s + 1) == 'u')
		len += ft_printf_u(va_arg(list, unsigned int));
	else if (*(*s + 1) == 'x' || (*(*s + 1) == 'X'))
		len += ft_printf_xx(*(*s + 1), va_arg(list, unsigned int));
	else if (*(*s + 1) == '%')
		len += ft_printf_c((int) '%');
	return (len);
}

int	ft_printf(const char *s, ...)
{
	int		len;
	va_list	list;

	len = 0;
	if (s == NULL || s == 0)
		return (0);
	va_start(list, s);
	while (*s != '\0')
	{
		if (*s == '%')
		{
			len += ft_print_specifier(&s, list);
			s++;
		}
		else
		{
			write(1, s, 1);
			len++;
		}
		s++;
	}
	va_end(list);
	return (len);
}
