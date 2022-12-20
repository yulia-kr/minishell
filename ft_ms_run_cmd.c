/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_run_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 22:15:24 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/17 17:33:44 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief   This function
 * 
 * @param cmd 
 */
int	ft_ms_run_cmd(t_cmd *cmd, t_parser_var *v_p)
{
	int	rc;

	rc = 1;
	if (cmd == 0)
		exit(1);
	if (*cmd == EXEC)
		ft_ms_cmd_exec(cmd, v_p);
	else if (*cmd == REDIR)
		ft_ms_cmd_redir(cmd, v_p);
	else if (*cmd == LIST)
		ft_ms_cmd_list(cmd, v_p);
	else if (*cmd == PIPE)
		ft_ms_cmd_pipe(cmd, v_p);
	else
		rc = ft_printf("Error! invalid syntax\n");
	exit(1);
	return (rc);
}
