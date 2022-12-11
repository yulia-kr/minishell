/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_cmd_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:43:20 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/10 13:41:45 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   This function is used within the ft_ms_exec_cmd function to
 *          execute any redir command found within the parsed tree return by 
 *          the ft_parser_parse function.
 * 
 * @param cmd 
 */
void	ft_ms_cmd_redir(t_cmd *cmd, t_parser_var *v_p)
{
	t_cmd_redir	*cmd_redir;

	cmd_redir = (t_cmd_redir *)cmd;
	close(cmd_redir->file_fd);
	ft_printf("%d %d\n", v_p->status, cmd_redir->file_mode);
	if (open(cmd_redir->file_s, cmd_redir->file_mode, S_IRWXU) < 0)
	{
		perror("open");
		ft_ms_free_rsc(v_p, FREE_ON_EXIT);
		exit(1);
	}
	ft_ms_run_cmd(cmd_redir->cmd, v_p);
}
