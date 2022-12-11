/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_peek.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 10:08:30 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/06 21:37:26 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 	This function perform a sneak peek search on the string, in other
 * 			words, a look ahead search to see if a character found is a member
 * 			of a given token (set of characters).
 * 			This function returns true (1) or false (0).
 * 
 * @param str_s 
 * @param str_e 
 * @param tk 
 * @return int 
 */
int	ft_parser_peek(char **str_s, char *str_e, char *tk)
{
	char	*s;

	s = *str_s;
	while (s < str_e && ft_strchr(P_WHITESPACE, *s))
		s++;
	*str_s = s;
	return (*s && ft_strchr(tk, *s));
}
