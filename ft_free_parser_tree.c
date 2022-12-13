/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_parser_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 20:32:30 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/11 13:46:44 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 	This function null terminates the all the string args at 
 * 			pipe and list nodes recursively.
 * 
 * @param cmd : address of the cmd pointer is passed in
 */
static void	ft_free_parser_pipe(t_cmd **cmd)
{
	t_cmd_pipe	*pipe_cmd;

	if ((**cmd) == PIPE)
	{
		pipe_cmd = (t_cmd_pipe *)(*cmd);
		ft_free_parser_tree(pipe_cmd->left);
		ft_free_parser_tree(pipe_cmd->right);
		pipe_cmd->left = NULL;
		pipe_cmd->right = NULL;
		free(pipe_cmd);
		pipe_cmd = NULL;
	}
}

/**
 * @brief 	This function null terminates all the string args with the null
 * 			character '\0'
 * 
 * @param cmd 
 * @return t_cmd* 
 */
void	ft_free_parser_tree(t_cmd *cmd)
{
	t_cmd_exec	*exec_cmd;
	t_cmd_redir	*redir_cmd;

	if (cmd == 0)
		return ;
	if (*cmd == EXEC)
	{
		exec_cmd = (t_cmd_exec *)cmd;
		ft_ms_rst_free_ptr_to_arr(&(exec_cmd->argv_s));
		ft_ms_rst_free_ptr_to_arr(&(exec_cmd->argv_e));
		free(exec_cmd);
		exec_cmd = NULL;
	}
	else if (*cmd == REDIR)
	{
		redir_cmd = (t_cmd_redir *)cmd;
		ft_free_parser_tree(redir_cmd->cmd);
		(redir_cmd->file_s) = NULL;
		(redir_cmd->file_e) = NULL;
		free(redir_cmd);
		redir_cmd = NULL;
	}
	else
		ft_free_parser_pipe(&cmd);
}
