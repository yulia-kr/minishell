/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:56:51 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/06 09:21:08 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   This function is used within the ft_ms_exec_cmd function to
 *          execute any list command found within the parsed tree return by 
 * 			the ft_parser_parse function.
 * @param cmd 
 */
void	ft_ms_cmd_list(t_cmd *cmd, t_parser_var *v)
{
	t_cmd_list	*cmd_list;

	cmd_list = (t_cmd_list *)cmd;
	if (fork() == 0)
		ft_ms_run_cmd(cmd_list->left, v);
	wait(0);
	ft_ms_run_cmd(cmd_list->right, v);
}
