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

/**
 * @brief 	This function prints all the system environment variables.
 * 
 * @param env_var_list 
 */
int	ft_ms_sys_env(t_cmd *cmd, t_parser_var *v_p)
{
	int			idx;
	t_cmd_exec	*cmd_exec;

	idx = 0;
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
	if (cmd_exec->argv_s[1] != NULL)
	{
		ft_printf("Error! - (env) : no option or argument required\n");
		v_p->status = STATUS_ERROR_OPTION;
		ft_ms_free_rsc(v_p, FREE_ON_EXIT);
		exit(127);
	}
	while ((v_p->env)[idx] != NULL)
	{
		ft_printf("%s\n", (v_p->env)[idx]);
		idx++;
	}
	return (0);
}
