/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_parse_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:03:19 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/11 10:11:24 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 	This function checks if the token received is for argument or cmd
 * 
 * @param tk 
 */
static int	ft_is_arg_or_cmd(int tk, t_parser_var *v)
{
	if (tk != 'a')
	{
		ft_printf("Error! syntax error\n");
		v->status = STATUS_ERROR_SYNTAX;
		return (-1);
	}
	return (0);
}

/**
 * @brief 	This function checks if the argument counter exceeds the arg limit.
 * 
 * @param argc 
 * @param v 
 */
static int	ft_chk_args_limit(int argc, t_parser_var *v)
{
	if ((argc) > v->max_args)
	{
		ft_printf("Error!\nArgs limit exceeded\n");
		v->status = STATUS_ERROR_SYNTAX;
		return (-1);
	}
	return (0);
}

static int	ft_upd_exec_cmd_argv(t_cmd *ret, t_cmd_exec *cmd, \
								t_parser_var *v, int *argc)
{
	int	status;

	status = 0;
	status = ft_is_arg_or_cmd(v->tok, v);
	if (status == 0)
	{
		cmd->argv_s[*argc] = v->tk_s;
		cmd->argv_e[*argc] = v->tk_e;
		(*argc)++;
		status = ft_chk_args_limit(*argc, v);
	}
	if (status < 0)
	{
		ft_free_parser_tree(ret);
		ret = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		*ret = P_ERROR;
		return (-1);
	}
	return (0);
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

	ret = ft_parser_init_cmd_exec(v);
	cmd = (t_cmd_exec *)ret;
	argc = 0;
	ret = ft_parser_parse_redir(ret, str_s, str_e, v);
	if (*ret == P_ERROR)
		return (ret);
	while (!ft_parser_peek(str_s, str_e, "|"))
	{
		v->tok = ft_parser_get_token(str_s, str_e, &(v->tk_s), &(v->tk_e));
		if (v->tok == 0)
			break ;
		if (ft_upd_exec_cmd_argv(ret, cmd, v, &argc) < 0)
			return (ret);
		ret = ft_parser_parse_redir(ret, str_s, str_e, v);
		if (*ret == P_ERROR)
			return (ret);
	}
	cmd->argv_s[argc] = 0;
	cmd->argv_e[argc] = 0;
	return (ret);
}
