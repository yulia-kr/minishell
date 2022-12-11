/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_sys_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:39:35 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/09 20:19:58 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ms_sys_echo(t_cmd *cmd, t_parser_var *v_p)
{
	int			check_n;
	int			i;
	t_cmd_exec	*cmd_exec;

	i = 1;
	check_n = 0;
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
	while ((ft_strncmp((cmd_exec->argv_s)[i], "-n", ft_strlen("-n"))) == 0)
	{
		if ((cmd_exec->argv_s)[i][ft_strlen("-n")] != '\0')
			break ;
		check_n = 1;
		i++;
	}
	while ((cmd_exec->argv_s)[i])
	{
		ft_printf("%s", (cmd_exec->argv_s)[i]);
		if ((cmd_exec->argv_s)[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (check_n == 0)
		write(1, "\n", 1);
	return (0);
}
