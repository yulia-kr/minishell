/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_get_max_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 06:33:47 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/06 10:29:02 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 	This function counts the total number of words given by user as 
 * 			maximum number of args. The value obtained is used by the parser.
 * 			This is performed by ignoring all whitespace characters and 
 * 			detecting only the first character of a word within the usr cmd
 * 			input.
 * 			The parser variable pointer (v_p.max_args) is updated with the 
 * 			counted args obtained.
 * 			RETURNS: 0 on success and -1 on fail.
 * 
 * @param v_p 
 * @return int 
 */
int	ft_parser_get_max_args(t_parser_var *v_p)
{
	char	*chr_p;
	int		flag;
	int		cnt_args;

	chr_p = v_p->usr_cmd_inp;
	if (chr_p == NULL)
		return (-1);
	flag = 1;
	cnt_args = 0;
	while (*chr_p != '\0')
	{
		if (ft_strchr(P_WHITESPACE, (int)*chr_p) == NULL && flag == 1)
		{
			cnt_args++;
			flag = 0;
		}
		else if (ft_strchr(P_WHITESPACE, (int)*chr_p))
			flag = 1;
		chr_p++;
	}
	v_p->max_args = cnt_args;
	return (0);
}
