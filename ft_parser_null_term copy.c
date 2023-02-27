/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_null_term.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 20:32:30 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/11 11:00:48 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_null_term_exec(t_cmd *cmd)
{
	int			i;
	t_cmd_exec	*exec_cmd;

	i = 0;
	exec_cmd = (t_cmd_exec *)cmd;
	while (((exec_cmd->argv_e)[i]) != 0)
	{
		if (*((exec_cmd->argv_e)[i]) != 0)
			(*((exec_cmd->argv_e)[i]) = '\0');
		i++;
	}
}

/**
 * @brief 	This function null terminates the all the string args at 
 * 			pipe and list nodes recursively.
 * 
 * @param cmd : address of the cmd pointer is passed in
 */
static void	ft_null_term_pipe_list(t_cmd **cmd)
{
	t_cmd_list	*list_cmd;
	t_cmd_pipe	*pipe_cmd;

	if ((**cmd) == LIST)
	{
		list_cmd = (t_cmd_list *)(*cmd);
		ft_parser_null_term(list_cmd->left);
		ft_parser_null_term(list_cmd->right);
	}
	else if ((**cmd) == PIPE)
	{
		pipe_cmd = (t_cmd_pipe *)(*cmd);
		ft_parser_null_term(pipe_cmd->left);
		ft_parser_null_term(pipe_cmd->right);
	}
}

/**
 * @brief 	This function null terminates all the string args with the null
 * 			character '\0'
 * 
 * @param cmd 
 * @return t_cmd* 
 */
t_cmd	*ft_parser_null_term(t_cmd *cmd)
{
	t_cmd_redir	*redir_cmd;

	if (cmd == 0)
		return (0);
	if (*cmd == EXEC)
	{
		ft_null_term_exec(cmd);
	}
	else if (*cmd == REDIR)
	{
		redir_cmd = (t_cmd_redir *)cmd;
		ft_parser_null_term(redir_cmd->cmd);
		*(redir_cmd->file_e) = 0;
	}
	else
		ft_null_term_pipe_list(&cmd);
	return (cmd);
}
