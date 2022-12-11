/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_parse_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:03:19 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/10 17:06:49 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 	This function checks if the token received is for argument or cmd
 * 
 * @param tk 
 */
static void	ft_is_arg_or_cmd(int tk)
{
	if (tk != 'a')
	{
		write(2, "Error!\nsyntax", 13);
		exit(1);
	}
}

/**
 * @brief 	This function checks if the argument counter exceeds the arg limit.
 * 
 * @param argc 
 * @param v 
 */
static void	ft_chk_args_limit(int argc, t_parser_var *v)
{
	if ((argc) > v->max_args)
	{
		write(2, "Error!\nArgs limit exceeded\n", 27);
		ft_printf("MAX_ARGS: %d", v->max_args);
		exit(1);
	}
}

/**
 * @brief 	This function parses the usr command input using the context
 * 			free grammar CFG -> REDIR {aaa REDIR}*
 * 
 * @param str_s 
 * @param str_e 
 * @param v 
 * @return t_cmd* 
 */
t_cmd	*ft_parser_parse_exec(char **str_s, char *str_e, t_parser_var *v)
{
	t_cmd		*ret;
	t_cmd_exec	*cmd;
	int			argc;
	char		*tk_s;
	char		*tk_e;

	ret = ft_parser_init_cmd_exec(v);
	cmd = (t_cmd_exec *)ret;
	argc = 0;
	ret = ft_parser_parse_redir(ret, str_s, str_e, v);
	if (*ret == P_ERROR)
		return (ret);
	while (!ft_parser_peek(str_s, str_e, "|"))
	{
		v->tok = ft_parser_get_token(str_s, str_e, &tk_s, &tk_e);
		if (v->tok == 0)
			break ;
		ft_is_arg_or_cmd(v->tok);
		cmd->argv_s[argc] = tk_s;
		cmd->argv_e[argc] = tk_e;
		argc++;
		ft_chk_args_limit(argc, v);
		ret = ft_parser_parse_redir(ret, str_s, str_e, v);
		if (*ret == P_ERROR)
			return (ret);
	}
	cmd->argv_s[argc] = 0;
	cmd->argv_e[argc] = 0;
	return (ret);
}
