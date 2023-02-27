/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_parse_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:57:56 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/10 14:06:42 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   This function parses the usr command input string into recursive
 *		  	execution tree based on the context free grammar CFG below.
 *		  	LINE -> PIPE {&&}[LINE]
 * 
 * @param str_s 
 * @param str_e 
 * @return t_cmd* 
 */
t_cmd	*ft_parser_parse_line(char **str_s, char *str_e, t_parser_var *v)
{
	t_cmd	*cmd;

	cmd = ft_parser_parse_pipe(str_s, str_e, v);
	if (*cmd == P_ERROR)
		return (cmd);
	while (ft_parser_peek(str_s, str_e, "&") && \
			ft_parser_peek(str_s, str_e, "&"))
	{
		ft_parser_get_token(str_s, str_e, 0, 0);
		cmd = ft_parser_init_cmd_list(cmd, \
				ft_parser_parse_line(str_s, str_e, v));
	}
	return (cmd);
}
