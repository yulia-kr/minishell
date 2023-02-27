/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_sys_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:55:50 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/11 16:58:04 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   This func checks if the exit command is given by the user
 *          The function handles whitespaces that may exist before the cmd. 
 * 
 * @param  v_p
 * @return int  -1 is returned if the user have given the exit command
 *               0 is returned if no exit command is the first word in str.
 */
int	ft_ms_sys_exit(t_cmd *cmd, t_parser_var *v_p)
{
	t_cmd_exec	*cmd_exec;

	if (*(cmd) != EXEC)
		return (1);
	cmd_exec = (t_cmd_exec *)(cmd);
	if ((cmd_exec->argv_s)[0] == 0)
		return (-1);
	if (v_p->flag_handler == 0)
	{
		ft_ms_handle_quotes_n_dollar(cmd_exec->argv_s, v_p);
		v_p->flag_handler = 1;
	}
	if (ft_ms_strcmp((cmd_exec->argv_s)[0], "exit") != 0)
		return (1);
	v_p->flag_handler = 0;
	ft_ms_free_rsc(v_p, FREE_ON_EXIT);
	exit(0);
	return (0);
}
