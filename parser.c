/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 23:22:39 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/06 10:50:19 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*ft_parser_init_cmd_pipe(t_cmd *left, t_cmd *right)
{
	t_cmd_pipe	*cmd;

	cmd = ft_calloc(sizeof(*cmd), 1);
	cmd->cmd_type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*ft_parser_init_cmd_list(t_cmd *left, t_cmd *right)
{
	t_cmd_list	*cmd;

	cmd = ft_calloc(sizeof(*cmd), 1);
	cmd->cmd_type = LIST;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
/**
 * @brief   This is a constructor function that creates the command object.
 * 
 * @param v_p 
 * @return t_cmd* 
 */

t_cmd	*ft_parser_init_cmd_exec(t_parser_var *v_p)
{
	t_cmd_exec	*cmd;

	cmd = ft_calloc(sizeof(*cmd), 1);
	cmd->cmd_type = EXEC;
	cmd->argv_s = (char **)ft_calloc(sizeof(char *), (v_p->max_args + 1));
	cmd->argv_e = (char **)ft_calloc(sizeof(char *), (v_p->max_args + 1));
	return ((t_cmd *)cmd);
}

t_cmd	*ft_parser_init_cmd_redir(t_cmd *subcmd, char *f_s, char *f_e, \
									int f_m, int f_fd)
{
	t_cmd_redir	*cmd;

	cmd = ft_calloc(sizeof(*cmd), 1);
	cmd->cmd_type = REDIR;
	cmd->file_mode = f_m;
	cmd->file_s = f_s;
	cmd->file_e = f_e;
	cmd->file_fd = f_fd; // 0 stdin, 1 stdout
	cmd->cmd = subcmd;
	return ((t_cmd *)cmd);
}
