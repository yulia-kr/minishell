/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_sys_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:39:35 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/22 23:00:52 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_chk_option(char *arg, int *flag)
{
	size_t	len_arg;
	size_t	idx;

	len_arg = 0;
	idx = 0;
	if (arg == NULL)
		return (-1);
	len_arg = ft_strlen(arg);
	if (len_arg < 2)
		return (-2);
	if (*arg != '-')
		return (-2);
	idx++;
	while (idx < len_arg)
	{
		if (arg[idx] != 'n')
			return (-2);
		idx++;
	}
	*flag = 1;
	return (0);
}

static int	ft_prnt_arg(t_cmd_exec *exe, int *idx, int *flag_ign, int *s_opt)
{
	if (*s_opt == 0)
		return (0);
	else if (*s_opt == -2)
	{
		*flag_ign = 1;
		ft_printf("%s", ((exe->argv_s)[*idx]));
		if ((exe->argv_s)[*idx + 1] != NULL)
			write(1, " ", 1);
	}
	else if (*s_opt == -1)
	{
		return (-1);
	}
	return (0);
}

static int	ft_echo(t_cmd_exec *cmd_exec)
{
	int			check_n;
	int			i;
	int			status_opt_chk;
	int			flag_ign;

	i = 1;
	check_n = 0;
	status_opt_chk = 0;
	flag_ign = 0;
	if (((cmd_exec->argv_s)[i]) == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	while ((cmd_exec->argv_s)[i] != NULL)
	{
		if (flag_ign == 0)
			status_opt_chk = ft_chk_option(((cmd_exec->argv_s)[i]), &check_n);
		if (ft_prnt_arg(cmd_exec, &i, &flag_ign, &status_opt_chk) < 0)
			return (0);
		i++;
	}
	if (check_n == 0)
		write(1, "\n", 1);
	return (0);
}

int	ft_ms_sys_echo(t_cmd *cmd, t_parser_var *v_p)
{
	t_cmd_exec	*cmd_exec;

	cmd_exec = (t_cmd_exec *)(cmd);
	if (*(cmd) != EXEC)
		return (1);
	if (v_p->flag_handler == 0)
	{
		ft_ms_handle_quotes_n_dollar(cmd_exec->argv_s, v_p);
		v_p->flag_handler = 1;
	}
	if (ft_ms_strcmp((cmd_exec->argv_s)[0], "echo") != 0)
		return (1);
	v_p->flag_handler = 0;
	ft_echo(cmd_exec);
	return (0);
}
