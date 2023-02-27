/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_cmd_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:39:56 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/06 09:20:34 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   This function executes only the default system calls functions
 *          (env, pwd, echo, e.t.c ) in a child process. 
 *          If the command string matches any of the sys call function, this
 *          function supercedes the execve function call.
 * 
 * @param cmd 
 * @param env_var_list 
 * @return int 
 */
static int	ft_sys_call(t_cmd_exec *cmd_exec, t_parser_var *v_p)
{
	int	status;

	status = 1;
	status = ft_ms_sys_env((t_cmd *)cmd_exec, v_p);
	if (status <= 0)
		return (status);
	status = ft_ms_sys_export((t_cmd *)cmd_exec, v_p);
	if (status <= 0)
		return (status);
	status = ft_ms_sys_unset((t_cmd *)cmd_exec, v_p);
	if (status <= 0)
		return (status);
	status = ft_ms_sys_chdir((t_cmd *)cmd_exec, v_p);
	if (status <= 0)
		return (status);
	status = ft_ms_sys_pwd((t_cmd *)cmd_exec, v_p);
	if (status <= 0)
		return (status);
	status = ft_ms_sys_echo((t_cmd *)cmd_exec, v_p);
	if (status <= 0)
		return (status);
	return (status);
}

/**
 * @brief   This function is used within the ft_ms_exec_cmd function to
 *          execute any exec cmd found within the parsed tree return by the
 *          ft_parser_parse function.
 * 
 * @param cmd 
 */
void	ft_ms_cmd_exec(t_cmd *cmd, t_parser_var *v_p)
{
	t_cmd_exec	*cmd_exec;
	int			status;

	cmd_exec = (t_cmd_exec *)cmd;
	if (cmd_exec->argv_s[0] == 0)
		exit(127);
	status = ft_sys_call(cmd_exec, v_p);
	if (status <= 0)
	{
		ft_ms_free_rsc(v_p, FREE_ON_EXIT);
		exit(status);
	}
	if (v_p->flag_handler == 0)
	{
		ft_ms_handle_quotes_n_dollar(cmd_exec->argv_s, v_p);
		v_p->flag_handler = 1;
	}
	ft_ms_find_prog(v_p->env_path, cmd_exec->argv_s, v_p);
	if (execve(cmd_exec->argv_s[0], cmd_exec->argv_s, v_p->env) < 0)
		ft_printf("%s: %s\n", cmd_exec->argv_s[0], strerror(errno));
	ft_ms_free_rsc(v_p, FREE_ON_EXIT);
	exit(127);
}
