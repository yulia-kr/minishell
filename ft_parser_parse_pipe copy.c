/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_parse_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:07:02 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/18 13:17:12 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   This function parses the usr command input string into recursive
 *		  	execution tree based on the context free grammar CFG below.
 *		  	PIPE -> EXEC [|LINE].
 *			This parse is performed based on the pipe character.
 * 
 * @param str_s 
 * @param str_e 
 * @return t_cmd* 
 */
t_cmd	*ft_parser_parse_pipe(char **str_s, char *str_e, t_parser_var *v)
{
	t_cmd	*cmd;

	cmd = ft_parser_parse_exec(str_s, str_e, v);
	if (*cmd == P_ERROR)
		return (cmd);
	if (ft_parser_peek(str_s, str_e, "|"))
	{
		if ((((t_cmd_exec *)cmd)->argv_s)[0] == 0)
		{
			ft_printf("Error! syntax error\n");
			v->status = STATUS_ERROR_SYNTAX;
			ft_free_parser_tree(cmd);
			cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
			*cmd = P_ERROR;
			return (cmd);
		}
		ft_parser_get_token(str_s, str_e, 0, 0);
		cmd = ft_parser_init_cmd_pipe(cmd, \
									ft_parser_parse_pipe(str_s, str_e, v));
	}
	return (cmd);
}
