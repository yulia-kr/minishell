/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_sys_call_child.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:59:20 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/11 14:59:20 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ms_sys_call_child(t_parser_var *v_p)
{
	int	pid_child;

	ft_term_config_set(&(v_p->v_term), TERM_CONFIG_DEFAULT);
	pid_child = fork();
	if (pid_child == 0)
	{
		v_p->pid = 0;
		ft_ms_run_cmd(v_p->cmd_tree, v_p);
	}
	wait(&(v_p->status));
	v_p->status_code = WIFEXITED(v_p->status);
	if (v_p->status_code == 1)
		v_p->status = WEXITSTATUS(v_p->status);
	ft_term_config_set(&(v_p->v_term), TERM_CONFIG_CUSTOM);
}
