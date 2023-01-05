/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_sys_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:47:38 by cudoh             #+#    #+#             */
/*   Updated: 2022/11/11 17:47:38 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_env(t_parser_var *v, t_cmd_exec *cmd_exec)
{
	int	idx;

	idx = 0;
	if (cmd_exec->argv_s[1] != NULL)
	{
		ft_printf("Error! - (env) : no option or argument required\n");
		v->status = STATUS_ERROR_OPTION;
		ft_ms_free_rsc(v, FREE_ON_EXIT);
		exit(1);
	}
	while ((v->env)[idx] != NULL)
	{
		if (ft_strchr(((v->env)[idx]), '='))
			ft_printf("%s\n", (v->env)[idx]);
		idx++;
	}
	return (0);
}

/**
 * @brief 	This function prints all the system environment variables.
 * 
 * @param env_var_list 
 */
int	ft_ms_sys_env(t_cmd *cmd, t_parser_var *v_p)
{
	t_cmd_exec	*cmd_exec;

	cmd_exec = (t_cmd_exec *)(cmd);
	if (*(cmd) != EXEC)
		return (1);
	if (v_p->flag_handler == 0)
	{
		ft_ms_handle_quotes_n_dollar(cmd_exec->argv_s, v_p);
		v_p->flag_handler = 1;
	}
	if (ft_ms_strcmp((cmd_exec->argv_s)[0], "env") != 0)
		return (1);
	v_p->flag_handler = 0;
	ft_env(v_p, cmd_exec);
	return (0);
}
