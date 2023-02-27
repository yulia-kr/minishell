/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 10:45:16 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/29 10:45:16 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
//--- FUNCTION DECLARATION ---
int		ft_printf(const char *s, ...);
int		ft_printf_c(char c);
size_t	ft_printf_s(char *s);
int		ft_printf_p(void *p);
int		ft_printf_d(int d);
int		ft_printf_u(unsigned int d);
int		ft_printf_xx(char x_chr, unsigned int x);
//--- HELPER FUNCTION ---
size_t	ft_strlen(const char *s);
int		ft_printf_nbr_base(long long unsigned n, size_t base, int c);
#endif //FT_PRINTF_H
