/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_sys_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:52:53 by cudoh             #+#    #+#             */
/*   Updated: 2022/11/13 11:52:53 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 	This function displays all declared environment variables
 * 			Alphabetically from uppercase to lowercase.
 * 
 */
static int	ft_is_argv(t_parser_var *v)
{
	int		idx;
	char	*s;

	s = NULL;
	idx = 0;
	ft_ms_env_arr_sort(v);
	while (v->env[idx] != NULL)
	{
		s = v->env[idx];
		ft_printf("declare -x ");
		while (!ft_strchr("=", *s))
		{
			write(1, s, 1);
			s++;
		}
		if (*s != '\0')
			ft_printf("=\"%s\"\n", (++s));
		else
			ft_printf("\n");
		idx++;
	}
	v->status = STATUS_OK;
	ft_ms_free_rsc(v, FREE_ON_CMD_EXEC);
	return (0);
}

/**
 * @brief 	The export command should be modified only within the main (parent)
 * 			process. Hence, this function only prints the shell env if 
 * 			executed within a child process.
 * 			(1) : Replaces the cmd "export" with "env" in arg array.
 * 			(1a) -> create a buffer to store the str "env";
 * 			(1b) -> copy the string "env" into the created buffer
 * 			(2) : Add the newly created buffer to garbage linked list
 * 				(exec_dyn_lst) for deallocation after cmd execution.
 * 			(3) : Terminate the cmd argv array with a null just after
 * 				or next to the cmd "env" string in the array.
 * 			(4) : Execute the sys call function ft_ms_sys_env.
 * 			(5) : Free all resources used for during execution process.
 * 
 * 
 * @param argv_s 
 * @param v_p 
 */
static void	ft_export_on_child(t_cmd_exec *cmd_exec, t_parser_var *v_p)
{
	char	**argv_s;

	argv_s = cmd_exec->argv_s;
	argv_s[0] = (char *)ft_calloc(ft_strlen("env") + 1, SZ_CHAR);
	ft_memcpy((void *)((argv_s)[0]), (void *)("env"), ft_strlen("env"));
	ft_lstadd_back(&(v_p->exec_dyn_lst), \
			ft_lstnew((void *)(&((argv_s)[0]))));
	(argv_s)[1] = NULL;
	ft_is_argv(v_p);
	ft_ms_free_rsc(v_p, FREE_ON_EXIT);
	exit(0);
}

/**
 * @brief 	The export sys call adds new or replace existing var in the shell
 * 			environment array. This operation should be done only in the main
 * 			(parent) process. If called within a child process, then it should
 * 			only print the contents of the environment array.
 * 			(1) - Check that the cmd type is of EXEC. if true, typecast ptr.
 * 			(2) - Handle the status character within cmd argv ($?).
 * 			(3) - Handle quote and dollar sign within cmd argv.
 * 			(4) - Store env value in variable (var) from cmd argv buffer.
 * 			(5) - Confirm that the first item in cmd argv equals "export".
 * 			(6) - Check the process level (parent or child).
 * 			(6a) -> if child, call ft_export_on_child.
 * 			(6b) -> if parent, call ft_export_on_parent.
 * 
 * @param v_p 
 * @return int 
 */
int	ft_ms_sys_export(t_cmd *cmd, t_parser_var *v_p)
{
	t_cmd_exec	*cmd_exec;

	if (*(cmd) != EXEC)
		return (1);
	cmd_exec = (t_cmd_exec *)(cmd);
	if ((cmd_exec->argv_s)[0] == 0)
		return (-1);
	if (v_p->flag_handler == 0)
	{
		ft_ms_handle_quotes_n_dollar(cmd_exec->argv_s, v_p);
		v_p->flag_handler = 1;
	}
	if (ft_ms_strcmp((cmd_exec->argv_s)[0], "export") != 0)
		return (1);
	v_p->flag_handler = 0;
	if (v_p->pid == 0)
		ft_export_on_child(cmd_exec, v_p);
	if (ft_ms_export_on_parent(cmd_exec, v_p, ft_is_argv) == 0 && \
								v_p->status != STATUS_OK)
		return (-1);
	return (0);
}
