/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_sys_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:55:53 by cudoh             #+#    #+#             */
/*   Updated: 2022/11/26 19:55:53 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_pwd(t_parser_var *v)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, MAX_PATH);
	if (pwd != NULL)
	{
		ft_printf("%s\n", pwd);
		free(pwd);
		ft_ms_free_rsc(v, FREE_ON_EXIT);
		exit(0);
	}
	else
	{
		perror("Unknown directory");
		ft_ms_free_rsc(v, FREE_ON_EXIT);
		exit(errno);
	}
	return (0);
}

int	ft_ms_sys_pwd(t_cmd *cmd, t_parser_var *v)
{
	t_cmd_exec	*cmd_exec;

	if (*(cmd) != EXEC)
		return (1);
	cmd_exec = (t_cmd_exec *)(cmd);
	if (v->flag_handler == 0)
	{
		ft_ms_handle_quotes_n_dollar(cmd_exec->argv_s, v);
		v->flag_handler = 1;
	}
	if (ft_ms_strcmp((cmd_exec->argv_s)[0], "pwd") != 0)
		return (1);
	v->flag_handler = 0;
	if ((cmd_exec->argv_s)[1] != NULL && (cmd_exec->argv_s)[1][0] == '-')
	{
		ft_printf("Error! - (pwd) : no option required\n");
		ft_ms_free_rsc(v, FREE_ON_EXIT);
		rl_clear_history();
		exit(STATUS_ERROR_OPTION);
	}
	if (ft_pwd(v) < 0)
		return (-1);
	return (0);
}
