/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_cmd_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:56:51 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/10 13:33:31 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   This function is used within the ft_ms_exec_cmd function to
 *          execute any pipe command found within the parsed tree return by 
 * 			the ft_parser_parse function.
 * @param cmd 
 */
void	ft_ms_cmd_pipe(t_cmd *cmd, t_parser_var *v_p)
{
	t_cmd_pipe	*cmd_pipe;
	int			p[2];
	int			status_l;
	int			status_r;

	status_l = 0;
	status_r = 0;
	cmd_pipe = (t_cmd_pipe *)cmd;
	if (*(cmd_pipe->left) == P_ERROR || *(cmd_pipe->right) == P_ERROR)
		exit(v_p->status);
	if (pipe(p) < 0)
		perror("Error!\nsys_pipe failed.");
	if (fork() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		ft_ms_run_cmd(cmd_pipe->left, v_p);
	}
	if (fork() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		ft_ms_run_cmd(cmd_pipe->right, v_p);
	}
	close(p[0]);
	close(p[1]);
	wait(&status_l);
	wait(&status_r);
	ft_ms_free_rsc(v_p, FREE_ON_EXIT);
	if (WIFEXITED(status_r) == 1)
				status_r = WEXITSTATUS(status_r);
	exit(status_r);
}
